/*
 * Generational Conservative Garbage Collector for SBCL x86
 *
 * inline functions that gc-common.c needs sight of
 */


/*
 * This software is part of the SBCL system. See the README file for
 * more information.
 *
 * This software is derived from the CMU CL system, which was
 * written at Carnegie Mellon University and released into the
 * public domain. The software is in the public domain and is
 * provided with absolutely no warranty. See the COPYING and CREDITS
 * files for more information.
 */

#ifndef _GENCGC_INTERNAL_H_
#define _GENCGC_INTERNAL_H_

#include <limits.h>
#include "gc.h"
#include "gencgc-alloc-region.h"
#include "genesis/code.h"
#include "hopscotch.h"

#ifndef GENCGC_IS_PRECISE
#error "GENCGC_IS_PRECISE must be #defined as 0 or 1"
#endif

#define GENCGC_PAGE_WORDS (GENCGC_PAGE_BYTES/N_WORD_BYTES)

/* Calculate the start address for the given page number. */
static inline char *page_address(page_index_t page_num) {
    return (void*)(DYNAMIC_SPACE_START + (page_num * GENCGC_PAGE_BYTES));
}

int gencgc_handle_wp_violation(void*, void*);


#if N_WORD_BITS == 64
  // It's more economical to store scan_start_offset using 4 bytes than 8.
  // Doing so makes struct page fit in 8 bytes if words_used takes 2 bytes.
  //   scan_start_offset = 4
  //   words_used        = 2
  //   flags             = 1
  //   gen               = 1
  // If words_used takes 4 bytes, then the above is 10 bytes which is padded to
  // 12, which is still an improvement over the 16 that it would have been.
# define CONDENSED_PAGE_TABLE 1
#else
# define CONDENSED_PAGE_TABLE 0
#endif

#if GENCGC_PAGE_WORDS > USHRT_MAX
# if GENCGC_PAGE_WORDS > UINT_MAX
#   error "GENCGC_PAGE_WORDS unexpectedly large."
# else
    typedef unsigned int page_words_t;
# endif
#else
  typedef unsigned short page_words_t;
#endif

/* New objects are allocated to PAGE_TYPE_MIXED or PAGE_TYPE_CONS */
/* If you change these constants, then possibly also change the following
 * functions in 'room.lisp':
 *  MAP-CODE-OBJECTS
 *  PRINT-ALL-CODE
 *  PRINT-LARGE-CODE
 *  PRINT-LARGE-UNBOXED
 */

// 4 bits for the type, 1 bit for SINGLE_OBJECT, 1 bit for OPEN_REGION

#define PAGE_TYPE_MASK        15 // mask out 'single-object' and 'open-region' flags
#define PAGE_TYPE_UNBOXED      1 // #b001
#define PAGE_TYPE_BOXED        2 // #b010
#define PAGE_TYPE_MIXED        3 // #b011
/* Small-Mixed pages hold objects that don't span cards. This is relatively easy to
 * arrange for by adding filler at the end of a card to align prior to the next object,
 * subject to a maximum allowable waste. Root scavenging can respect card boundaries
 * and use scavenge functions specific to each object - the best of both worlds */
#define PAGE_TYPE_SMALL_MIXED  4 // #b100
#define PAGE_TYPE_CONS         5 // #b101
#define PAGE_TYPE_CODE         7 // #b111
#define THREAD_PAGE_FLAG       8
#define SINGLE_OBJECT_FLAG    16
#define OPEN_REGION_PAGE_FLAG 32
#define FREE_PAGE_FLAG        0

/* Note that this structure is also used from Lisp-side in
 * src/code/room.lisp, and the Lisp-side structure layout is currently
 * not groveled from C code but hardcoded. Any changes to the
 * structure layout need to be also made there.
 *
 * FIXME: We should probably just define this structure in Lisp, and
 * output the C version in genesis. -- JES, 2006-12-30.
 */
struct page {
    /* This is the offset from the first byte of some object in memory
     * prior to and no closer than the start of the page to the start
     * of the page.  Lower values here are better, 0 is ideal.  This
     * is useful for determining where to start when scanning forward
     * through a heap page (either for conservative root validation or
     * for scavenging). MUST be 0 for unallocated pages.
     */
#if CONDENSED_PAGE_TABLE
    // The low bit of the offset indicates the scale factor:
    // 0 = double-lispwords, 1 = gc cards. Large objects are card-aligned,
    // and this representation allows for a 32TB contiguous block using 32K
    // card size. Larger allocations will have pages that can't directly
    // store the full offset. That has to be dealt with by the accessor.
    unsigned int scan_start_offset_;
#else
    os_vm_size_t scan_start_offset_;
#endif

