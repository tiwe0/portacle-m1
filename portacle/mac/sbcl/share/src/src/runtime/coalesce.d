coalesce.o coalesce.d : coalesce.c sbcl.h genesis/config.h genesis/constants.h gc.h \
  os.h runtime.h lispobj.h fixnump.h align.h target-os.h darwin-os.h \
  target-arch-os.h arch-os-generic.inc target-arch.h gc-internal.h \
  genesis/code.h genesis/simple-fun.h thread.h globals.h \
  gencgc-alloc-region.h genesis/symbol.h genesis/vector.h \
  genesis/static-symbols.h genesis/thread.h genesis/thread-instance.h \
  genesis/fdefn.h interrupt.h validate.h interr.h gc-assert.h code.h \
  gencgc-internal.h hopscotch.h gc-private.h genesis/instance.h \
  genesis/weak-pointer.h immobile-space.h genesis/layout.h \
  genesis/cons.h genesis/gc-tables.h
