sprof.o sprof.d : sprof.c thread.h sbcl.h genesis/config.h genesis/constants.h \
  globals.h runtime.h lispobj.h fixnump.h align.h os.h target-os.h \
  darwin-os.h target-arch-os.h arch-os-generic.inc target-arch.h \
  gencgc-alloc-region.h gc.h genesis/symbol.h genesis/vector.h \
  genesis/static-symbols.h genesis/thread.h genesis/thread-instance.h \
  genesis/fdefn.h interrupt.h validate.h murmur_hash.h gc-assert.h \
  interr.h arch.h gc-internal.h genesis/code.h genesis/simple-fun.h \
  code.h gencgc-internal.h hopscotch.h lispregs.h target-lispregs.h \
  genesis/regnames.h callframe.inc genesis/compiled-debug-fun.h
