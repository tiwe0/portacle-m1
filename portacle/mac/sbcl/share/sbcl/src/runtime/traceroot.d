traceroot.o traceroot.d : traceroot.c genesis/sbcl.h arch.h os.h runtime.h lispobj.h \
  align.h target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h thread.h globals.h genesis/symbol.h genesis/vector.h \
  symbol-tls.inc genesis/static-symbols.h genesis/thread.h \
  gencgc-alloc-region.h interrupt.h validate.h gc-typedefs.h lispregs.h \
  target-lispregs.h genesis/regnames.h gc.h gc-assert.h interr.h \
  immobile-space.h gencgc-impl.h genesis/cardmarks.h genesis/cons.h \
  genesis/weak-pointer.h hopscotch.h code.h genesis/closure.h \
  forwarding-ptr.inc genesis/fdefn.h genesis/gc-tables.h \
  genesis/hash-table.h genesis/instance.h instance.inc genesis/package.h \
  search.h genesis/avlnode.h genesis/sap.h print.h
