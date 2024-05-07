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
#ifndef SBCL_GENESIS_COMPILED_DEBUG_INFO
#define SBCL_GENESIS_COMPILED_DEBUG_INFO
#ifndef __ASSEMBLER__

#include "lispobj.h"
struct compiled_debug_fun {
    lispobj header; // = word_0_
    lispobj _layout;
    lispobj name;
    lispobj vars;
    lispobj blocks;
    lispobj tlf_number;
    lispobj arguments;
    lispobj returns;
    lispobj encoded_locs;
    lispobj next;
};

#endif /* __ASSEMBLER__ */

#ifndef __ASSEMBLER__

#include "lispobj.h"
struct compiled_debug_info {
    lispobj header; // = word_0_
    lispobj _layout;
    lispobj name;
    lispobj source;
    lispobj package;
    lispobj fun_map;
    lispobj contexts;
    lispobj memo_cell;
};

#endif /* __ASSEMBLER__ */

#endif
