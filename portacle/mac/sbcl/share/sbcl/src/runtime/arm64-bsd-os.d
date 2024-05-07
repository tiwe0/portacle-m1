arm64-bsd-os.o arm64-bsd-os.d : arm64-bsd-os.c genesis/sbcl.h os.h runtime.h lispobj.h \
  align.h target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h arch.h thread.h globals.h genesis/symbol.h \
  genesis/vector.h symbol-tls.inc genesis/static-symbols.h \
  genesis/thread.h gencgc-alloc-region.h interrupt.h validate.h \
  gc-typedefs.h interr.h lispregs.h target-lispregs.h genesis/regnames.h
