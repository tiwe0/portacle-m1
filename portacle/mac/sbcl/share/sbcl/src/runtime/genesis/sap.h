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
#ifndef SBCL_GENESIS_SAP
#define SBCL_GENESIS_SAP
#ifdef __ASSEMBLER__

/* These offsets are SLOT-OFFSET * N-WORD-BYTES - LOWTAG
 * so they work directly on tagged addresses. */

#define SAP_POINTER_OFFSET -7
#define SAP_SIZE 2

#else /* __ASSEMBLER__ */

#include "lispobj.h"
struct sap {
    lispobj header;
    char * pointer;
};

#define DX_ALLOC_SAP(var_name, ptr)                                 \
lispobj var_name;                                                   \
struct sap _dx_##var_name __attribute__ ((aligned (16)));           \
do {                                                                \
    _dx_##var_name.header = (1 << 8) | SAP_WIDETAG;                 \
    _dx_##var_name.pointer = (char *)(ptr);                         \
    var_name = make_lispobj(&_dx_##var_name, OTHER_POINTER_LOWTAG); \
} while (0)

#endif /* __ASSEMBLER__ */
#endif
