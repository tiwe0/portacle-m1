os-common.o os-common.d : os-common.c sbcl.h genesis/config.h genesis/constants.h \
  globals.h runtime.h lispobj.h fixnump.h align.h os.h target-os.h \
  darwin-os.h target-arch-os.h arch-os-generic.inc target-arch.h \
  genesis/cons.h genesis/vector.h genesis/symbol.h \
  genesis/static-symbols.h thread.h gencgc-alloc-region.h gc.h \
  genesis/thread.h genesis/thread-instance.h genesis/fdefn.h interrupt.h \
  validate.h arch.h interr.h immobile-space.h code.h genesis/code.h \
  gc-assert.h sys_mmap.inc gc-internal.h genesis/simple-fun.h \
  gencgc-internal.h hopscotch.h
