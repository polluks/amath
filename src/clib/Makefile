CC       = x86_64-aros-gcc
CFLAGS   = -std=c9x -O3 -DWITHTEST -I. -I.. -Wall
AR       = x86_64-aros-ar
RANLIB   = x86_64-aros-ranlib
MKDIR    = mkdir -p
DEL      = rm -f
INSTALL  = install -m 0644
PREFIX   = /usr

alib     = libamathc.a
solib    = libamathc.so

all: static shared

static: ${alib}

shared: ${solib}

static/alloccpy.o:	alloccpy.c
	${CC} ${CFLAGS} -fno-builtin -c alloccpy.c -o static/alloccpy.o

shared/alloccpy.o:	alloccpy.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c alloccpy.c -o shared/alloccpy.o

static/mem.o:	mem.c
	${CC} ${CFLAGS} -fno-builtin -c mem.c -o static/mem.o

shared/mem.o:	mem.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c mem.c -o shared/mem.o

static/memcpy.o:	memcpy.c
	${CC} ${CFLAGS} -fno-builtin -c memcpy.c -o static/memcpy.o

shared/memcpy.o:	memcpy.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c memcpy.c -o shared/memcpy.o

static/memset.o:	memset.c
	${CC} ${CFLAGS} -fno-builtin -c memset.c -o static/memset.o

shared/memset.o:	memset.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c memset.c -o shared/memset.o

static/strcmp.o:	strcmp.c
	${CC} ${CFLAGS} -fno-builtin -c strcmp.c -o static/strcmp.o

shared/strcmp.o:	strcmp.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c strcmp.c -o shared/strcmp.o

static/strlen.o:	strlen.c
	${CC} ${CFLAGS} -fno-builtin -c strlen.c -o static/strlen.o

shared/strlen.o:	strlen.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c strlen.c -o shared/strlen.o

static/untag.o:	untag.c
	${CC} ${CFLAGS} -fno-builtin -c untag.c -o static/untag.o

shared/untag.o:	untag.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c untag.c -o shared/untag.o

.PHONY: build
build:
	${MKDIR} static
	${MKDIR} shared

${solib}:	build  shared/alloccpy.o shared/mem.o shared/memcpy.o shared/memset.o shared/strcmp.o shared/strlen.o shared/untag.o
	${CC} -shared -fPIC -Wl,-soname,${solib} -o ${solib}  shared/alloccpy.o shared/mem.o shared/memcpy.o shared/memset.o shared/strcmp.o shared/strlen.o shared/untag.o -lc

${alib}:	build  static/alloccpy.o static/mem.o static/memcpy.o static/memset.o static/strcmp.o static/strlen.o static/untag.o
	${AR} rcs static/${alib}  static/alloccpy.o static/mem.o static/memcpy.o static/memset.o static/strcmp.o static/strlen.o static/untag.o
	${RANLIB} static/${alib}

.PHONY: install
install:	${alib} ${solib}
	${MKDIR} ${DESTDIR}${PREFIX}/lib
	${MKDIR} ${DESTDIR}${PREFIX}/include
	${INSTALL} static/${alib} ${DESTDIR}${PREFIX}/lib/${alib}
	${INSTALL} ${solib} ${DESTDIR}${PREFIX}/lib/${solib}
	${INSTALL} ../amath.h ${DESTDIR}${PREFIX}/include
	${INSTALL} ../amathc.h ${DESTDIR}${PREFIX}/include

.PHONY:	uninstall
uninstall:
	${DEL} ${DESTDIR}${PREFIX}/lib/${alib}
	${DEL} ${DESTDIR}${PREFIX}/lib/${solib}
	${DEL} ${DESTDIR}${PREFIX}/include/amath.h
	${DEL} ${DESTDIR}${PREFIX}/include/amathc.h

clean:
	${DEL} static/${alib} ${solib}  static/alloccpy.o static/mem.o static/memcpy.o static/memset.o static/strcmp.o static/strlen.o static/untag.o  shared/alloccpy.o shared/mem.o shared/memcpy.o shared/memset.o shared/strcmp.o shared/strlen.o shared/untag.o

