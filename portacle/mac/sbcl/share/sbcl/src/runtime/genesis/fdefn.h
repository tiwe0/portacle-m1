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
#ifndef SBCL_GENESIS_FDEFN
#define SBCL_GENESIS_FDEFN
#ifdef __ASSEMBLER__

/* These offsets are SLOT-OFFSET * N-WORD-BYTES - LOWTAG
 * so they work directly on tagged addresses. */

#define FDEFN_NAME_OFFSET -7
#define FDEFN_FUN_OFFSET 1
#define FDEFN_RAW_ADDR_OFFSET 9
#define FDEFN_SIZE 4

#else /* __ASSEMBLER__ */

#include "lispobj.h"
struct fdefn {
    lispobj header;
    lispobj name;
    lispobj fun;
    char * raw_addr;
};
static inline struct fdefn* FDEFN(lispobj obj) {
  return (struct fdefn*)(obj - 15);
}
#define StaticSymbolFunction(x) FdefnFun(x##_FDEFN)
/* Return 'fun' given a tagged pointer to an fdefn. */
static inline lispobj FdefnFun(lispobj fdefn) { return FDEFN(fdefn)->fun; }
extern lispobj decode_fdefn_rawfun(struct fdefn *fdefn);

#endif /* __ASSEMBLER__ */
#endif
