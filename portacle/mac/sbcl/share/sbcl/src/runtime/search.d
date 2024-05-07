search.o search.d : search.c genesis/sbcl.h interr.h os.h runtime.h lispobj.h \
  align.h target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h search.h thread.h globals.h genesis/symbol.h \
  genesis/vector.h symbol-tls.inc genesis/static-symbols.h \
  genesis/thread.h gencgc-alloc-region.h interrupt.h validate.h \
  gc-typedefs.h gc.h gc-assert.h immobile-space.h gencgc-impl.h \
  genesis/cardmarks.h genesis/cons.h genesis/weak-pointer.h hopscotch.h \
  code.h genesis/closure.h forwarding-ptr.inc \
  genesis/primitive-objects.h genesis/number-types.h genesis/fdefn.h \
  genesis/instance.h instance.inc genesis/sap.h genesis/value-cell.h \
  genesis/hash-table.h genesis/package.h genesis/split-ordered-list.h \
  genesis/brothertree.h
