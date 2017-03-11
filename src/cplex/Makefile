CC        = gcc
CFLAGS    = -std=c9x -O3 -DWITHTEST  -I. -I.. -Wall
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
alib      = libamathcplex.a
solib     = libamathcplex.so
pkgconfig = amathi.pc
manpage   = amathi.3

all: static shared

static: ${alib}

shared: ${solib}

static/cacos.o:	cacos.c
	${CC} ${CFLAGS} -fno-builtin -c cacos.c -o static/cacos.o

shared/cacos.o:	cacos.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c cacos.c -o shared/cacos.o

static/cacosh.o:	cacosh.c
	${CC} ${CFLAGS} -fno-builtin -c cacosh.c -o static/cacosh.o

shared/cacosh.o:	cacosh.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c cacosh.c -o shared/cacosh.o

static/cacot.o:	cacot.c
	${CC} ${CFLAGS} -fno-builtin -c cacot.c -o static/cacot.o

shared/cacot.o:	cacot.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c cacot.c -o shared/cacot.o

static/cacoth.o:	cacoth.c
	${CC} ${CFLAGS} -fno-builtin -c cacoth.c -o static/cacoth.o

shared/cacoth.o:	cacoth.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c cacoth.c -o shared/cacoth.o

static/cacsc.o:	cacsc.c
	${CC} ${CFLAGS} -fno-builtin -c cacsc.c -o static/cacsc.o

shared/cacsc.o:	cacsc.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c cacsc.c -o shared/cacsc.o

static/cacsch.o:	cacsch.c
	${CC} ${CFLAGS} -fno-builtin -c cacsch.c -o static/cacsch.o

shared/cacsch.o:	cacsch.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c cacsch.c -o shared/cacsch.o

static/casec.o:	casec.c
	${CC} ${CFLAGS} -fno-builtin -c casec.c -o static/casec.o

shared/casec.o:	casec.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c casec.c -o shared/casec.o

static/casech.o:	casech.c
	${CC} ${CFLAGS} -fno-builtin -c casech.c -o static/casech.o

shared/casech.o:	casech.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c casech.c -o shared/casech.o

static/casin.o:	casin.c
	${CC} ${CFLAGS} -fno-builtin -c casin.c -o static/casin.o

shared/casin.o:	casin.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c casin.c -o shared/casin.o

static/casinh.o:	casinh.c
	${CC} ${CFLAGS} -fno-builtin -c casinh.c -o static/casinh.o

shared/casinh.o:	casinh.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c casinh.c -o shared/casinh.o

static/catan.o:	catan.c
	${CC} ${CFLAGS} -fno-builtin -c catan.c -o static/catan.o

shared/catan.o:	catan.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c catan.c -o shared/catan.o

static/catanh.o:	catanh.c
	${CC} ${CFLAGS} -fno-builtin -c catanh.c -o static/catanh.o

shared/catanh.o:	catanh.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c catanh.c -o shared/catanh.o

static/ccbrt.o:	ccbrt.c
	${CC} ${CFLAGS} -fno-builtin -c ccbrt.c -o static/ccbrt.o

shared/ccbrt.o:	ccbrt.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c ccbrt.c -o shared/ccbrt.o

static/ccos.o:	ccos.c
	${CC} ${CFLAGS} -fno-builtin -c ccos.c -o static/ccos.o

shared/ccos.o:	ccos.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c ccos.c -o shared/ccos.o

static/ccosh.o:	ccosh.c
	${CC} ${CFLAGS} -fno-builtin -c ccosh.c -o static/ccosh.o

shared/ccosh.o:	ccosh.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c ccosh.c -o shared/ccosh.o

static/ccot.o:	ccot.c
	${CC} ${CFLAGS} -fno-builtin -c ccot.c -o static/ccot.o

shared/ccot.o:	ccot.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c ccot.c -o shared/ccot.o

static/ccoth.o:	ccoth.c
	${CC} ${CFLAGS} -fno-builtin -c ccoth.c -o static/ccoth.o

shared/ccoth.o:	ccoth.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c ccoth.c -o shared/ccoth.o

