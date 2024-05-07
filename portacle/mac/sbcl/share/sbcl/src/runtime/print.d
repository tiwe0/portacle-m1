print.o print.d : print.c genesis/sbcl.h print.h runtime.h lispobj.h align.h \
  genesis/vector.h code.h genesis/closure.h gc-assert.h interr.h os.h \
  target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h gc.h gc-typedefs.h immobile-space.h gencgc-impl.h \
  gencgc-alloc-region.h genesis/cardmarks.h genesis/cons.h \
  genesis/weak-pointer.h globals.h hopscotch.h forwarding-ptr.inc \
  genesis/gc-tables.h thread.h genesis/symbol.h symbol-tls.inc \
  genesis/static-symbols.h genesis/thread.h interrupt.h validate.h \
  vars.h genesis/primitive-objects.h genesis/number-types.h \
  genesis/fdefn.h genesis/instance.h instance.inc genesis/sap.h \
  genesis/value-cell.h genesis/tagnames.h \
  genesis/defstruct-description.h genesis/print.inc
