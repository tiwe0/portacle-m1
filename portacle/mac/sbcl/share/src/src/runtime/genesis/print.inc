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
static void (*print_fns[])(lispobj obj) = {
 print_fixnum, print_otherimm, print_fixnum, print_struct,
 print_fixnum, print_otherimm, print_fixnum, print_list,
 print_fixnum, print_otherimm, print_fixnum, print_fun_or_otherptr,
 print_fixnum, print_otherimm, print_fixnum, print_fun_or_otherptr
};
static void (*brief_fns[])(lispobj obj) = {
 brief_fixnum, brief_otherimm, brief_fixnum, brief_struct,
 brief_fixnum, brief_otherimm, brief_fixnum, brief_list,
 brief_fixnum, brief_otherimm, brief_fixnum, brief_fun_or_otherptr,
 brief_fixnum, brief_otherimm, brief_fixnum, brief_fun_or_otherptr
};
