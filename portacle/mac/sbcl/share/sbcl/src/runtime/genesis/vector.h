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
#ifndef SBCL_GENESIS_VECTOR
#define SBCL_GENESIS_VECTOR
#ifdef __ASSEMBLER__

/* These offsets are SLOT-OFFSET * N-WORD-BYTES - LOWTAG
 * so they work directly on tagged addresses. */

#define VECTOR_LENGTH_OFFSET -7
#define VECTOR_DATA_OFFSET 1
#define VECTOR_SIZE 2

#else /* __ASSEMBLER__ */

#include "lispobj.h"
struct vector {
    lispobj header;
    lispobj length_;
    uword_t data[1];
};
struct array {
    lispobj header;
    lispobj fill_pointer;
    lispobj elements;
    lispobj data;
    lispobj displacement;
    lispobj displaced_p;
    lispobj displaced_from;
    lispobj dimensions[1];
};
static inline sword_t vector_len(struct vector* v) {  return v->length_ >> 1; }
static inline struct vector* VECTOR(lispobj obj) {
  return (struct vector*)(obj - 15);
}
static inline char* vector_sap(lispobj v) { return (char*)VECTOR(v)->data; }
static inline unsigned int schar(struct vector* string, int index) {
    return (widetag_of(&string->header) == SIMPLE_BASE_STRING_WIDETAG) ?
      ((unsigned char*)string->data)[index] :
      ((unsigned int*)string->data)[index];
}

#endif /* __ASSEMBLER__ */
#endif
