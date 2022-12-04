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

#endif /* __ASSEMBLER__ */
#endif
