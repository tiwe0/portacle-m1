dynbind.o dynbind.d : dynbind.c genesis/sbcl.h runtime.h lispobj.h align.h globals.h \
  os.h target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h dynbind.h thread.h genesis/symbol.h genesis/vector.h \
  symbol-tls.inc genesis/static-symbols.h genesis/thread.h \
  gencgc-alloc-region.h interrupt.h validate.h gc-typedefs.h interr.h \
  genesis/binding.h
