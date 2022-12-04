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
#ifndef SBCL_GENESIS_CONFIG
#define SBCL_GENESIS_CONFIG
#define LISP_FEATURE_64_BIT
#define LISP_FEATURE_ALIEN_CALLBACKS
#define LISP_FEATURE_ANSI_CL
#define LISP_FEATURE_ANSI_COMPLIANT_LOAD_TRUENAME
#define LISP_FEATURE_ARM64
#define LISP_FEATURE_BSD
#define LISP_FEATURE_CALL_SYMBOL
#define LISP_FEATURE_COMMON_LISP
#define LISP_FEATURE_COMPACT_SYMBOL
#define LISP_FEATURE_COMPARE_AND_SWAP_VOPS
#define LISP_FEATURE_DARWIN
#define LISP_FEATURE_DARWIN_JIT
#define LISP_FEATURE_FP_AND_PC_STANDARD_SAVE
#define LISP_FEATURE_GCC_TLS
#define LISP_FEATURE_GENCGC
#define LISP_FEATURE_IEEE_FLOATING_POINT
#define LISP_FEATURE_LITTLE_ENDIAN
#define LISP_FEATURE_MACH_O
#define LISP_FEATURE_NO_CONTINUE_UNWIND
#define LISP_FEATURE_OS_PROVIDES_BLKSIZE_T
#define LISP_FEATURE_OS_PROVIDES_DLADDR
#define LISP_FEATURE_OS_PROVIDES_DLOPEN
#define LISP_FEATURE_OS_PROVIDES_SUSECONDS_T
#define LISP_FEATURE_OS_THREAD_STACK
#define LISP_FEATURE_PACKAGE_LOCAL_NICKNAMES
#define LISP_FEATURE_PAUSELESS_THREADSTART
#define LISP_FEATURE_ROUND_FLOAT
#define LISP_FEATURE_SBCL
#define LISP_FEATURE_SB_CORE_COMPRESSION
#define LISP_FEATURE_SB_DOC
#define LISP_FEATURE_SB_EVAL
#define LISP_FEATURE_SB_PACKAGE_LOCKS
#define LISP_FEATURE_SB_SOURCE_LOCATIONS
#define LISP_FEATURE_SB_THREAD
#define LISP_FEATURE_SB_UNICODE
#define LISP_FEATURE_UNBIND_IN_UNWIND
#define LISP_FEATURE_UNDEFINED_FUN_RESTARTS
#define LISP_FEATURE_UNIX
#define LISP_FEATURE_UNWIND_TO_FRAME_AND_CALL_VOP
#define LISP_FEATURE_USE_CONS_REGION

#define SBCL_TARGET_ARCHITECTURE_STRING "arm64"
#define SBCL_VERSION_STRING "2.2.6.0.HEAD.1-4b8ada2"
#define CORE_MAGIC 0x5342434C
#ifndef __ASSEMBLER__

#define LISPOBJ(x) ((lispobj)x)

#else /* __ASSEMBLER__ */

#define LISPOBJ(thing) thing

#endif /* __ASSEMBLER__ */


#endif
