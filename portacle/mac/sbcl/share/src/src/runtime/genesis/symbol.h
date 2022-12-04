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
#ifndef SBCL_GENESIS_SYMBOL
#define SBCL_GENESIS_SYMBOL
#ifdef __ASSEMBLER__

/* These offsets are SLOT-OFFSET * N-WORD-BYTES - LOWTAG
 * so they work directly on tagged addresses. */

#define SYMBOL_HASH_OFFSET -7
#define SYMBOL_VALUE_OFFSET 1
#define SYMBOL_INFO_OFFSET 9
#define SYMBOL_NAME_OFFSET 17
#define SYMBOL_FDEFN_OFFSET 25
#define SYMBOL_SIZE 6

#else /* __ASSEMBLER__ */

#include "lispobj.h"
struct symbol {
    lispobj header;
    lispobj hash;
    lispobj value;
    lispobj info;
    lispobj name;
    lispobj fdefn;
};

lispobj symbol_function(struct symbol* symbol);
#include "genesis/vector.h"
struct vector *symbol_name(struct symbol*);

lispobj symbol_package(struct symbol*);
static inline int symbol_package_id(struct symbol* s) { return s->name >> 48; }
#define decode_symbol_name(ptr) (ptr & (uword_t)0xFFFFFFFFFFFF)
static inline void set_symbol_name(struct symbol*s, lispobj name) {
  s->name = (s->name & (uword_t)0xFFFF000000000000) | name;
}
static inline struct symbol* SYMBOL(lispobj obj) {
  return (struct symbol*)(obj - 15);
}

#endif /* __ASSEMBLER__ */
#endif
