arm64-assem.o arm64-assem.d : arm64-assem.S globals.h sbcl.h genesis/config.h \
  genesis/constants.h lispregs.h target-lispregs.h genesis/regnames.h \
  validate.h genesis/closure.h genesis/funcallable-instance.h \
  genesis/fdefn.h genesis/static-symbols.h genesis/simple-fun.h \
  genesis/symbol.h genesis/thread.h
