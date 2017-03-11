CXX       = g++
CXXFLAGS  = -O3 -DWITHTEST  -I. -I.. -Wall
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
alib      = libamathapp.a
solib     = libamathapp.so
pkgconfig = amatha.pc

all: static shared

static: ${alib}

shared: ${solib}

static/aengine.o:	aengine.cpp
	${CXX} ${CXXFLAGS} -c aengine.cpp -o static/aengine.o

shared/aengine.o:	aengine.cpp
	${CXX} ${CXXFLAGS} -fPIC -c aengine.cpp -o shared/aengine.o

static/charbuf.o:	charbuf.cpp
	${CXX} ${CXXFLAGS} -c charbuf.cpp -o static/charbuf.o

shared/charbuf.o:	charbuf.cpp
	${CXX} ${CXXFLAGS} -fPIC -c charbuf.cpp -o shared/charbuf.o

static/integer.o:	integer.cpp
	${CXX} ${CXXFLAGS} -c integer.cpp -o static/integer.o

shared/integer.o:	integer.cpp
	${CXX} ${CXXFLAGS} -fPIC -c integer.cpp -o shared/integer.o

static/cplex.o:	cplex.cpp
	${CXX} ${CXXFLAGS} -c cplex.cpp -o static/cplex.o

shared/cplex.o:	cplex.cpp
	${CXX} ${CXXFLAGS} -fPIC -c cplex.cpp -o shared/cplex.o

static/nnumb.o:	nnumb.cpp
	${CXX} ${CXXFLAGS} -c nnumb.cpp -o static/nnumb.o

shared/nnumb.o:	nnumb.cpp
	${CXX} ${CXXFLAGS} -fPIC -c nnumb.cpp -o shared/nnumb.o

static/ntext.o:	ntext.cpp
	${CXX} ${CXXFLAGS} -c ntext.cpp -o static/ntext.o

shared/ntext.o:	ntext.cpp
	${CXX} ${CXXFLAGS} -fPIC -c ntext.cpp -o shared/ntext.o

static/real.o:	real.cpp
	${CXX} ${CXXFLAGS} -c real.cpp -o static/real.o

shared/real.o:	real.cpp
	${CXX} ${CXXFLAGS} -fPIC -c real.cpp -o shared/real.o

.PHONY: build
build:
	${MKDIR} static
	${MKDIR} shared

${solib}:	build  shared/aengine.o shared/charbuf.o shared/integer.o shared/cplex.o shared/nnumb.o shared/ntext.o shared/real.o
	${CXX} ${CXXFLAGS} -shared -s -fPIC -Wl,-soname,${solib}.1.7.0 -o ${solib}  shared/aengine.o shared/charbuf.o shared/integer.o shared/cplex.o shared/nnumb.o shared/ntext.o shared/real.o

${alib}:	build  static/aengine.o static/charbuf.o static/integer.o static/cplex.o static/nnumb.o static/ntext.o static/real.o
	${AR} rcs static/${alib}  static/aengine.o static/charbuf.o static/integer.o static/cplex.o static/nnumb.o static/ntext.o static/real.o
	${RANLIB} static/${alib}

.PHONY: install
install:	${alib} ${solib}
	${MKDIR} ${INSTDIR}
	${MKDIR} ${INSTDIRPC}
	${MKDIR} ${INSTDIRI}
	${INSTALL} static/${alib} ${INSTDIR}/${alib}
	${INSTALL} ${solib} ${INSTDIR}/${solib}
	${INSTALL} ${pkgconfig} ${INSTDIRPC}/${pkgconfig}
	${INSTALL} aengine.h ${INSTDIRI}/aengine.h
	${INSTALL} charbuf.h ${INSTDIRI}/charbuf.h
	${INSTALL} cplex.h ${INSTDIRI}/cplex.h
	${INSTALL} integer.h ${INSTDIRI}/integer.h
	${INSTALL} nnumb.h ${INSTDIRI}/nnumb.h
	${INSTALL} ntext.h ${INSTDIRI}/ntext.h
	${INSTALL} numb.h ${INSTDIRI}/numb.h
	${INSTALL} real.h ${INSTDIRI}/real.h
	${LDCONFIG} ${INSTDIR}

.PHONY:	uninstall
uninstall:
	${DEL} ${INSTDIR}/${alib}
	${DEL} ${INSTDIR}/${solib}
	${DEL} ${INSTDIRPC}/${pkgconfig}
	${DEL} ${INSTDIRI}/aengine.h
	${DEL} ${INSTDIRI}/charbuf.h
	${DEL} ${INSTDIRI}/cplex.h
	${DEL} ${INSTDIRI}/integer.h
	${DEL} ${INSTDIRI}/nnumb.h
	${DEL} ${INSTDIRI}/ntext.h
	${DEL} ${INSTDIRI}/numb.h
	${DEL} ${INSTDIRI}/real.h
	${LDCONFIG}

clean:
	${DEL} static/${alib} ${solib}  static/aengine.o static/charbuf.o static/integer.o static/cplex.o static/nnumb.o static/ntext.o static/real.o  shared/aengine.o shared/charbuf.o shared/integer.o shared/cplex.o shared/nnumb.o shared/ntext.o shared/real.o

