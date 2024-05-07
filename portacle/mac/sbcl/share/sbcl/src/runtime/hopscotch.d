hopscotch.o hopscotch.d : hopscotch.c os.h genesis/sbcl.h runtime.h lispobj.h align.h \
  target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h gc.h gc-assert.h interr.h gc-typedefs.h immobile-space.h \
  gencgc-impl.h gencgc-alloc-region.h genesis/cardmarks.h genesis/cons.h \
  genesis/weak-pointer.h globals.h hopscotch.h code.h genesis/closure.h \
  forwarding-ptr.inc genesis/vector.h murmur_hash.h
