print.o print.d : print.c sbcl.h genesis/config.h genesis/constants.h print.h \
  runtime.h lispobj.h fixnump.h align.h genesis/vector.h code.h \
  genesis/code.h gc-assert.h interr.h os.h target-os.h darwin-os.h \
  target-arch-os.h arch-os-generic.inc target-arch.h gc-internal.h \
  genesis/simple-fun.h thread.h globals.h gencgc-alloc-region.h gc.h \
  genesis/symbol.h genesis/static-symbols.h genesis/thread.h \
  genesis/thread-instance.h genesis/fdefn.h interrupt.h validate.h \
  gencgc-internal.h hopscotch.h gc-private.h genesis/instance.h \
  genesis/weak-pointer.h immobile-space.h genesis/layout.h \
  genesis/cons.h genesis/gc-tables.h monitor.h vars.h \
  genesis/primitive-objects.h genesis/array.h genesis/bignum.h \
  genesis/binding.h genesis/catch-block.h genesis/closure.h \
  genesis/complex.h genesis/complex-double-float.h \
  genesis/complex-single-float.h genesis/double-float.h \
  genesis/funcallable-instance.h genesis/ratio.h genesis/sap.h \
  genesis/unwind-block.h genesis/value-cell.h genesis/tagnames.h \
  genesis/defstruct-description.h genesis/defstruct-slot-description.h \
  genesis/print.inc forwarding-ptr.h genesis/classoid.h
