coreparse.o coreparse.d : coreparse.c genesis/sbcl.h os.h runtime.h lispobj.h align.h \
  target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h globals.h core.h arch.h thread.h genesis/symbol.h \
  genesis/vector.h symbol-tls.inc genesis/static-symbols.h \
  genesis/thread.h gencgc-alloc-region.h interrupt.h validate.h \
  gc-typedefs.h interr.h gc.h gc-assert.h immobile-space.h gencgc-impl.h \
  genesis/cardmarks.h genesis/cons.h genesis/weak-pointer.h hopscotch.h \
  code.h genesis/closure.h forwarding-ptr.inc graphvisit.h \
  genesis/instance.h instance.inc genesis/fdefn.h \
  ../../output/build-id.inc genesis/gc-tables.h genesis/hash-table.h \
  var-io.h genesis/split-ordered-list.h
