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
#ifndef SBCL_GENESIS_ARENA
#define SBCL_GENESIS_ARENA
#ifndef __ASSEMBLER__

#include "lispobj.h"
struct arena {
    lispobj header; // = word_0_
    lispobj _layout;
    lispobj uw_current_block;
    lispobj uw_first_block;
    lispobj uw_huge_objects;
    lispobj uw_original_size;
    lispobj uw_growth_amount;
    lispobj uw_size_limit;
    lispobj uw_length;
    lispobj uw_bytes_wasted;
    lispobj index;
    lispobj hidden;
    lispobj uw_token;
    lispobj userdata;
    lispobj link;
};

#endif /* __ASSEMBLER__ */

#endif
