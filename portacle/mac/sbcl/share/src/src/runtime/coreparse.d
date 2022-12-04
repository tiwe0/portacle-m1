coreparse.o coreparse.d : coreparse.c sbcl.h genesis/config.h genesis/constants.h os.h \
  runtime.h lispobj.h fixnump.h align.h target-os.h darwin-os.h \
  target-arch-os.h arch-os-generic.inc target-arch.h globals.h core.h \
  arch.h thread.h gencgc-alloc-region.h gc.h genesis/symbol.h \
  genesis/vector.h genesis/static-symbols.h genesis/thread.h \
  genesis/thread-instance.h genesis/fdefn.h interrupt.h validate.h \
  interr.h gc-internal.h genesis/code.h genesis/simple-fun.h gc-assert.h \
  code.h gencgc-internal.h hopscotch.h gc-private.h genesis/instance.h \
  genesis/weak-pointer.h immobile-space.h genesis/layout.h \
  genesis/cons.h /usr/local/include/zstd.h ../../output/build-id.inc \
  genesis/gc-tables.h genesis/hash-table.h var-io.h unaligned.h
