breakpoint.o breakpoint.d : breakpoint.c genesis/sbcl.h genesis/sap.h lispobj.h \
  runtime.h align.h os.h target-os.h darwin-os.h target-arch-os.h \
  arch-os-generic.inc target-arch.h interrupt.h genesis/static-symbols.h \
  thread.h globals.h genesis/symbol.h genesis/vector.h symbol-tls.inc \
  genesis/thread.h gencgc-alloc-region.h validate.h gc-typedefs.h arch.h \
  gc.h gc-assert.h interr.h immobile-space.h gencgc-impl.h \
  genesis/cardmarks.h genesis/cons.h genesis/weak-pointer.h hopscotch.h \
  code.h genesis/closure.h forwarding-ptr.inc lispregs.h \
  target-lispregs.h genesis/regnames.h breakpoint.h genesis/fdefn.h
