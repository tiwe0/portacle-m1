monitor.o monitor.d : monitor.c genesis/sbcl.h lispobj.h runtime.h align.h parse.h \
  vars.h print.h genesis/vector.h arch.h os.h target-os.h darwin-os.h \
  target-arch-os.h arch-os-generic.inc target-arch.h thread.h globals.h \
  genesis/symbol.h symbol-tls.inc genesis/static-symbols.h \
  genesis/thread.h gencgc-alloc-region.h interrupt.h validate.h \
  gc-typedefs.h interr.h search.h lispregs.h target-lispregs.h \
  genesis/regnames.h genesis/instance.h instance.inc \
  genesis/primitive-objects.h genesis/number-types.h genesis/closure.h \
  genesis/cons.h genesis/fdefn.h genesis/sap.h genesis/value-cell.h \
  genesis/weak-pointer.h genesis/gc-tables.h genesis/unwind-block.h \
  genesis/hash-table.h gc.h gc-assert.h immobile-space.h gencgc-impl.h \
  genesis/cardmarks.h hopscotch.h code.h forwarding-ptr.inc \
  ../../tlsf-bsd/tlsf/tlsf.h
