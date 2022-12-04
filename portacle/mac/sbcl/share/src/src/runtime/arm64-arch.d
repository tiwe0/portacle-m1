arm64-arch.o arm64-arch.d : arm64-arch.c sbcl.h genesis/config.h genesis/constants.h \
  runtime.h lispobj.h fixnump.h align.h arch.h os.h target-os.h \
  darwin-os.h target-arch-os.h arch-os-generic.inc target-arch.h \
  thread.h globals.h gencgc-alloc-region.h gc.h genesis/symbol.h \
  genesis/vector.h genesis/static-symbols.h genesis/thread.h \
  genesis/thread-instance.h genesis/fdefn.h interrupt.h validate.h \
  lispregs.h target-lispregs.h genesis/regnames.h alloc.h gc-internal.h \
  genesis/code.h genesis/simple-fun.h interr.h gc-assert.h code.h \
  gencgc-internal.h hopscotch.h genesis/sap.h breakpoint.h monitor.h \
  pseudo-atomic.h
