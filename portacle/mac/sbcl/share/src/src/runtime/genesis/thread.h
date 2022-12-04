/*
 * This is a machine-generated file. Please do not edit it by hand.
 * (As of sbcl-0.8.14, it came from WRITE-CONFIG-H in genesis.lisp.)
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
#define THREAD_TLS_SIZE_OFFSET 232
#define THREAD_CONTROL_FRAME_POINTER_OFFSET 240
#define THREAD_CONTROL_STACK_POINTER_OFFSET 248
#define THREAD_TOT_BYTES_ALLOC_BOXED_OFFSET 256
#define THREAD_TOT_BYTES_ALLOC_UNBOXED_OFFSET 264
#define THREAD_SLOW_PATH_ALLOCS_OFFSET 272
#define THREAD_ET_ALLOCATOR_MUTEX_ACQ_OFFSET 280
#define THREAD_ET_FIND_FREEISH_PAGE_OFFSET 288
#define THREAD_ET_BZEROING_OFFSET 296
#define THREAD_OBJ_SIZE_HISTO_OFFSET 304
#define THREAD_LISP_THREAD_OFFSET 1072
#define THREAD_SIZE 135

#else /* __ASSEMBLER__ */

#include "lispobj.h"
#define HAVE_THREAD_PSEUDO_ATOMIC_BITS_SLOT 1

typedef lispobj pa_bits_t;

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
    lispobj tls_size;
    lispobj * control_frame_pointer;
    lispobj * control_stack_pointer;
    lispobj tot_bytes_alloc_boxed;
    lispobj tot_bytes_alloc_unboxed;
    lispobj slow_path_allocs;
    lispobj et_allocator_mutex_acq;
    lispobj et_find_freeish_page;
    lispobj et_bzeroing;
    size_histogram obj_size_histo;
    lispobj lisp_thread;
};

#endif /* __ASSEMBLER__ */
#endif
