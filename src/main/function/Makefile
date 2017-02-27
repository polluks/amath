CXX      = x86_64-aros-g++
CXXFLAGS = -O2 -DWITHTEST  -I. -I../.. -Wall
AR       = x86_64-aros-ar
RANLIB   = x86_64-aros-ranlib
DEL      = rm -f

all: lib
static: lib

absolute.o:	absolute.cpp
	${CXX} ${CXXFLAGS} -c absolute.cpp

aexcosecant.o:	aexcosecant.cpp
	${CXX} ${CXXFLAGS} -c aexcosecant.cpp

aexsecant.o:	aexsecant.cpp
	${CXX} ${CXXFLAGS} -c aexsecant.cpp

arccos.o:	arccos.cpp
	${CXX} ${CXXFLAGS} -c arccos.cpp

arcsin.o:	arcsin.cpp
	${CXX} ${CXXFLAGS} -c arcsin.cpp

arctan.o:	arctan.cpp
	${CXX} ${CXXFLAGS} -c arctan.cpp

arccosecant.o:	arccosecant.cpp
	${CXX} ${CXXFLAGS} -c arccosecant.cpp

arccotangent.o:	arccotangent.cpp
	${CXX} ${CXXFLAGS} -c arccotangent.cpp

arcsecant.o:	arcsecant.cpp
	${CXX} ${CXXFLAGS} -c arcsecant.cpp

ceil.o:	ceil.cpp
	${CXX} ${CXXFLAGS} -c ceil.cpp

cosecant.o:	cosecant.cpp
	${CXX} ${CXXFLAGS} -c cosecant.cpp

cosine.o:	cosine.cpp
	${CXX} ${CXXFLAGS} -c cosine.cpp

cotangent.o:	cotangent.cpp
	${CXX} ${CXXFLAGS} -c cotangent.cpp

covercos.o:	covercos.cpp
	${CXX} ${CXXFLAGS} -c covercos.cpp

coversin.o:	coversin.cpp
	${CXX} ${CXXFLAGS} -c coversin.cpp

cube.o:	cube.cpp
	${CXX} ${CXXFLAGS} -c cube.cpp

excosecant.o:	excosecant.cpp
	${CXX} ${CXXFLAGS} -c excosecant.cpp

exsecant.o:	exsecant.cpp
	${CXX} ${CXXFLAGS} -c exsecant.cpp

floor.o:	floor.cpp
	${CXX} ${CXXFLAGS} -c floor.cpp

hacovercos.o:	hacovercos.cpp
	${CXX} ${CXXFLAGS} -c hacovercos.cpp

hacoversin.o:	hacoversin.cpp
	${CXX} ${CXXFLAGS} -c hacoversin.cpp

havercos.o:	havercos.cpp
	${CXX} ${CXXFLAGS} -c havercos.cpp

haversin.o:	haversin.cpp
	${CXX} ${CXXFLAGS} -c haversin.cpp

ln.o:	ln.cpp
	${CXX} ${CXXFLAGS} -c ln.cpp

log10.o:	log10.cpp
	${CXX} ${CXXFLAGS} -c log10.cpp

log2.o:	log2.cpp
	${CXX} ${CXXFLAGS} -c log2.cpp

node.o:	node.cpp
	${CXX} ${CXXFLAGS} -c node.cpp

round.o:	round.cpp
	${CXX} ${CXXFLAGS} -c round.cpp

secant.o:	secant.cpp
	${CXX} ${CXXFLAGS} -c secant.cpp

signum.o:	signum.cpp
	${CXX} ${CXXFLAGS} -c signum.cpp

sine.o:	sine.cpp
	${CXX} ${CXXFLAGS} -c sine.cpp

square.o:	square.cpp
	${CXX} ${CXXFLAGS} -c square.cpp

tangent.o:	tangent.cpp
	${CXX} ${CXXFLAGS} -c tangent.cpp

trunc.o:	trunc.cpp
	${CXX} ${CXXFLAGS} -c trunc.cpp

user.o:	user.cpp
	${CXX} ${CXXFLAGS} -c user.cpp

vercos.o:	vercos.cpp
	${CXX} ${CXXFLAGS} -c vercos.cpp

versin.o:	versin.cpp
	${CXX} ${CXXFLAGS} -c versin.cpp

lib:	 absolute.o aexcosecant.o aexsecant.o arccos.o arcsin.o arctan.o arccosecant.o arccotangent.o arcsecant.o ceil.o cosecant.o cosine.o cotangent.o covercos.o coversin.o cube.o excosecant.o exsecant.o floor.o hacovercos.o hacoversin.o havercos.o haversin.o ln.o log10.o log2.o node.o round.o secant.o signum.o sine.o square.o tangent.o trunc.o user.o vercos.o versin.o
	${AR} rcs libfunctions.a  absolute.o aexcosecant.o aexsecant.o arccos.o arcsin.o arctan.o arccosecant.o arccotangent.o arcsecant.o ceil.o cosecant.o cosine.o cotangent.o covercos.o coversin.o cube.o excosecant.o exsecant.o floor.o hacovercos.o hacoversin.o havercos.o haversin.o ln.o log10.o log2.o node.o round.o secant.o signum.o sine.o square.o tangent.o trunc.o user.o vercos.o versin.o
	${RANLIB} libfunctions.a

clean:
	${DEL} libfunctions.a  absolute.o aexcosecant.o aexsecant.o arccos.o arcsin.o arctan.o arccosecant.o arccotangent.o arcsecant.o ceil.o cosecant.o cosine.o cotangent.o covercos.o coversin.o cube.o excosecant.o exsecant.o floor.o hacovercos.o hacoversin.o havercos.o haversin.o ln.o log10.o log2.o node.o round.o secant.o signum.o sine.o square.o tangent.o trunc.o user.o vercos.o versin.o

