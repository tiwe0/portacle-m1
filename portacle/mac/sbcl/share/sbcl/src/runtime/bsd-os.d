bsd-os.o bsd-os.d : bsd-os.c genesis/sbcl.h os.h runtime.h lispobj.h align.h \
  target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h arch.h thread.h globals.h genesis/symbol.h \
  genesis/vector.h symbol-tls.inc genesis/static-symbols.h \
  genesis/thread.h gencgc-alloc-region.h interrupt.h validate.h \
  gc-typedefs.h interr.h lispregs.h target-lispregs.h genesis/regnames.h \
  genesis/fdefn.h gc.h gc-assert.h immobile-space.h gencgc-impl.h \
  genesis/cardmarks.h genesis/cons.h genesis/weak-pointer.h hopscotch.h \
  code.h genesis/closure.h forwarding-ptr.inc sys_mmap.inc
