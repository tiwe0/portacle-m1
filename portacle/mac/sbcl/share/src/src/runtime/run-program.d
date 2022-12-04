run-program.o run-program.d : run-program.c sbcl.h genesis/config.h genesis/constants.h \
  interr.h os.h runtime.h lispobj.h fixnump.h align.h target-os.h \
  darwin-os.h target-arch-os.h arch-os-generic.inc target-arch.h
