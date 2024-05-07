#include "interr.h"
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    extern int initialize_lisp(int argc, char *argv[], char *envp[]);
#ifdef TRACE_MMAP_SYSCALLS
    extern FILE* mmgr_debug_logfile;
    mmgr_debug_logfile = fopen("mman.log", "w");
#endif
    initialize_lisp(argc, argv, envp);
    lose("unexpected return from initial thread in main()");
    return 0;
}
