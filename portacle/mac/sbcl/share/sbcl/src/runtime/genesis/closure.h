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
#ifndef SBCL_GENESIS_CLOSURE
#define SBCL_GENESIS_CLOSURE
#ifdef __ASSEMBLER__

/* These offsets are SLOT-OFFSET * N-WORD-BYTES - LOWTAG
 * so they work directly on tagged addresses. */

#define CLOSURE_FUN_OFFSET -3
#define CLOSURE_INFO_OFFSET 5
#define CLOSURE_SIZE 2

#else /* __ASSEMBLER__ */

#include "lispobj.h"
struct closure {
    lispobj header;
    lispobj fun;
    lispobj info[1];
};

#endif /* __ASSEMBLER__ */
#ifdef __ASSEMBLER__

/* These offsets are SLOT-OFFSET * N-WORD-BYTES - LOWTAG
 * so they work directly on tagged addresses. */

#define SIMPLE_FUN_SELF_OFFSET -3
#define SIMPLE_FUN_INSTS_OFFSET 5
#define SIMPLE_FUN_SIZE 2

#else /* __ASSEMBLER__ */

#include "lispobj.h"
struct simple_fun {
    lispobj header;
    lispobj self;
    unsigned char insts[1];
};

#endif /* __ASSEMBLER__ */
#ifdef __ASSEMBLER__

/* These offsets are SLOT-OFFSET * N-WORD-BYTES - LOWTAG
 * so they work directly on tagged addresses. */

#define CODE_BOXED_SIZE_OFFSET -7
#define CODE_FIXUPS_OFFSET 1
#define CODE_DEBUG_INFO_OFFSET 9
#define CODE_CONSTANTS_OFFSET 17
#define CODE_SIZE 4

#else /* __ASSEMBLER__ */

#include "lispobj.h"
struct code {
    lispobj header;
    lispobj boxed_size;
    lispobj fixups;
    lispobj debug_info;
    lispobj constants[1];
};
#define CODE_SLOTS_PER_SIMPLE_FUN 4
static inline struct code* fun_code_header(struct simple_fun* fun) {
  return (struct code*)((lispobj*)fun - ((uint32_t)fun->header >> 8));
}
static inline struct simple_fun* FUNCTION(lispobj obj) {
  return (struct simple_fun*)(obj - 11);
}

#endif /* __ASSEMBLER__ */
#endif
