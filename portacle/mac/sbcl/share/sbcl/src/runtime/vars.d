vars.o vars.d : vars.c genesis/sbcl.h runtime.h lispobj.h align.h vars.h os.h \
  target-os.h darwin-os.h target-arch-os.h arch-os-generic.inc \
  target-arch.h
