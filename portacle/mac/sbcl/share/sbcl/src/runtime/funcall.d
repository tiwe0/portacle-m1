funcall.o funcall.d : funcall.c genesis/sbcl.h runtime.h lispobj.h align.h globals.h \
  os.h target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h interrupt.h genesis/static-symbols.h thread.h \
  genesis/symbol.h genesis/vector.h symbol-tls.inc genesis/thread.h \
  gencgc-alloc-region.h validate.h gc-typedefs.h
