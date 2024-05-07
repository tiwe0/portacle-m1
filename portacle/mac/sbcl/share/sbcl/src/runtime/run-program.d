run-program.o run-program.d : run-program.c genesis/sbcl.h interr.h os.h runtime.h \
  lispobj.h align.h target-os.h darwin-os.h target-arch-os.h \
  arch-os-generic.inc target-arch.h
