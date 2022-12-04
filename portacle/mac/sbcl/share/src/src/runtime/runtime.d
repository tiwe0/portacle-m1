runtime.o runtime.d : runtime.c sbcl.h genesis/config.h genesis/constants.h \
  runtime.h lispobj.h fixnump.h align.h vars.h globals.h os.h \
  target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h interr.h alloc.h gc-internal.h genesis/code.h \
  genesis/simple-fun.h thread.h gencgc-alloc-region.h gc.h \
  genesis/symbol.h genesis/vector.h genesis/static-symbols.h \
  genesis/thread.h genesis/thread-instance.h genesis/fdefn.h interrupt.h \
  validate.h gc-assert.h code.h gencgc-internal.h hopscotch.h \
  genesis/sap.h arch.h core.h save.h lispregs.h target-lispregs.h \
  genesis/regnames.h
