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
#ifndef SBCL_GENESIS_CARDMARKS
#define SBCL_GENESIS_CARDMARKS
#include "lispobj.h"
extern unsigned char *gc_card_mark;

/* SIMD-within-a-register algorithms
 *
 * from https://graphics.stanford.edu/~seander/bithacks.html
 */
static inline uword_t word_haszero(uword_t word) {
  return ((word - 0x0101010101010101LL) & ~word & 0x8080808080808080LL) != 0;
}
static inline uword_t word_has_stickymark(uword_t word) {
  return word_haszero(word ^ 0x0202020202020202LL);
}
static inline int cardseq_all_marked_nonsticky(long card) {
    uword_t* mark = (uword_t*)&gc_card_mark[card];
    return (mark[0] | mark[1] | mark[2] | mark[3]) == 0;
}
static inline int cardseq_any_marked(long card) {
    uword_t* mark = (uword_t*)&gc_card_mark[card];
    return (mark[0] & mark[1] & mark[2] & mark[3]) != (uword_t)-1;
}
static inline int cardseq_any_sticky_mark(long card) {
    uword_t* mark = (uword_t*)&gc_card_mark[card];
    return word_has_stickymark(mark[0]) || word_has_stickymark(mark[1]) || word_has_stickymark(mark[2]) || word_has_stickymark(mark[3]);
}
#endif
