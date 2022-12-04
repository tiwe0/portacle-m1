save.o save.d : save.c sbcl.h genesis/config.h genesis/constants.h runtime.h \
  lispobj.h fixnump.h align.h os.h target-os.h darwin-os.h \
  target-arch-os.h arch-os-generic.inc target-arch.h core.h globals.h \
  save.h dynbind.h lispregs.h target-lispregs.h genesis/regnames.h \
  validate.h thread.h gencgc-alloc-region.h gc.h genesis/symbol.h \
  genesis/vector.h genesis/static-symbols.h genesis/thread.h \
  genesis/thread-instance.h genesis/fdefn.h interrupt.h gc-internal.h \
  genesis/code.h genesis/simple-fun.h interr.h gc-assert.h code.h \
  gencgc-internal.h hopscotch.h arch.h immobile-space.h search.h \
  /usr/local/include/zstd.h