    /* the number of lispwords of this page that are used. This may be less
     * than the usage at an instant in time for pages within the current
     * allocation regions. MUST be 0 for unallocated pages.
     */
    page_words_t words_used_;

    // !!! If bit positions are changed, be sure to reflect the changes into
    // page_extensible_p() as well as ALLOCATION-INFORMATION in sb-introspect
    // and WALK-DYNAMIC-SPACE.
        /*
         * The 4 low bits of 'type' are defined by PAGE_TYPE_x constants.
         *  0000 free
         *  ?001 strictly boxed data (pointers, immediates, object headers)
         *  ?010 strictly unboxed data
         *  ?011 mixed boxed/unboxed non-code objects
         *  ?111 code
         * The next two bits are SINGLE_OBJECT and OPEN_REGION */
    unsigned char type;

    /* the generation that this page belongs to. This should be valid
     * for all pages that may have objects allocated, even current
     * allocation region pages - this allows the space of an object to
     * be easily determined. */
    generation_index_t gen;
};
extern struct page *page_table;

/* a structure to hold the state of a generation
 *
 * CAUTION: If you modify this, make sure to touch up the alien
 * definition in src/code/gc.lisp accordingly. ...or better yes,
 * deal with the FIXME there...
 */
struct generation {
    /* the bytes allocated to this generation */
    os_vm_size_t bytes_allocated;

    /* the number of bytes at which to trigger a GC */
    os_vm_size_t gc_trigger;

    /* to calculate a new level for gc_trigger */
    os_vm_size_t bytes_consed_between_gc;

    /* the number of GCs since the last raise */
    int num_gc;

    /* the number of GCs to run on the generations before raising objects to the
     * next generation */
    int number_of_gcs_before_promotion;

    /* the cumulative sum of the bytes allocated to this generation. It is
     * cleared after a GC on this generations, and update before new
     * objects are added from a GC of a younger generation. Dividing by
     * the bytes_allocated will give the average age of the memory in
     * this generation since its last GC. */
    os_vm_size_t cum_sum_bytes_allocated;

    /* a minimum average memory age before a GC will occur helps
     * prevent a GC when a large number of new live objects have been
     * added, in which case a GC could be a waste of time */
    double minimum_age_before_gc;
};

/* When computing a card index we never subtract the heap base, which simplifies
 * code generation. The heap base is guaranteed to be GC-page-aligned.
 * The low bits can wraparound from all 1s to all 0s such that lowest numbered
 * page index in linear order may have a higher card index.
 * Two small examples of the distinction between page index and card index.
 * For both examples: heap base = 0xEB00, page-size = 256b, npages = 8.
 *
 * Scenario A:
 *   CARDS_PER_PAGE = 1, card-size = 256b, ncards = 8, right-shift = 8, mask = #b111
 *     page     page      card
 *    index     base     index
 *       0      EB00        3
 *       1      EC00        4
 *       2      ED00        5
 *       3      EE00        6
 *       4      EF00        7
 *       5      F000        0
 *       6      F100        1
 *       7      F200        2
 *
 * Scenario B:
 *   CARDS_PER_PAGE = 2, card-size = 128b, ncards = 16, right-shift = 7, mask = #b1111
 *     page     page            card
 *    index     base         indices
 *       0      EB00, EB80      6, 7
 *       1      EC00, EC80      8, 9
 *       2      ED00, ED80    10, 11
 *       3      EE00, EE80    12, 13
 *       4      EF00, EF80    14, 15
 *       5      F000, F080      0, 1
 *       6      F100, F180      2, 3
 *       7      F200, F280      4, 5
 *
 */
extern unsigned char *gc_card_mark;
extern long gc_card_table_mask;
#define addr_to_card_index(addr) ((((uword_t)addr)>>GENCGC_CARD_SHIFT) & gc_card_table_mask)
#define page_to_card_index(n) addr_to_card_index(page_address(n))

struct __attribute__((packed)) corefile_pte {
  uword_t sso; // scan start offset
  page_words_t words_used; // low bit is the 'large object' flag
};

/* values for the page.allocated field */


extern page_index_t page_table_pages;


/* forward declarations */

void gc_close_region(struct alloc_region *alloc_region, int page_type);
static inline void ensure_region_closed(struct alloc_region *alloc_region,
                                        int page_type)
{
    if (alloc_region->start_addr)
        gc_close_region(alloc_region, page_type);
}

