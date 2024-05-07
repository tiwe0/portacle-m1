#ifndef _X86_SOLARIS_OS_H
#define _X86_SOLARIS_OS_H

typedef ucontext_t os_context_t;
typedef int os_context_register_t;

#include "arch-os-generic.inc"

#define OS_CONTEXT_PC(contex) context->uc_mcontext.gregs[14] /* REG_EIP */

#endif /* _X86_SOLARIS_OS_H */