static/ccsc.o:	ccsc.c
	${CC} ${CFLAGS} -fno-builtin -c ccsc.c -o static/ccsc.o

shared/ccsc.o:	ccsc.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c ccsc.c -o shared/ccsc.o

static/ccsch.o:	ccsch.c
	${CC} ${CFLAGS} -fno-builtin -c ccsch.c -o static/ccsch.o

shared/ccsch.o:	ccsch.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c ccsch.c -o shared/ccsch.o

static/cexp.o:	cexp.c
	${CC} ${CFLAGS} -fno-builtin -c cexp.c -o static/cexp.o

shared/cexp.o:	cexp.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c cexp.c -o shared/cexp.o

static/clog.o:	clog.c
	${CC} ${CFLAGS} -fno-builtin -c clog.c -o static/clog.o

shared/clog.o:	clog.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c clog.c -o shared/clog.o

static/clog10.o:	clog10.c
	${CC} ${CFLAGS} -fno-builtin -c clog10.c -o static/clog10.o

shared/clog10.o:	clog10.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c clog10.c -o shared/clog10.o

static/clogb.o:	clogb.c
	${CC} ${CFLAGS} -fno-builtin -c clogb.c -o static/clogb.o

shared/clogb.o:	clogb.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c clogb.c -o shared/clogb.o

static/cpow.o:	cpow.c
	${CC} ${CFLAGS} -fno-builtin -c cpow.c -o static/cpow.o

shared/cpow.o:	cpow.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c cpow.c -o shared/cpow.o

static/csec.o:	csec.c
	${CC} ${CFLAGS} -fno-builtin -c csec.c -o static/csec.o

shared/csec.o:	csec.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c csec.c -o shared/csec.o

static/csech.o:	csech.c
	${CC} ${CFLAGS} -fno-builtin -c csech.c -o static/csech.o

shared/csech.o:	csech.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c csech.c -o shared/csech.o

static/csgn.o:	csgn.c
	${CC} ${CFLAGS} -fno-builtin -c csgn.c -o static/csgn.o

shared/csgn.o:	csgn.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c csgn.c -o shared/csgn.o

static/csin.o:	csin.c
	${CC} ${CFLAGS} -fno-builtin -c csin.c -o static/csin.o

shared/csin.o:	csin.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c csin.c -o shared/csin.o

static/csinh.o:	csinh.c
	${CC} ${CFLAGS} -fno-builtin -c csinh.c -o static/csinh.o

shared/csinh.o:	csinh.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c csinh.c -o shared/csinh.o

static/csqrt.o:	csqrt.c
	${CC} ${CFLAGS} -fno-builtin -c csqrt.c -o static/csqrt.o

shared/csqrt.o:	csqrt.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c csqrt.c -o shared/csqrt.o

static/ctan.o:	ctan.c
	${CC} ${CFLAGS} -fno-builtin -c ctan.c -o static/ctan.o

shared/ctan.o:	ctan.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c ctan.c -o shared/ctan.o

static/ctanh.o:	ctanh.c
	${CC} ${CFLAGS} -fno-builtin -c ctanh.c -o static/ctanh.o

shared/ctanh.o:	ctanh.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c ctanh.c -o shared/ctanh.o

static/prim.o:	prim.c
	${CC} ${CFLAGS} -fno-builtin -c prim.c -o static/prim.o

shared/prim.o:	prim.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c prim.c -o shared/prim.o

.PHONY: build
build:
	${MKDIR} static
	${MKDIR} shared

