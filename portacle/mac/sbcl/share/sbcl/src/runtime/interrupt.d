interrupt.o interrupt.d : interrupt.c genesis/sbcl.h runtime.h lispobj.h align.h \
  arch.h os.h target-os.h darwin-os.h target-arch-os.h \
  arch-os-generic.inc target-arch.h thread.h globals.h genesis/symbol.h \
  genesis/vector.h symbol-tls.inc genesis/static-symbols.h \
  genesis/thread.h gencgc-alloc-region.h interrupt.h validate.h \
  gc-typedefs.h code.h genesis/closure.h gc-assert.h interr.h lispregs.h \
  target-lispregs.h genesis/regnames.h gc.h immobile-space.h \
  gencgc-impl.h genesis/cardmarks.h genesis/cons.h \
  genesis/weak-pointer.h hopscotch.h forwarding-ptr.inc genesis/sap.h \
  dynbind.h pseudo-atomic.h genesis/fdefn.h atomiclog.inc
