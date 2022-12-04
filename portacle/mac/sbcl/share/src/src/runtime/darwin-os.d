darwin-os.o darwin-os.d : darwin-os.c thread.h sbcl.h genesis/config.h \
  genesis/constants.h globals.h runtime.h lispobj.h fixnump.h align.h \
  os.h target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h gencgc-alloc-region.h gc.h genesis/symbol.h \
  genesis/vector.h genesis/static-symbols.h genesis/thread.h \
  genesis/thread-instance.h genesis/fdefn.h interrupt.h validate.h \
  interr.h
