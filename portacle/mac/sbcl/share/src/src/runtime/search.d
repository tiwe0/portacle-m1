search.o search.d : search.c sbcl.h genesis/config.h genesis/constants.h runtime.h \
  lispobj.h fixnump.h align.h os.h target-os.h darwin-os.h \
  target-arch-os.h arch-os-generic.inc target-arch.h search.h thread.h \
  globals.h gencgc-alloc-region.h gc.h genesis/symbol.h genesis/vector.h \
  genesis/static-symbols.h genesis/thread.h genesis/thread-instance.h \
  genesis/fdefn.h interrupt.h validate.h gc-internal.h genesis/code.h \
  genesis/simple-fun.h interr.h gc-assert.h code.h gencgc-internal.h \
  hopscotch.h gc-private.h genesis/instance.h genesis/weak-pointer.h \
  immobile-space.h genesis/layout.h genesis/cons.h \
  genesis/primitive-objects.h genesis/array.h genesis/bignum.h \
  genesis/binding.h genesis/catch-block.h genesis/closure.h \
  genesis/complex.h genesis/complex-double-float.h \
  genesis/complex-single-float.h genesis/double-float.h \
  genesis/funcallable-instance.h genesis/ratio.h genesis/sap.h \
  genesis/unwind-block.h genesis/value-cell.h genesis/hash-table.h \
  genesis/package.h brothertree.h forwarding-ptr.h
