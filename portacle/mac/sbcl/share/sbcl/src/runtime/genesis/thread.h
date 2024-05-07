/*
 * This is a machine-generated file. Please do not edit it by hand.
 *
 * This file contains low-level information about the
 * internals of a particular version and configuration
 * of SBCL. It is used by the C compiler to create a runtime
 * support environment, an executable program in the host
 * operating system's native format, which can then be used to
 * load and run 'core' files, which are basically programs
 * in SBCL's own format.
 */
#ifndef SBCL_GENESIS_THREAD
#define SBCL_GENESIS_THREAD
#define THREAD_HEADER_SLOTS 0

#ifdef __ASSEMBLER__

/* These offsets are SLOT-OFFSET * N-WORD-BYTES - LOWTAG
 * so they work directly on tagged addresses. */

#define THREAD_NO_TLS_VALUE_MARKER_OFFSET 0
#define THREAD_STEPPING_OFFSET 8
#define THREAD_BINDING_STACK_POINTER_OFFSET 16
#define THREAD_CURRENT_CATCH_BLOCK_OFFSET 24
#define THREAD_CURRENT_UNWIND_PROTECT_BLOCK_OFFSET 32
#define THREAD_PSEUDO_ATOMIC_BITS_OFFSET 40
#define THREAD_ALIEN_STACK_POINTER_OFFSET 48
#define THREAD_PROFILE_DATA_OFFSET 56
#define THREAD_BOXED_TLAB_OFFSET 64
#define THREAD_CONS_TLAB_OFFSET 88
#define THREAD_MIXED_TLAB_OFFSET 112
#define THREAD_OS_ADDRESS_OFFSET 136
#define THREAD_OS_THREAD_OFFSET 144
#define THREAD_OS_KERNEL_TID_OFFSET 152
#define THREAD_ALIEN_STACK_START_OFFSET 160
#define THREAD_BINDING_STACK_START_OFFSET 168
#define THREAD_CONTROL_STACK_START_OFFSET 176
#define THREAD_CONTROL_STACK_END_OFFSET 184
#define THREAD_THIS_OFFSET 192
#define THREAD_PREV_OFFSET 200
#define THREAD_NEXT_OFFSET 208
#define THREAD_STATE_WORD_OFFSET 216
#define THREAD_SPROF_DATA_OFFSET 224
#define THREAD_ARENA_OFFSET 232
#define THREAD_TLS_SIZE_OFFSET 240
#define THREAD_CONTROL_FRAME_POINTER_OFFSET 248
#define THREAD_CONTROL_STACK_POINTER_OFFSET 256
#define THREAD_CARD_TABLE_OFFSET 264
#define THREAD_SYMBOL_TLAB_OFFSET 272
#define THREAD_SYS_MIXED_TLAB_OFFSET 296
#define THREAD_SYS_CONS_TLAB_OFFSET 320
#define THREAD_TOT_BYTES_ALLOC_BOXED_OFFSET 344
#define THREAD_TOT_BYTES_ALLOC_UNBOXED_OFFSET 352
#define THREAD_SLOW_PATH_ALLOCS_OFFSET 360
#define THREAD_ET_ALLOCATOR_MUTEX_ACQ_OFFSET 368
#define THREAD_ET_FIND_FREEISH_PAGE_OFFSET 376
#define THREAD_ET_BZEROING_OFFSET 384
#define THREAD_ALLOCATOR_HISTOGRAM_OFFSET 392
#define THREAD_LISP_THREAD_OFFSET 1160
#define THREAD_SIZE 146

#else /* __ASSEMBLER__ */

#include "lispobj.h"
struct thread_instance {
    lispobj header; // = word_0_
    lispobj _layout;
    lispobj _name;
    lispobj _ephemeral_p;
    lispobj uw_primitive_thread;
    lispobj uw_os_thread;
    lispobj uw_control_stack_start;
    lispobj uw_control_stack_end;
    lispobj startup_info;
    lispobj _visible;
    lispobj interruptions;
    lispobj interruptions_lock;
    lispobj uw_max_stw_pause;
    lispobj uw_sum_stw_pause;
    lispobj uw_ct_stw_pauses;
    lispobj result;
    lispobj semaphore;
    lispobj waiting_for;
};
struct lispmutex {
    lispobj header; // = word_0_
    lispobj _layout;
    lispobj uw_state;
    lispobj name;
    lispobj _owner;
};
#include <pthread.h>
#include "gencgc-alloc-region.h"

#define N_HISTOGRAM_BINS_LARGE 32
#define N_HISTOGRAM_BINS_SMALL 32
typedef lispobj size_histogram[2*N_HISTOGRAM_BINS_LARGE+N_HISTOGRAM_BINS_SMALL];

struct thread_state_word {
  // - control_stack_guard_page_protected is referenced from
  //   hand-written assembly code. (grep 'THREAD_STATE_WORD_OFFSET')
  // - sprof_enable is referenced with SAPs.
  //   (grep 'sb-vm:thread-state-word-slot')
  char control_stack_guard_page_protected;
  char sprof_enable; // statistical CPU profiler switch
  char state;
  char user_thread_p; // opposite of lisp's ephemeral-p
  char padding[4];
};
#define INIT_THREAD_REGIONS(x) \
 gc_init_region(&x->boxed_tlab),\
 gc_init_region(&x->cons_tlab),\
 gc_init_region(&x->mixed_tlab),\
 gc_init_region(&x->symbol_tlab),\
 gc_init_region(&x->sys_mixed_tlab),\
 gc_init_region(&x->sys_cons_tlab)

#define HAVE_THREAD_PSEUDO_ATOMIC_BITS_SLOT 1

typedef lispobj pa_bits_t;

extern struct thread *all_threads;
struct thread {
    lispobj no_tls_value_marker;
    lispobj stepping;
    lispobj * binding_stack_pointer;
    lispobj current_catch_block;
    lispobj current_unwind_protect_block;
    pa_bits_t pseudo_atomic_bits;
    lispobj * alien_stack_pointer;
    uword_t * profile_data;
    struct alloc_region boxed_tlab;
    struct alloc_region cons_tlab;
    struct alloc_region mixed_tlab;
    void * os_address;
    pthread_t os_thread;
    lispobj os_kernel_tid;
    lispobj * alien_stack_start;
    lispobj * binding_stack_start;
    lispobj * control_stack_start;
    lispobj * control_stack_end;
    struct thread * this;
    struct thread * prev;
    struct thread * next;
    struct thread_state_word state_word;
    lispobj sprof_data;
    lispobj arena;
    lispobj tls_size;
    lispobj * control_frame_pointer;
    lispobj * control_stack_pointer;
    lispobj card_table;
    struct alloc_region symbol_tlab;
    struct alloc_region sys_mixed_tlab;
    struct alloc_region sys_cons_tlab;
    lispobj tot_bytes_alloc_boxed;
    lispobj tot_bytes_alloc_unboxed;
    lispobj slow_path_allocs;
    lispobj et_allocator_mutex_acq;
    lispobj et_find_freeish_page;
    lispobj et_bzeroing;
    size_histogram allocator_histogram;
    lispobj lisp_thread;
};

#endif /* __ASSEMBLER__ */
#endif
