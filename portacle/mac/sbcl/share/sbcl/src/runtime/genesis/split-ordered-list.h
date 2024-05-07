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
#ifndef SBCL_GENESIS_SPLIT_ORDERED_LIST
#define SBCL_GENESIS_SPLIT_ORDERED_LIST
#ifndef __ASSEMBLER__

#include "lispobj.h"
struct split_ordered_list {
    lispobj header; // = word_0_
    lispobj _layout;
    lispobj head;
    lispobj inserter;
    lispobj deleter;
    lispobj finder;
    lispobj inequality;
    lispobj equality;
    lispobj uw_count;
    lispobj uw_threshold;
    lispobj hashfun;
    lispobj bins;
    lispobj elts_per_bin;
    lispobj valuesp;
};

struct list_node {
    lispobj header; // = word_0_
    lispobj _layout;
    lispobj _node_next;
};

struct solist_node {
    lispobj header; // = word_0_
    lispobj _layout;
    lispobj _node_next;
    lispobj node_hash;
    lispobj so_key;
    lispobj so_data;
};
static inline int so_dummy_node_p(struct solist_node* n) {
    return !(n->node_hash & 2);
}

#endif /* __ASSEMBLER__ */

#endif
