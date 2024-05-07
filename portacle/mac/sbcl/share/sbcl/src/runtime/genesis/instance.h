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
#ifndef SBCL_GENESIS_INSTANCE
#define SBCL_GENESIS_INSTANCE
#ifdef __ASSEMBLER__

/* These offsets are SLOT-OFFSET * N-WORD-BYTES - LOWTAG
 * so they work directly on tagged addresses. */

#define INSTANCE_SLOTS_OFFSET 5
#define INSTANCE_SIZE 1

#else /* __ASSEMBLER__ */

#include "lispobj.h"
struct instance {
    lispobj header;
    lispobj slots[1];
};
static inline struct instance* INSTANCE(lispobj obj) {
  return (struct instance*)(obj - 3);
}

#endif /* __ASSEMBLER__ */
#ifdef __ASSEMBLER__

/* These offsets are SLOT-OFFSET * N-WORD-BYTES - LOWTAG
 * so they work directly on tagged addresses. */

#define FUNCALLABLE_INSTANCE_TRAMPOLINE_OFFSET -3
#define FUNCALLABLE_INSTANCE_FUNCTION_OFFSET 5
#define FUNCALLABLE_INSTANCE_LAYOUT_OFFSET 13
#define FUNCALLABLE_INSTANCE_INFO_OFFSET 21
#define FUNCALLABLE_INSTANCE_SIZE 4

#else /* __ASSEMBLER__ */

#include "lispobj.h"
struct funcallable_instance {
    lispobj header;
    lispobj trampoline;
    lispobj function;
    lispobj layout;
    lispobj info[1];
};

#endif /* __ASSEMBLER__ */

#define LAYOUT_LAYOUT_ID 3
#define HASHSET_LAYOUT_ID -125
#define HASHSET_STORAGE_LAYOUT_ID -124
#define LFLIST_NODE_LAYOUT_ID 4
#define FINALIZER_NODE_LAYOUT_ID -121
#define BROTHERTREE_UNARY_NODE_LAYOUT_ID 5
#define PACKAGE_LAYOUT_ID -126
#define HASH_TABLE_LAYOUT_ID -127

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
    lispobj slot_mapper;
    lispobj slot_table;
    lispobj uw_id_word0;
    lispobj uw_id_word1;
    lispobj uw_id_word2;
};

#endif /* __ASSEMBLER__ */

static inline struct layout* LAYOUT(lispobj obj) {
  return (struct layout*)(obj - 3);
}
#include "instance.inc"
#endif
