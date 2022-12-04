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
#ifndef SBCL_GENESIS_FUNCALLABLE_INSTANCE
#define SBCL_GENESIS_FUNCALLABLE_INSTANCE
#ifdef __ASSEMBLER__

/* These offsets are SLOT-OFFSET * N-WORD-BYTES - LOWTAG
 * so they work directly on tagged addresses. */

#define FUNCALLABLE_INSTANCE_TRAMPOLINE_OFFSET -3
#define FUNCALLABLE_INSTANCE_LAYOUT_OFFSET 5
#define FUNCALLABLE_INSTANCE_FUNCTION_OFFSET 13
#define FUNCALLABLE_INSTANCE_INFO_OFFSET 21
#define FUNCALLABLE_INSTANCE_SIZE 4

#else /* __ASSEMBLER__ */

#include "lispobj.h"
struct funcallable_instance {
    lispobj header;
    lispobj trampoline;
    lispobj layout;
    lispobj function;
    lispobj info[1];
};

#endif /* __ASSEMBLER__ */
#endif
