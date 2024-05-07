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
#ifndef SBCL_GENESIS_VALUE_CELL
#define SBCL_GENESIS_VALUE_CELL
#ifdef __ASSEMBLER__

/* These offsets are SLOT-OFFSET * N-WORD-BYTES - LOWTAG
 * so they work directly on tagged addresses. */

#define VALUE_CELL_VALUE_OFFSET -7
#define VALUE_CELL_SIZE 2

#else /* __ASSEMBLER__ */

#include "lispobj.h"
struct value_cell {
    lispobj header;
    lispobj value;
};

#endif /* __ASSEMBLER__ */
#endif
