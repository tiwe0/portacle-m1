arm64-arch.o arm64-arch.d : arm64-arch.c genesis/sbcl.h runtime.h lispobj.h align.h \
  arch.h os.h target-os.h darwin-os.h target-arch-os.h \
  arch-os-generic.inc target-arch.h thread.h globals.h genesis/symbol.h \
  genesis/vector.h symbol-tls.inc genesis/static-symbols.h \
  genesis/thread.h gencgc-alloc-region.h interrupt.h validate.h \
  gc-typedefs.h lispregs.h target-lispregs.h genesis/regnames.h interr.h \
  breakpoint.h pseudo-atomic.h
