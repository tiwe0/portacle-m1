arena.o arena.d : arena.c genesis/sbcl.h runtime.h lispobj.h align.h globals.h \
  os.h target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h gc.h gc-assert.h interr.h gc-typedefs.h immobile-space.h \
  gencgc-impl.h gencgc-alloc-region.h genesis/cardmarks.h genesis/cons.h \
  genesis/weak-pointer.h hopscotch.h code.h genesis/closure.h \
  forwarding-ptr.inc lispregs.h target-lispregs.h genesis/regnames.h \
  genesis/arena.h genesis/gc-tables.h thread.h genesis/symbol.h \
  genesis/vector.h symbol-tls.inc genesis/static-symbols.h \
  genesis/thread.h interrupt.h validate.h genesis/instance.h \
  instance.inc graphvisit.h
