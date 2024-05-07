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
#ifndef SBCL_GENESIS_NUMBER_TYPES
#define SBCL_GENESIS_NUMBER_TYPES
#include "lispobj.h"
struct bignum {
    lispobj header;
    sword_t digits[1];
};
struct ratio {
    lispobj header;
    lispobj numerator;
    lispobj denominator;
};
struct double_float {
    lispobj header;
    double value;
};
struct complex {
    lispobj header;
    lispobj real;
    lispobj imag;
};
struct complex_single_float {
    lispobj header;
    struct { float data[2]; }  data;
};
struct complex_double_float {
    lispobj header;
    lispobj filler;
    double real;
    double imag;
};
#endif
