funcall.o funcall.d : funcall.c sbcl.h genesis/config.h genesis/constants.h \
  runtime.h lispobj.h fixnump.h align.h globals.h os.h target-os.h \
  darwin-os.h target-arch-os.h arch-os-generic.inc target-arch.h \
  interrupt.h genesis/static-symbols.h thread.h gencgc-alloc-region.h \
  gc.h genesis/symbol.h genesis/vector.h genesis/thread.h \
  genesis/thread-instance.h genesis/fdefn.h validate.h
