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
#ifndef SBCL_GENESIS_AVLNODE
#define SBCL_GENESIS_AVLNODE
#ifndef __ASSEMBLER__

#include "lispobj.h"
struct avlnode {
    lispobj header; // = word_0_
    lispobj _layout;
    lispobj left;
    lispobj right;
    lispobj uw_key;
    lispobj data;
};

#endif /* __ASSEMBLER__ */

#endif
