/*
 * memory validation
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

#include <stdio.h>
#include <stdlib.h>

#include "genesis/sbcl.h"
#include "runtime.h"
#include "os.h"
#include "globals.h"
#include "interr.h"
#include "validate.h"
#include "interr.h"                     /* for declaration of lose */

#ifdef LISP_FEATURE_CHENEYGC
uword_t DYNAMIC_0_SPACE_START, DYNAMIC_1_SPACE_START;
#else
uword_t DYNAMIC_SPACE_START;
#endif
uword_t READ_ONLY_SPACE_START, READ_ONLY_SPACE_END;
#ifdef LISP_FEATURE_RELOCATABLE_STATIC_SPACE
uword_t STATIC_SPACE_START, STATIC_SPACE_END;
#endif

uword_t asm_routines_start, asm_routines_end;

// Return the ALLOCATE_LOW flag or 0 for the hardwired spaces
// depending on the backend.  Why specify the ALLOCATE_LOW on a non-relocatable
// mapping? To make the OS tell us an address that it would have been ok with,
// as well as our code being ok with. Otherwise, we see unhelpful output:
//  "mmap: wanted 1048576 bytes at 0x50000000, actually mapped at 0x7f75b1f6b000"
// which could never work as the base of static space on x86-64.
// Care is needed because not all backends put the small spaces below 2GB.
// In particular, arm64 has #xF0000000 which is above 2GB but below 4GB.
// The ALLOCATE_LOW flag means that the limit is 2GB.
// (See MAP_32BIT in http://man7.org/linux/man-pages/man2/mmap.2.html)
static const int should_allocate_low =
#ifdef LISP_FEATURE_X86_64
    ALLOCATE_LOW;
#else
    0;
#endif

os_vm_address_t undefined_alien_address = 0;
/* As contrasted with the useless os_vm_page_size which is identical to
 * the constant BACKEND_PAGE_BYTES that we define for various other purposes
 * such as core file loading and generational GC,
 * this is the number the OS tells us */
int os_reported_page_size;

#ifdef LISP_FEATURE_WIN32
#include <sysinfoapi.h>
#endif

static void
ensure_undefined_alien(void) {
#ifdef LISP_FEATURE_WIN32
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    os_reported_page_size = info.dwPageSize;
#else
    os_reported_page_size = getpagesize();
#endif
    os_vm_address_t start =
        os_alloc_gc_space(0, MOVABLE|IS_GUARD_PAGE, NULL, os_reported_page_size);
    if (start) {
        undefined_alien_address = start;
    } else {
        lose("could not allocate guard page for undefined alien");
    }
}

bool allocate_hardwired_spaces(bool hard_failp)
{
    struct {
        uword_t start;
        unsigned size;
        int id;
    } preinit_spaces[] = {
        { READ_ONLY_SPACE_START, READ_ONLY_SPACE_SIZE, READ_ONLY_CORE_SPACE_ID },
#ifndef LISP_FEATURE_IMMOBILE_SPACE
        { ALIEN_LINKAGE_TABLE_SPACE_START, ALIEN_LINKAGE_TABLE_SPACE_SIZE, ALIEN_LINKAGE_TABLE_CORE_SPACE_ID },
#endif
        { STATIC_SPACE_START, STATIC_SPACE_SIZE, STATIC_CORE_SPACE_ID },
#ifdef LISP_FEATURE_DARWIN_JIT
        { STATIC_CODE_SPACE_START, STATIC_CODE_SPACE_SIZE, STATIC_CODE_CORE_SPACE_ID },
#endif
    };
    int i;
    int n_spaces = sizeof preinit_spaces / sizeof preinit_spaces[0];
    for (i = 0; i< n_spaces; ++i) {
        if (!preinit_spaces[i].size) continue;
        if (os_alloc_gc_space(preinit_spaces[i].id,
                              NOT_MOVABLE | should_allocate_low,
                              (os_vm_address_t)preinit_spaces[i].start,
                              preinit_spaces[i].size)) continue;
        if (!hard_failp) return 0; // soft fail. Try again after disabling ASLR
        fprintf(stderr,
                "failed to allocate %lu bytes at %p\n",
                (long unsigned)preinit_spaces[i].size, (void*)preinit_spaces[i].start);
        fprintf(stderr,
                "(hint: Try \"ulimit -a\"; maybe you should increase memory limits.)\n");
        exit(1);
    }
    return 1;
}

void
allocate_lisp_dynamic_space(bool did_preinit)
{
    // Small spaces can be allocated after large spaces are.
    // The above code is only utilized when heap relocation is disabled.
    // And when so, failure to allocate dynamic space is fatal.
    if (!did_preinit)
      allocate_hardwired_spaces(1);

#ifdef LISP_FEATURE_OS_PROVIDES_DLOPEN
    ensure_undefined_alien();
#endif
}

static inline void
protect_guard_page(void *page, int protect_p, os_vm_prot_t flags) {
    os_protect(page, os_vm_page_size, protect_p ?
               flags : OS_VM_PROT_READ | OS_VM_PROT_WRITE);
}

#define DEF_PROTECT_PAGE(name,page_name,flags)                          \
    void                                                                \
    protect_##name(int protect_p, struct thread *thread) {              \
        if (!thread)                                                    \
            thread = get_sb_vm_thread();                      \
        protect_guard_page(page_name(thread), protect_p, flags);        \
    }

#ifndef LISP_FEATURE_WIN32
DEF_PROTECT_PAGE(control_stack_hard_guard_page,
                 CONTROL_STACK_HARD_GUARD_PAGE,
                 OS_VM_PROT_NONE)
DEF_PROTECT_PAGE(control_stack_guard_page,
                 CONTROL_STACK_GUARD_PAGE, OS_VM_PROT_READ)
DEF_PROTECT_PAGE(control_stack_return_guard_page,
                 CONTROL_STACK_RETURN_GUARD_PAGE, OS_VM_PROT_READ)
#endif

DEF_PROTECT_PAGE(binding_stack_hard_guard_page,
                 BINDING_STACK_HARD_GUARD_PAGE,
                 OS_VM_PROT_NONE)
DEF_PROTECT_PAGE(binding_stack_guard_page,
                 BINDING_STACK_GUARD_PAGE,
                 OS_VM_PROT_NONE)
DEF_PROTECT_PAGE(binding_stack_return_guard_page,
                 BINDING_STACK_RETURN_GUARD_PAGE,
                 OS_VM_PROT_NONE)

DEF_PROTECT_PAGE(alien_stack_hard_guard_page,
                 ALIEN_STACK_HARD_GUARD_PAGE,
                 OS_VM_PROT_NONE)
DEF_PROTECT_PAGE(alien_stack_guard_page,
                 ALIEN_STACK_GUARD_PAGE,
                 OS_VM_PROT_NONE)
DEF_PROTECT_PAGE(alien_stack_return_guard_page,
                 ALIEN_STACK_RETURN_GUARD_PAGE,
                 OS_VM_PROT_NONE)
