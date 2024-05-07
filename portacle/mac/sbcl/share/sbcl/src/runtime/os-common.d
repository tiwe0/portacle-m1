os-common.o os-common.d : os-common.c genesis/sbcl.h globals.h runtime.h lispobj.h \
  align.h os.h target-os.h darwin-os.h target-arch-os.h \
  arch-os-generic.inc target-arch.h genesis/cons.h genesis/vector.h \
  genesis/symbol.h symbol-tls.inc genesis/static-symbols.h thread.h \
  genesis/thread.h gencgc-alloc-region.h interrupt.h validate.h \
  gc-typedefs.h arch.h interr.h immobile-space.h code.h \
  genesis/closure.h gc-assert.h gc.h gencgc-impl.h genesis/cardmarks.h \
  genesis/weak-pointer.h hopscotch.h forwarding-ptr.inc sys_mmap.inc
