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
#ifndef SBCL_GENESIS_HASH_TABLE
#define SBCL_GENESIS_HASH_TABLE
#ifndef __ASSEMBLER__

#include "lispobj.h"
struct hash_table {
    lispobj header; // = word_0_
    lispobj _layout;
    lispobj gethash_impl;
    lispobj puthash_impl;
    lispobj remhash_impl;
    lispobj clrhash_impl;
    lispobj pairs;
    lispobj cache;
    lispobj index_vector;
    lispobj next_vector;
    lispobj hash_vector;
    lispobj uw_flags;
    lispobj _lock;
    lispobj test_fun;
    lispobj hash_fun;
    lispobj test;
    lispobj rehash_size;
    lispobj word_17_; // rehash_threshold
    lispobj _count;
    lispobj next_free_kv;
    lispobj smashed_cells;
    struct hash_table* next_weak_hash_table;
};

static inline int hashtable_kind(struct hash_table* ht) { return (ht->uw_flags >> 4) & 3; }
static inline int hashtable_weakp(struct hash_table* ht) { return ht->uw_flags & 8; }
static inline int hashtable_weakness(struct hash_table* ht) { return ht->uw_flags >> 6; }
#define HASHTABLE_KIND_EQL 1

#endif /* __ASSEMBLER__ */

#endif
