save.o save.d : save.c genesis/sbcl.h runtime.h lispobj.h align.h os.h \
  target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h core.h globals.h dynbind.h lispregs.h target-lispregs.h \
  genesis/regnames.h validate.h thread.h genesis/symbol.h \
  genesis/vector.h symbol-tls.inc genesis/static-symbols.h \
  genesis/thread.h gencgc-alloc-region.h interrupt.h gc-typedefs.h gc.h \
  gc-assert.h interr.h immobile-space.h gencgc-impl.h \
  genesis/cardmarks.h genesis/cons.h genesis/weak-pointer.h hopscotch.h \
  code.h genesis/closure.h forwarding-ptr.inc arch.h search.h \
  incremental-compact.h
