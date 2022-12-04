gencgc.o gencgc.d : gencgc.c sbcl.h genesis/config.h genesis/constants.h runtime.h \
  lispobj.h fixnump.h align.h os.h target-os.h darwin-os.h \
  target-arch-os.h arch-os-generic.inc target-arch.h interr.h globals.h \
  interrupt.h genesis/static-symbols.h thread.h gencgc-alloc-region.h \
  gc.h genesis/symbol.h genesis/vector.h genesis/thread.h \
  genesis/thread-instance.h genesis/fdefn.h validate.h lispregs.h \
  target-lispregs.h genesis/regnames.h arch.h gc-internal.h \
  genesis/code.h genesis/simple-fun.h gc-assert.h code.h \
  gencgc-internal.h hopscotch.h gc-private.h genesis/instance.h \
  genesis/weak-pointer.h immobile-space.h genesis/layout.h \
  genesis/cons.h gencgc-private.h pseudo-atomic.h alloc.h genesis/sap.h \
  genesis/gc-tables.h save.h core.h genesis/hash-table.h \
  forwarding-ptr.h var-io.h private-cons.inc brothertree.h verify.inc
