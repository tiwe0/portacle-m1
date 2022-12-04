dynbind.o dynbind.d : dynbind.c sbcl.h genesis/config.h genesis/constants.h \
  runtime.h lispobj.h fixnump.h align.h globals.h os.h target-os.h \
  darwin-os.h target-arch-os.h arch-os-generic.inc target-arch.h \
  dynbind.h thread.h gencgc-alloc-region.h gc.h genesis/symbol.h \
  genesis/vector.h genesis/static-symbols.h genesis/thread.h \
  genesis/thread-instance.h genesis/fdefn.h interrupt.h validate.h \
  interr.h genesis/binding.h
