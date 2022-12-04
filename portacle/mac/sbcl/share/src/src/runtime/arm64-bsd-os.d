arm64-bsd-os.o arm64-bsd-os.d : arm64-bsd-os.c sbcl.h genesis/config.h \
  genesis/constants.h os.h runtime.h lispobj.h fixnump.h align.h \
  target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h arch.h thread.h globals.h gencgc-alloc-region.h gc.h \
  genesis/symbol.h genesis/vector.h genesis/static-symbols.h \
  genesis/thread.h genesis/thread-instance.h genesis/fdefn.h interrupt.h \
  validate.h interr.h lispregs.h target-lispregs.h genesis/regnames.h
