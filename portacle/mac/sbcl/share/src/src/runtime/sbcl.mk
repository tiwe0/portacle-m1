CC=cc
LD=ld
CFLAGS= -fno-omit-frame-pointer -D_GNU_SOURCE -g -Wall -Wundef -Wsign-compare -Wpointer-arith -O3 -g -Wall -fdollars-in-identifiers -fno-omit-frame-pointer
ASFLAGS= -fno-omit-frame-pointer -D_GNU_SOURCE -g -Wall -Wundef -Wsign-compare -Wpointer-arith -O3 -g -Wall -fdollars-in-identifiers -fno-omit-frame-pointer
LINKFLAGS=-g -dynamic -twolevel_namespace -bind_at_load
LDFLAGS=
__LDFLAGS__=
LIBS=-lSystem -lc -ldl -lpthread -lzstd  -lm
