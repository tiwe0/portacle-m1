stringspace.o stringspace.d : stringspace.c code.h genesis/closure.h lispobj.h \
  genesis/sbcl.h gc-assert.h interr.h os.h runtime.h align.h target-os.h \
  darwin-os.h target-arch-os.h arch-os-generic.inc target-arch.h gc.h \
  gc-typedefs.h immobile-space.h gencgc-impl.h gencgc-alloc-region.h \
  genesis/cardmarks.h genesis/cons.h genesis/weak-pointer.h globals.h \
  hopscotch.h forwarding-ptr.inc genesis/gc-tables.h genesis/instance.h \
  instance.inc genesis/static-symbols.h genesis/symbol.h \
  genesis/vector.h symbol-tls.inc validate.h thread.h genesis/thread.h \
  interrupt.h
