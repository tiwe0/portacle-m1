gc-common.o gc-common.d : gc-common.c sbcl.h genesis/config.h genesis/constants.h \
  runtime.h lispobj.h fixnump.h align.h os.h target-os.h darwin-os.h \
  target-arch-os.h arch-os-generic.inc target-arch.h interr.h globals.h \
  interrupt.h genesis/static-symbols.h thread.h gencgc-alloc-region.h \
  gc.h genesis/symbol.h genesis/vector.h genesis/thread.h \
  genesis/thread-instance.h genesis/fdefn.h validate.h lispregs.h \
  target-lispregs.h genesis/regnames.h arch.h hopscotch.h code.h \
  genesis/code.h gc-assert.h genesis/primitive-objects.h genesis/array.h \
  genesis/bignum.h genesis/binding.h genesis/catch-block.h \
  genesis/closure.h genesis/complex.h genesis/complex-double-float.h \
  genesis/complex-single-float.h genesis/cons.h genesis/double-float.h \
  genesis/funcallable-instance.h genesis/instance.h genesis/ratio.h \
  genesis/sap.h genesis/simple-fun.h genesis/unwind-block.h \
  genesis/value-cell.h genesis/weak-pointer.h genesis/layout.h \
  genesis/hash-table.h gc-internal.h gencgc-internal.h gc-private.h \
  immobile-space.h forwarding-ptr.h var-io.h search.h murmur_hash.h \
  weak-hash-pred.inc genesis/gc-tables.h
