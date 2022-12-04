vars.o vars.d : vars.c sbcl.h genesis/config.h genesis/constants.h runtime.h \
  lispobj.h fixnump.h align.h vars.h os.h target-os.h darwin-os.h \
  target-arch-os.h arch-os-generic.inc target-arch.h
