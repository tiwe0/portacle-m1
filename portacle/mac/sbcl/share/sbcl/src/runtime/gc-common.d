gc-common.o gc-common.d : gc-common.c genesis/sbcl.h runtime.h lispobj.h align.h os.h \
  target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h interr.h globals.h interrupt.h genesis/static-symbols.h \
  thread.h genesis/symbol.h genesis/vector.h symbol-tls.inc \
  genesis/thread.h gencgc-alloc-region.h validate.h gc-typedefs.h \
  lispregs.h target-lispregs.h genesis/regnames.h arch.h gc.h \
  gc-assert.h immobile-space.h gencgc-impl.h genesis/cardmarks.h \
  genesis/cons.h genesis/weak-pointer.h hopscotch.h code.h \
  genesis/closure.h forwarding-ptr.inc genesis/primitive-objects.h \
  genesis/number-types.h genesis/fdefn.h genesis/instance.h instance.inc \
  genesis/sap.h genesis/value-cell.h genesis/binding.h \
  genesis/hash-table.h genesis/split-ordered-list.h var-io.h search.h \
  murmur_hash.h incremental-compact.h weak-hash-pred.inc \
  genesis/gc-tables.h sys_mmap.inc
