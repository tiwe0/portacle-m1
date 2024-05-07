thread.o thread.d : thread.c genesis/sbcl.h runtime.h lispobj.h align.h validate.h \
  thread.h globals.h os.h target-os.h darwin-os.h target-arch-os.h \
  arch-os-generic.inc target-arch.h genesis/symbol.h genesis/vector.h \
  symbol-tls.inc genesis/static-symbols.h genesis/thread.h \
  gencgc-alloc-region.h interrupt.h gc-typedefs.h arch.h dynbind.h \
  genesis/cons.h genesis/fdefn.h genesis/instance.h instance.inc \
  interr.h gc.h gc-assert.h immobile-space.h gencgc-impl.h \
  genesis/cardmarks.h genesis/weak-pointer.h hopscotch.h code.h \
  genesis/closure.h forwarding-ptr.inc pseudo-atomic.h lispregs.h \
  target-lispregs.h genesis/regnames.h atomiclog.inc \
  genesis/thread-init.inc
