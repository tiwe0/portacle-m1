fullcgc.o fullcgc.d : fullcgc.c gc.h genesis/sbcl.h gc-assert.h interr.h os.h \
  runtime.h lispobj.h align.h target-os.h darwin-os.h target-arch-os.h \
  arch-os-generic.inc target-arch.h gc-typedefs.h immobile-space.h \
  gencgc-impl.h gencgc-alloc-region.h genesis/cardmarks.h genesis/cons.h \
  genesis/weak-pointer.h globals.h hopscotch.h code.h genesis/closure.h \
  forwarding-ptr.inc genesis/gc-tables.h genesis/instance.h instance.inc \
  genesis/vector.h genesis/hash-table.h genesis/static-symbols.h \
  genesis/symbol.h symbol-tls.inc genesis/fdefn.h queue.h validate.h \
  thread.h genesis/thread.h interrupt.h trace-object.inc \
  weak-hash-pred.inc genesis/split-ordered-list.h
