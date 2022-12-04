parse.o parse.d : parse.c sbcl.h genesis/config.h genesis/constants.h runtime.h \
  lispobj.h fixnump.h align.h globals.h os.h target-os.h darwin-os.h \
  target-arch-os.h arch-os-generic.inc target-arch.h vars.h parse.h \
  interrupt.h genesis/static-symbols.h thread.h gencgc-alloc-region.h \
  gc.h genesis/symbol.h genesis/vector.h genesis/thread.h \
  genesis/thread-instance.h genesis/fdefn.h validate.h lispregs.h \
  target-lispregs.h genesis/regnames.h monitor.h arch.h search.h \
  genesis/simple-fun.h
