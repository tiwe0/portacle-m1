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
#ifndef SBCL_GENESIS_BINDING
#define SBCL_GENESIS_BINDING
#ifdef __ASSEMBLER__

/* These offsets are SLOT-OFFSET * N-WORD-BYTES - LOWTAG
 * so they work directly on tagged addresses. */

#define BINDING_VALUE_OFFSET 0
#define BINDING_SYMBOL_OFFSET 8
#define BINDING_SIZE 2

#else /* __ASSEMBLER__ */

#include "lispobj.h"
struct binding {
    lispobj value;
    lispobj symbol;
};

#endif /* __ASSEMBLER__ */
#endif