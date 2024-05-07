validate.o validate.d : validate.c genesis/sbcl.h runtime.h lispobj.h align.h os.h \
  target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h globals.h interr.h validate.h thread.h genesis/symbol.h \
  genesis/vector.h symbol-tls.inc genesis/static-symbols.h \
  genesis/thread.h gencgc-alloc-region.h interrupt.h gc-typedefs.h
