CXX      = x86_64-aros-g++
CXXFLAGS = -O3 -DWITHTEST  -I. -I.. -Wall
AR       = x86_64-aros-ar
RANLIB   = x86_64-aros-ranlib
MKDIR    = mkdir -p
DEL      = rm -f
INSTALL  = install -m 0644
PREFIX   = /usr

alib     = libamathapp.a
solib    = libamathapp.so

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
	${CC} -shared -fPIC -Wl,-soname,${solib} -o ${solib}  shared/aengine.o shared/charbuf.o shared/integer.o shared/cplex.o shared/nnumb.o shared/ntext.o shared/real.o

${alib}:	build  static/aengine.o static/charbuf.o static/integer.o static/cplex.o static/nnumb.o static/ntext.o static/real.o
	${AR} rcs static/${alib}  static/aengine.o static/charbuf.o static/integer.o static/cplex.o static/nnumb.o static/ntext.o static/real.o
	${RANLIB} static/${alib}

.PHONY:	install
install: ${solib}
	${MKDIR} ${DESTDIR}${PREFIX}/lib
	${INSTALL} ${solib} ${DESTDIR}${PREFIX}/lib/${solib}

.PHONY:	uninstall
uninstall:
	${DEL} ${DESTDIR}${PREFIX}/lib/${solib}

clean:
	${DEL} static/${alib} ${solib}  static/aengine.o static/charbuf.o static/integer.o static/cplex.o static/nnumb.o static/ntext.o static/real.o  shared/aengine.o shared/charbuf.o shared/integer.o shared/cplex.o shared/nnumb.o shared/ntext.o shared/real.o

