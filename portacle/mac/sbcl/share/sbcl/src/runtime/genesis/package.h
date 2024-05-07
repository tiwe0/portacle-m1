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
#ifndef SBCL_GENESIS_PACKAGE
#define SBCL_GENESIS_PACKAGE
#ifndef __ASSEMBLER__

#include "lispobj.h"
struct symbol_table {
    lispobj header; // = word_0_
    lispobj _layout;
    lispobj _cells;
    lispobj modified;
    lispobj package;
    lispobj size;
    lispobj free;
    lispobj deleted;
};

#endif /* __ASSEMBLER__ */

#ifndef __ASSEMBLER__

#include "lispobj.h"
struct package {
    lispobj header; // = word_0_
    lispobj _layout;
    lispobj _name;
    lispobj id;
    lispobj keys;
    lispobj tables;
    lispobj mru_table_index;
    lispobj _used_by;
    lispobj internal_symbols;
    lispobj external_symbols;
    lispobj _shadowing_symbols;
    lispobj doc_string;
    lispobj _bits;
    lispobj _implementation_packages;
    lispobj _local_nicknames;
    lispobj source_location;
};

#endif /* __ASSEMBLER__ */

#endif
