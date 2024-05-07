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
#ifndef SBCL_GENESIS_TAGNAMES
#define SBCL_GENESIS_TAGNAMES
#include <stddef.h>

static const char *lowtag_names[] = {
    "even fixnum",
    "other immediate 0",
    "pad0",
    "instance pointer",
    "pad1",
    "other immediate 1",
    "pad2",
    "list pointer",
    "odd fixnum",
    "other immediate 2",
    "pad3",
    "fun pointer",
    "pad4",
    "other immediate 3",
    "pad5",
    "other pointer"
};

const char *widetag_names[] = {
    "unknown [0]",
    "unknown [1]",
    "unbound-marker",
    "unknown [3]",
    "bignum",
    "ratio",
    "sfloat",
    "dfloat",
    "cplxnum",
    "cplx-sfloat",
    "cplx-dfloat",
    "symbol",
    "sap",
    "codeblob",
    "instance",
    "funinstance",
    "simplefun",
    "closure",
    "unknown [18]",
    "value-cell",
    "char",
    "unknown [21]",
    "weakptr",
    "fdefn",
    "unknown [24]",
    "unknown [25]",
    "unknown [26]",
    "filler",
    "unknown [28]",
    "unknown [29]",
    "unknown [30]",
    "unknown [31]",
    "simple-array",
    "simple-array-NIL",
    "simple-vec",
    "simple-bit-vec",
    "UB2-vec",
    "UB4-vec",
    "UB7-vec",
    "UB8-vec",
    "UB15-vec",
    "UB16-vec",
    "UB31-vec",
    "UB32-vec",
    "Ufixnum-vec",
    "UB63-vec",
    "UB64-vec",
    "SB8-vec",
    "SB16-vec",
    "SB32-vec",
    "fixnum-vec",
    "SB64-vec",
    "sfloat-vec",
    "dfloat-vec",
    "cplx-sfloat-vec",
    "cplx-dfloat-vec",
    "simple-base-str",
    "simple-char-str",
    "fancy-base-str",
    "fancy-char-str",
    "fancy-bit-vec",
    "fancy-vec",
    "fancy-array",
    "unknown [63]"
};
static char *symbol_slots[] = {
 "hash: ", "value: ", "fdefn: ", "info: ", "name: ", NULL
};
static char *ratio_slots[] = {
 "numerator: ", "denominator: ", NULL
};
static char *complex_slots[] = {
 "real: ", "imag: ", NULL
};
static char *code_slots[] = {
 "boxed_size: ", "fixups: ", "debug_info: ", NULL
};
static char *simple_fun_slots[] = {
 "self: ", NULL
};
static char *closure_slots[] = {
 "fun: ", NULL
};
static char *funcallable_instance_slots[] = {
 "trampoline: ", "function: ", "layout: ", NULL
};
static char *weak_pointer_slots[] = {
 "value: ", NULL
};
static char *fdefn_slots[] = {
 "name: ", "fun: ", "raw_addr: ", NULL
};
static char *value_cell_slots[] = {
 "value: ", NULL
};
#endif
