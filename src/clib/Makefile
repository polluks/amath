CC        = gcc
CFLAGS    = -std=c9x -O3 -DWITHTEST -I. -I.. -Wall
AR        = ar
RANLIB    = ranlib
MKDIR     = mkdir -p
DEL       = rm -f
INSTALL   = install -m 0644
LDCONFIG  = ldconfig
PREFIX    = /usr
INSTDIR   = ${DESTDIR}${PREFIX}/lib/amath
INSTDIRI  = ${DESTDIR}${PREFIX}/include/amath
INSTDIRPC = ${DESTDIR}${PREFIX}/lib/pkgconfig
INSTDIRM  = ${DESTDIR}${PREFIX}/share/man/man3
alib      = libamathc.a
solib     = libamathc.so
pkgconfig = amathc.pc
manpage   = amathc.3

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
	${CC} ${CFLAGS} -shared -s -fPIC -Wl,-soname,${solib}.1.7.0 -o ${solib}  shared/alloccpy.o shared/mem.o shared/memcpy.o shared/memset.o shared/strcmp.o shared/strlen.o shared/untag.o -lc

${alib}:	build  static/alloccpy.o static/mem.o static/memcpy.o static/memset.o static/strcmp.o static/strlen.o static/untag.o
	${AR} rcs static/${alib}  static/alloccpy.o static/mem.o static/memcpy.o static/memset.o static/strcmp.o static/strlen.o static/untag.o
	${RANLIB} static/${alib}

.PHONY: install
install:	${alib} ${solib}
	${MKDIR} ${INSTDIR}
	${MKDIR} ${INSTDIRPC}
	${MKDIR} ${INSTDIRI}
	${INSTALL} static/${alib} ${INSTDIR}/${alib}
	${INSTALL} ${solib} ${INSTDIR}/${solib}
	${INSTALL} ${pkgconfig} ${INSTDIRPC}/${pkgconfig}
	${INSTALL} ${manpage} ${INSTDIRM}/${manpage}
	${INSTALL} ../amath.h ${INSTDIRI}
	${INSTALL} ../amathc.h ${INSTDIRI}
	${LDCONFIG} ${INSTDIR}

.PHONY:	uninstall
uninstall:
	${DEL} ${INSTDIR}/${alib}
	${DEL} ${INSTDIR}/${solib}
	${DEL} ${INSTDIRPC}/${pkgconfig}
	${DEL} ${INSTDIRM}/${manpage}
	${DEL} ${INSTDIRI}/amath.h
	${DEL} ${INSTDIRI}/amathc.h
	${LDCONFIG}

clean:
	${DEL} static/${alib} ${solib}  static/alloccpy.o static/mem.o static/memcpy.o static/memset.o static/strcmp.o static/strlen.o static/untag.o  shared/alloccpy.o shared/mem.o shared/memcpy.o shared/memset.o shared/strcmp.o shared/strlen.o shared/untag.o