static inline void gc_set_region_empty(struct alloc_region *region)
{
    /* Free-pointer has to be not equal to 0 because it's undefined behavior
     * to add any value whatsoever to the null pointer.
     * Annoying, isn't it.  http://c-faq.com/null/machexamp.html */
    region->free_pointer = region->end_addr = (void*)0x1000;
    /* Start 0 is the indicator of closed-ness. */
    region->start_addr = 0;
    /* last_page is not reset. It can be used as a hint where to resume
     * allocating after closing and re-opening the region */
}

static inline void gc_init_region(struct alloc_region *region)
{
    // A distinction without a difference (it used to do one more assignment)
    gc_set_region_empty(region);
}

/*
 * predicates
 */

#define compacting_p() (from_space>=0)

/* Find the page index within the page_table for the given
 * address. Return -1 on failure. */
static inline page_index_t find_page_index(void *addr)
{
    if (addr >= (void*)DYNAMIC_SPACE_START) {
        page_index_t index = ((uintptr_t)addr -
                              (uintptr_t)DYNAMIC_SPACE_START) / GENCGC_PAGE_BYTES;
        if (index < page_table_pages)
            return (index);
    }
    return (-1);
}

#define page_single_obj_p(page) ((page_table[page].type & SINGLE_OBJECT_FLAG)!=0)

extern unsigned char* gc_page_pins;
static inline boolean pinned_p(lispobj obj, page_index_t page)
{
    extern struct hopscotch_table pinned_objects;
    // Single-object pages can be pinned, but the object doesn't go
    // in the hashtable. pinned_p can be queried on those pages,
    // but the answer is always 'No', because if pinned, the page would
    // already have had its generation changed to newspace.
    if (page_single_obj_p(page)) return 0;

#ifdef RETURN_PC_WIDETAG
    // Yet another complication from the despised LRA objects- with the
    // refinement of 8 pin bits per page, we either must set all possible bits
    // for a simple-fun, or map LRAs to the code base address.
    if (widetag_of(native_pointer(obj)) == RETURN_PC_WIDETAG) {
        // The hash-table stores tagged pointers.
        obj = make_lispobj(fun_code_header(native_pointer(obj)),
                           OTHER_POINTER_LOWTAG);
        page = find_page_index((void*)obj);
    }
#endif

    unsigned char pins = gc_page_pins[page];
    if (!pins) return 0;
    unsigned addr_lowpart = obj & (GENCGC_PAGE_BYTES-1);
    // Divide the page into 8 parts, see whether that part is pinned.
    unsigned subpage = addr_lowpart / (GENCGC_PAGE_BYTES/8);
    return (pins & (1<<subpage)) && hopscotch_containsp(&pinned_objects, obj);
}

// Return true only if 'obj' must be *physically* transported to survive gc.
// Return false if obj is in the immobile space regardless of its generation.
// Pretend pinned objects are not in oldspace so that they don't get moved.
static boolean __attribute__((unused))
from_space_p(lispobj obj)
{
    gc_dcheck(compacting_p());
    page_index_t page_index = find_page_index((void*)obj);
    // NOTE: It is legal to access page_table at index -1,
    // and the 'gen' of page -1 is an otherwise unused value.
    return page_table[page_index].gen == from_space && !pinned_p(obj, page_index);
}

static boolean __attribute__((unused)) new_space_p(lispobj obj)
{
    gc_dcheck(compacting_p());
    page_index_t page_index = find_page_index((void*)obj);
    // NOTE: It is legal to access page_table at index -1,
    // and the 'gen' of page -1 is an otherwise unused value.
    return page_table[page_index].gen == new_space;
}

#ifdef LISP_FEATURE_IMMOBILE_SPACE
struct fixedobj_page { // 12 bytes per page
    union immobile_page_attr {
      int packed;
      struct {
        unsigned char flags;
        unsigned char obj_align; // object spacing expressed in lisp words
        unsigned char unused1;
        /* Which generations have data on this page */
        unsigned char gens_; // a bitmap
      } parts;
    } attr;
    int free_index; // index is in bytes. 4 bytes
    short int prior_gc_free_word_index; // index is in words. 2 bytes
    /* page index of next page with same attributes */
    short int page_link; // 2 bytes
};
extern struct fixedobj_page *fixedobj_pages;
#define fixedobj_page_obj_align(i) (fixedobj_pages[i].attr.parts.obj_align<<WORD_SHIFT)
#endif

extern page_index_t next_free_page;

extern uword_t
walk_generation(uword_t (*proc)(lispobj*,lispobj*,uword_t),
                generation_index_t generation, uword_t extra);

generation_index_t gc_gen_of(lispobj obj, int defaultval);

#endif /* _GENCGC_INTERNAL_H_*/