${solib}:	build  shared/cacos.o shared/cacosh.o shared/cacot.o shared/cacoth.o shared/cacsc.o shared/cacsch.o shared/casec.o shared/casech.o shared/casin.o shared/casinh.o shared/catan.o shared/catanh.o shared/ccbrt.o shared/ccos.o shared/ccosh.o shared/ccot.o shared/ccoth.o shared/ccsc.o shared/ccsch.o shared/cexp.o shared/clog.o shared/clog10.o shared/clogb.o shared/cpow.o shared/csec.o shared/csech.o shared/csgn.o shared/csin.o shared/csinh.o shared/csqrt.o shared/ctan.o shared/ctanh.o shared/prim.o
	${CC} ${CFLAGS} -shared -s -fPIC -Wl,-soname,${solib}.1.7.0 -o ${solib}  shared/cacos.o shared/cacosh.o shared/cacot.o shared/cacoth.o shared/cacsc.o shared/cacsch.o shared/casec.o shared/casech.o shared/casin.o shared/casinh.o shared/catan.o shared/catanh.o shared/ccbrt.o shared/ccos.o shared/ccosh.o shared/ccot.o shared/ccoth.o shared/ccsc.o shared/ccsch.o shared/cexp.o shared/clog.o shared/clog10.o shared/clogb.o shared/cpow.o shared/csec.o shared/csech.o shared/csgn.o shared/csin.o shared/csinh.o shared/csqrt.o shared/ctan.o shared/ctanh.o shared/prim.o

${alib}:	build  static/cacos.o static/cacosh.o static/cacot.o static/cacoth.o static/cacsc.o static/cacsch.o static/casec.o static/casech.o static/casin.o static/casinh.o static/catan.o static/catanh.o static/ccbrt.o static/ccos.o static/ccosh.o static/ccot.o static/ccoth.o static/ccsc.o static/ccsch.o static/cexp.o static/clog.o static/clog10.o static/clogb.o static/cpow.o static/csec.o static/csech.o static/csgn.o static/csin.o static/csinh.o static/csqrt.o static/ctan.o static/ctanh.o static/prim.o
	${AR} rcs static/${alib}  static/cacos.o static/cacosh.o static/cacot.o static/cacoth.o static/cacsc.o static/cacsch.o static/casec.o static/casech.o static/casin.o static/casinh.o static/catan.o static/catanh.o static/ccbrt.o static/ccos.o static/ccosh.o static/ccot.o static/ccoth.o static/ccsc.o static/ccsch.o static/cexp.o static/clog.o static/clog10.o static/clogb.o static/cpow.o static/csec.o static/csech.o static/csgn.o static/csin.o static/csinh.o static/csqrt.o static/ctan.o static/ctanh.o static/prim.o
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
	${INSTALL} ../complex.h ${INSTDIRI}/amathi.h
	${LDCONFIG} ${INSTDIR}

.PHONY: uninstall
uninstall:
	${DEL} ${INSTDIR}/${alib}
	${DEL} ${INSTDIR}/${solib}
	${DEL} ${INSTDIRPC}/${pkgconfig}
	${DEL} ${INSTDIRM}/${manpage}
	${DEL} ${INSTDIRPC}/amathi.pc
	${DEL} ${INSTDIRI}/amathi.h
	${LDCONFIG}

clean:
	${DEL} static/${alib} ${solib}  static/cacos.o static/cacosh.o static/cacot.o static/cacoth.o static/cacsc.o static/cacsch.o static/casec.o static/casech.o static/casin.o static/casinh.o static/catan.o static/catanh.o static/ccbrt.o static/ccos.o static/ccosh.o static/ccot.o static/ccoth.o static/ccsc.o static/ccsch.o static/cexp.o static/clog.o static/clog10.o static/clogb.o static/cpow.o static/csec.o static/csech.o static/csgn.o static/csin.o static/csinh.o static/csqrt.o static/ctan.o static/ctanh.o static/prim.o  shared/cacos.o shared/cacosh.o shared/cacot.o shared/cacoth.o shared/cacsc.o shared/cacsch.o shared/casec.o shared/casech.o shared/casin.o shared/casinh.o shared/catan.o shared/catanh.o shared/ccbrt.o shared/ccos.o shared/ccosh.o shared/ccot.o shared/ccoth.o shared/ccsc.o shared/ccsch.o shared/cexp.o shared/clog.o shared/clog10.o shared/clogb.o shared/cpow.o shared/csec.o shared/csech.o shared/csgn.o shared/csin.o shared/csinh.o shared/csqrt.o shared/ctan.o shared/ctanh.o shared/prim.o

