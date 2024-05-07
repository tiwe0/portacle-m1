alloc.o alloc.d : alloc.c gc.h genesis/sbcl.h gc-assert.h interr.h os.h runtime.h \
  lispobj.h align.h target-os.h darwin-os.h target-arch-os.h \
  arch-os-generic.inc target-arch.h gc-typedefs.h immobile-space.h \
  gencgc-impl.h gencgc-alloc-region.h genesis/cardmarks.h genesis/cons.h \
  genesis/weak-pointer.h globals.h hopscotch.h code.h genesis/closure.h \
  forwarding-ptr.inc pseudo-atomic.h genesis/thread.h \
  genesis/static-symbols.h genesis/symbol.h genesis/vector.h \
  symbol-tls.inc thread.h interrupt.h validate.h genesis/gc-tables.h \
  arch.h genesis/fdefn.h
