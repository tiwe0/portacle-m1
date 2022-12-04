main.o main.d : main.c interr.h os.h sbcl.h genesis/config.h genesis/constants.h \
  runtime.h lispobj.h fixnump.h align.h target-os.h darwin-os.h \
  target-arch-os.h arch-os-generic.inc target-arch.h
