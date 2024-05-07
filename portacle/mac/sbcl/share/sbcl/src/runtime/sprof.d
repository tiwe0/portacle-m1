sprof.o sprof.d : sprof.c thread.h genesis/sbcl.h globals.h runtime.h lispobj.h \
  align.h os.h target-os.h darwin-os.h target-arch-os.h \
  arch-os-generic.inc target-arch.h genesis/symbol.h genesis/vector.h \
  symbol-tls.inc genesis/static-symbols.h genesis/thread.h \
  gencgc-alloc-region.h interrupt.h validate.h gc-typedefs.h \
  murmur_hash.h gc-assert.h interr.h arch.h code.h genesis/closure.h \
  gc.h immobile-space.h gencgc-impl.h genesis/cardmarks.h genesis/cons.h \
  genesis/weak-pointer.h hopscotch.h forwarding-ptr.inc lispregs.h \
  target-lispregs.h genesis/regnames.h callframe.inc \
  genesis/compiled-debug-info.h
