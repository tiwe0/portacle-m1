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
#ifndef SBCL_GENESIS_LAYOUT
#define SBCL_GENESIS_LAYOUT
#ifndef __ASSEMBLER__

#include "lispobj.h"
struct layout {
    lispobj header; // = word_0_
    lispobj _layout;
    lispobj sw_flags;
    lispobj clos_hash;
    lispobj classoid;
    lispobj invalid;
    lispobj inherits;
    lispobj _info;
    lispobj equalp_impl;
    lispobj slot_table;
    lispobj uw_id_word0;
    lispobj uw_id_word1;
    lispobj uw_id_word2;
};

#endif /* __ASSEMBLER__ */

static inline struct layout* LAYOUT(lispobj obj) {
  return (struct layout*)(obj - 3);
}
#endif
