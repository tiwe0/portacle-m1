monitor.o monitor.d : monitor.c sbcl.h genesis/config.h genesis/constants.h \
  runtime.h lispobj.h fixnump.h align.h parse.h vars.h print.h \
  genesis/vector.h arch.h os.h target-os.h darwin-os.h target-arch-os.h \
  arch-os-generic.inc target-arch.h thread.h globals.h \
  gencgc-alloc-region.h gc.h genesis/symbol.h genesis/static-symbols.h \
  genesis/thread.h genesis/thread-instance.h genesis/fdefn.h interrupt.h \
  validate.h interr.h search.h lispregs.h target-lispregs.h \
  genesis/regnames.h genesis/primitive-objects.h genesis/array.h \
  genesis/bignum.h genesis/binding.h genesis/catch-block.h \
  genesis/closure.h genesis/code.h genesis/complex.h \
  genesis/complex-double-float.h genesis/complex-single-float.h \
  genesis/cons.h genesis/double-float.h genesis/funcallable-instance.h \
  genesis/instance.h genesis/ratio.h genesis/sap.h genesis/simple-fun.h \
  genesis/unwind-block.h genesis/value-cell.h genesis/weak-pointer.h \
  genesis/gc-tables.h gc-internal.h gc-assert.h code.h gencgc-internal.h \
  hopscotch.h
