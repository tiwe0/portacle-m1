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
#ifndef SBCL_GENESIS_GC_TABLES
#define SBCL_GENESIS_GC_TABLES
#include "lispobj.h"
static inline int specialized_vector_widetag_p(unsigned char widetag) {
  return widetag>=0x85 && (0x03FFFFFAU >> ((widetag-0x80)>>2)) & 1;
}
static inline int leaf_obj_widetag_p(unsigned char widetag) {
  return (0x3FFFFFA08001690LU >> (widetag>>2)) & 1;
}
extern unsigned char widetag_lowtag[256];
static inline lispobj compute_lispobj(lispobj* base_addr) {
  return make_lispobj(base_addr, LOWTAG_FOR_WIDETAG(*base_addr & WIDETAG_MASK));
}

#ifdef WANT_SCAV_TRANS_SIZE_TABLES
unsigned char widetag_lowtag[256] = {
    7,    0,    7,    7,    7,    0,    7,    7,    7,    7,    7,    7,    7,    0,    7,    7,
    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7,    7,    7,    7,    7, 0x8F,    7,    7,
    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,
    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x83,    7,    7,    7, 0x8B,    7,    7,
    7, 0x8B,    7,    7,    7, 0x8B,    7,    7,    7,    0,    7,    7,    7, 0x8F,    7,    7,
    7,    7,    7,    7,    7,    0,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,
    7,    0,    7,    7,    7,    0,    7,    7,    7,    0,    7,    7,    7, 0x80,    7,    7,
    7,    0,    7,    7,    7,    0,    7,    7,    7,    0,    7,    7,    7,    0,    7,    7,
    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,
    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,
    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,
    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,
    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,
    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,
    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,
    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7, 0x8F,    7,    7,    7,    0,    7,    7,
};
sword_t (*const scavtab[256])(lispobj *where, lispobj object) = {
  scav_immediate,                scav_lose,                     scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_lose,                     scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_immediate,                scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_lose,                     scav_immediate,                scav_other_pointer,
  scav_immediate,                scav_bignum,                   scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_boxed,                    scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_immediate,                scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_unboxed,                  scav_immediate,                scav_other_pointer,
  scav_immediate,                scav_boxed,                    scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_unboxed,                  scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_unboxed,                  scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_symbol,                   scav_immediate,                scav_other_pointer,
  scav_immediate,                scav_unboxed,                  scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_code_blob,                scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_instance,                 scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_funinstance,              scav_immediate,                scav_other_pointer,
  scav_immediate,                scav_lose,                     scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_closure,                  scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_lose,                     scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_boxed,                    scav_immediate,                scav_other_pointer,
  scav_immediate,                scav_immediate,                scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_lose,                     scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_weakptr,                  scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_fdefn,                    scav_immediate,                scav_other_pointer,
  scav_immediate,                scav_lose,                     scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_lose,                     scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_lose,                     scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_filler,                   scav_immediate,                scav_other_pointer,
  scav_immediate,                scav_lose,                     scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_lose,                     scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_lose,                     scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_lose,                     scav_immediate,                scav_other_pointer,
  scav_immediate,                scav_array,                    scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_vector_nil,               scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_vector_t,                 scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_vector_bit,               scav_immediate,                scav_other_pointer,
  scav_immediate,                scav_vector_unsigned_byte_2,   scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_vector_unsigned_byte_4,   scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_vector_unsigned_byte_8,   scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_vector_unsigned_byte_8,   scav_immediate,                scav_other_pointer,
  scav_immediate,                scav_vector_unsigned_byte_16,  scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_vector_unsigned_byte_16,  scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_vector_unsigned_byte_32,  scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_vector_unsigned_byte_32,  scav_immediate,                scav_other_pointer,
  scav_immediate,                scav_vector_unsigned_byte_64,  scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_vector_unsigned_byte_64,  scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_vector_unsigned_byte_64,  scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_vector_unsigned_byte_8,   scav_immediate,                scav_other_pointer,
  scav_immediate,                scav_vector_unsigned_byte_16,  scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_vector_unsigned_byte_32,  scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_vector_unsigned_byte_64,  scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_vector_unsigned_byte_64,  scav_immediate,                scav_other_pointer,
  scav_immediate,                scav_vector_unsigned_byte_32,  scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_vector_unsigned_byte_64,  scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_vector_unsigned_byte_64,  scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_vector_unsigned_byte_128, scav_immediate,                scav_other_pointer,
  scav_immediate,                scav_base_string,              scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_vector_unsigned_byte_32,  scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_array,                    scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_array,                    scav_immediate,                scav_other_pointer,
  scav_immediate,                scav_array,                    scav_immediate,                scav_instance_pointer,
  scav_immediate,                scav_array,                    scav_immediate,                scav_list_pointer,
  scav_immediate,                scav_array,                    scav_immediate,                scav_fun_pointer,
  scav_immediate,                scav_lose,                     scav_immediate,                scav_other_pointer,
};
static void (*scav_ptr[4])(lispobj *where, lispobj object)= {
  (void(*)(lispobj*,lispobj))scav_instance_pointer,
  (void(*)(lispobj*,lispobj))scav_list_pointer,
  (void(*)(lispobj*,lispobj))scav_fun_pointer,
  (void(*)(lispobj*,lispobj))scav_other_pointer
};
static lispobj (*transother[64])(lispobj object) = {
  trans_lose,                    trans_lose,                    trans_lose,                    trans_lose,
  trans_bignum,                  trans_ratio_or_complex,        trans_lose,                    trans_unboxed,
  trans_ratio_or_complex,        trans_unboxed,                 trans_unboxed,                 trans_tiny_mixed,
  trans_unboxed,                 trans_code_blob,               trans_lose,                    trans_lose,
  trans_lose,                    trans_lose,                    trans_lose,                    trans_boxed,
  trans_lose,                    trans_lose,                    trans_weakptr,                 trans_fdefn,
  trans_lose,                    trans_lose,                    trans_lose,                    trans_lose,
  trans_lose,                    trans_lose,                    trans_lose,                    trans_lose,
  trans_array,                   trans_vector_nil,              trans_vector_t,                trans_vector_bit,
  trans_vector_unsigned_byte_2,  trans_vector_unsigned_byte_4,  trans_vector_unsigned_byte_8,  trans_vector_unsigned_byte_8,
  trans_vector_unsigned_byte_16, trans_vector_unsigned_byte_16, trans_vector_unsigned_byte_32, trans_vector_unsigned_byte_32,
  trans_vector_unsigned_byte_64, trans_vector_unsigned_byte_64, trans_vector_unsigned_byte_64, trans_vector_unsigned_byte_8,
  trans_vector_unsigned_byte_16, trans_vector_unsigned_byte_32, trans_vector_unsigned_byte_64, trans_vector_unsigned_byte_64,
  trans_vector_unsigned_byte_32, trans_vector_unsigned_byte_64, trans_vector_unsigned_byte_64, trans_vector_unsigned_byte_128,
  trans_base_string,             trans_vector_unsigned_byte_32, trans_array,                   trans_array,
  trans_array,                   trans_array,                   trans_array,                   trans_lose,
};
#define size_pointer (sizerfn)0
#define size_immediate (sizerfn)0
#define size_unboxed size_boxed
sword_t (*sizetab[256])(lispobj *where) = {
  size_immediate,                size_lose,                     size_immediate,                size_pointer,
  size_immediate,                size_lose,                     size_immediate,                size_pointer,
  size_immediate,                size_immediate,                size_immediate,                size_pointer,
  size_immediate,                size_lose,                     size_immediate,                size_pointer,
  size_immediate,                size_bignum,                   size_immediate,                size_pointer,
  size_immediate,                size_boxed,                    size_immediate,                size_pointer,
  size_immediate,                size_immediate,                size_immediate,                size_pointer,
  size_immediate,                size_unboxed,                  size_immediate,                size_pointer,
  size_immediate,                size_boxed,                    size_immediate,                size_pointer,
  size_immediate,                size_unboxed,                  size_immediate,                size_pointer,
  size_immediate,                size_unboxed,                  size_immediate,                size_pointer,
  size_immediate,                size_tiny_boxed,               size_immediate,                size_pointer,
  size_immediate,                size_unboxed,                  size_immediate,                size_pointer,
  size_immediate,                size_code_blob,                size_immediate,                size_pointer,
  size_immediate,                size_instance,                 size_immediate,                size_pointer,
  size_immediate,                size_short_boxed,              size_immediate,                size_pointer,
  size_immediate,                size_lose,                     size_immediate,                size_pointer,
  size_immediate,                size_short_boxed,              size_immediate,                size_pointer,
  size_immediate,                size_lose,                     size_immediate,                size_pointer,
  size_immediate,                size_boxed,                    size_immediate,                size_pointer,
  size_immediate,                size_immediate,                size_immediate,                size_pointer,
  size_immediate,                size_lose,                     size_immediate,                size_pointer,
  size_immediate,                size_weakptr,                  size_immediate,                size_pointer,
  size_immediate,                size_fdefn,                    size_immediate,                size_pointer,
  size_immediate,                size_lose,                     size_immediate,                size_pointer,
  size_immediate,                size_lose,                     size_immediate,                size_pointer,
  size_immediate,                size_lose,                     size_immediate,                size_pointer,
  size_immediate,                size_filler,                   size_immediate,                size_pointer,
  size_immediate,                size_lose,                     size_immediate,                size_pointer,
  size_immediate,                size_lose,                     size_immediate,                size_pointer,
  size_immediate,                size_lose,                     size_immediate,                size_pointer,
  size_immediate,                size_lose,                     size_immediate,                size_pointer,
  size_immediate,                size_array,                    size_immediate,                size_pointer,
  size_immediate,                size_vector_nil,               size_immediate,                size_pointer,
  size_immediate,                size_vector_t,                 size_immediate,                size_pointer,
  size_immediate,                size_vector_bit,               size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_2,   size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_4,   size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_8,   size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_8,   size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_16,  size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_16,  size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_32,  size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_32,  size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_64,  size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_64,  size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_64,  size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_8,   size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_16,  size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_32,  size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_64,  size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_64,  size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_32,  size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_64,  size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_64,  size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_128, size_immediate,                size_pointer,
  size_immediate,                size_base_string,              size_immediate,                size_pointer,
  size_immediate,                size_vector_unsigned_byte_32,  size_immediate,                size_pointer,
  size_immediate,                size_array,                    size_immediate,                size_pointer,
  size_immediate,                size_array,                    size_immediate,                size_pointer,
  size_immediate,                size_array,                    size_immediate,                size_pointer,
  size_immediate,                size_array,                    size_immediate,                size_pointer,
  size_immediate,                size_array,                    size_immediate,                size_pointer,
  size_immediate,                size_lose,                     size_immediate,                size_pointer,
};
#undef size_immediate
#undef size_pointer
#undef size_unboxed
#endif
#endif
