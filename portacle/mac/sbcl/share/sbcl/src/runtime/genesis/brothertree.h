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
#ifndef SBCL_GENESIS_BROTHERTREE
#define SBCL_GENESIS_BROTHERTREE
#ifndef __ASSEMBLER__

#include "lispobj.h"
struct unary_node {
    lispobj header; // = word_0_
    lispobj _layout;
    lispobj child;
};

#endif /* __ASSEMBLER__ */

#ifndef __ASSEMBLER__

#include "lispobj.h"
struct binary_node {
    lispobj header; // = word_0_
    lispobj _layout;
    lispobj uw_key;
    lispobj _left;
    lispobj _right;
};

#endif /* __ASSEMBLER__ */

extern uword_t brothertree_find_lesseql(uword_t key, lispobj tree);
#endif
