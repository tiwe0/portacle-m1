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
#ifndef SBCL_GENESIS_WEAK_POINTER
#define SBCL_GENESIS_WEAK_POINTER
#ifdef __ASSEMBLER__

/* These offsets are SLOT-OFFSET * N-WORD-BYTES - LOWTAG
 * so they work directly on tagged addresses. */

#define WEAK_POINTER_VALUE_OFFSET -7
#define WEAK_POINTER_SIZE 2

#else /* __ASSEMBLER__ */

#include "lispobj.h"
struct weak_pointer {
    lispobj header;
    lispobj value;
};
extern struct weak_pointer *weak_pointer_chain;
static inline int weakptr_vectorp(struct weak_pointer* wp) { return !(wp->header & 0x100); }
static inline void set_weak_pointer_next(struct weak_pointer *wp, void *next) {
    wp->header = ((uword_t)next << 16) | (wp->header & 0xffff);
}
static inline struct weak_pointer *get_weak_pointer_next(struct weak_pointer *wp) {
    // extract a 48-bit pointer from the header
    return (void*)(wp->header >> 16);
}
#define WEAK_POINTER_CHAIN_END (void*)(intptr_t)1
#define reset_weak_pointer_next(wp) set_weak_pointer_next(wp,0)
#define in_weak_pointer_list(wp) (get_weak_pointer_next(wp)!=0)

#endif /* __ASSEMBLER__ */
#endif
