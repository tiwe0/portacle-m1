runtime.o runtime.d : runtime.c genesis/sbcl.h runtime.h lispobj.h align.h vars.h \
  globals.h os.h target-os.h darwin-os.h target-arch-os.h \
  arch-os-generic.inc target-arch.h interr.h interrupt.h \
  genesis/static-symbols.h thread.h genesis/symbol.h genesis/vector.h \
  symbol-tls.inc genesis/thread.h gencgc-alloc-region.h validate.h \
  gc-typedefs.h arch.h gc.h gc-assert.h immobile-space.h gencgc-impl.h \
  genesis/cardmarks.h genesis/cons.h genesis/weak-pointer.h hopscotch.h \
  code.h genesis/closure.h forwarding-ptr.inc core.h lispregs.h \
  target-lispregs.h genesis/regnames.h
