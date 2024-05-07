main.o main.d : main.c interr.h os.h genesis/sbcl.h runtime.h lispobj.h align.h \
  target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h
