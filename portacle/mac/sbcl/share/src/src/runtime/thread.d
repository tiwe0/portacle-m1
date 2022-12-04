thread.o thread.d : thread.c sbcl.h genesis/config.h genesis/constants.h runtime.h \
  lispobj.h fixnump.h align.h validate.h thread.h globals.h os.h \
  target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h gencgc-alloc-region.h gc.h genesis/symbol.h \
  genesis/vector.h genesis/static-symbols.h genesis/thread.h \
  genesis/thread-instance.h genesis/fdefn.h interrupt.h arch.h dynbind.h \
  genesis/cons.h interr.h alloc.h gc-internal.h genesis/code.h \
  genesis/simple-fun.h gc-assert.h code.h gencgc-internal.h hopscotch.h \
  genesis/sap.h pseudo-atomic.h lispregs.h target-lispregs.h \
  genesis/regnames.h atomiclog.inc genesis/thread-init.inc
