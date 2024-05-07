arm64-darwin-os.o arm64-darwin-os.d : arm64-darwin-os.c thread.h genesis/sbcl.h globals.h \
  runtime.h lispobj.h align.h os.h target-os.h darwin-os.h \
  target-arch-os.h arch-os-generic.inc target-arch.h genesis/symbol.h \
  genesis/vector.h symbol-tls.inc genesis/static-symbols.h \
  genesis/thread.h gencgc-alloc-region.h interrupt.h validate.h \
  gc-typedefs.h gc.h gc-assert.h interr.h immobile-space.h gencgc-impl.h \
  genesis/cardmarks.h genesis/cons.h genesis/weak-pointer.h hopscotch.h \
  code.h genesis/closure.h forwarding-ptr.inc
