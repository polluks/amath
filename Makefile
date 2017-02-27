
CC       = gcc
CXX      = g++
CFLAGS   = -O2 -DWITHTEST -Wall -Isrc -Isrc/main
CXXFLAGS = -O2 -DWITHTEST  -Wall -Isrc -Isrc/main
AR       = ar
RANLIB   = ranlib
LFLAGS   = -lappsystem -lfunctions -lstatement -lappmain -lfunctions -lstatement -lappmain -lamathapp -lamathcplex -lamath -lamathc -lstdc++
LPATH    = -Lsrc/lib -Lsrc/clib -Lsrc/real -Lsrc/cplex -Lsrc/main/function -Lsrc/main/statement -Lsrc/main -Lsrc/system
LPATHS   = -Lsrc/lib/static -Lsrc/clib/static -Lsrc/real/static -Lsrc/cplex/static -Lsrc/main/function -Lsrc/main/statement -Lsrc/main -Lsrc/system
FLXCAT   = build/flexcat/flexcat
MKDIR    = mkdir -p
DEL      = rm -f
INSTALL  = install -m 0755
PREFIX   = /usr

all:	shared-app
app:	appmain functions statement appsystem
libs:	amathapp amath amathc amathcplex

amath:	static-app
static:	static-app

src/main.o:	src/main.cpp
	${CXX} ${CXXFLAGS} -c src/main.cpp -o src/main.o

appmain:
	cd src/main && ${MAKE}

appsystem:
	cd src/system && ${MAKE}

functions:
	cd src/main/function && ${MAKE}

statement:
	cd src/main/statement && ${MAKE}

amathapp:
	cd src/lib && ${MAKE}

amath:
	cd src/real && ${MAKE}

amathc:
	cd src/clib && ${MAKE}

amathcplex:
	cd src/cplex && ${MAKE}

catalogsa:
	${FLXCAT} text/keyword.cd src/localize/kword.h=text/keyword.sd
	${FLXCAT} text/help.cd src/localize/help.h=text/help.sd
	${FLXCAT} text/ident.cd src/localize/ident.h=text/ident.sd
	${FLXCAT} text/text.cd src/localize/text.h=text/text.sd

catalogsu:
	iconv -f ISO-8859-15 -t UTF-8 catalog/dansk/amath-help.ct >utext/dk-help.dict
	iconv -f ISO-8859-15 -t UTF-8 catalog/dansk/amath-ident.ct >utext/dk-ident.dict
	iconv -f ISO-8859-15 -t UTF-8 catalog/dansk/amath-text.ct >utext/dk-text.dict
	iconv -f ISO-8859-15 -t UTF-8 catalog/dansk/amath-keyword.ct >utext/dk-keyword.dict

catalogsw:
	iconv -f ISO-8859-15 -t CP850 catalog/dansk/amath-help.ct >utext/dk-help.dict
	iconv -f ISO-8859-15 -t CP850 catalog/dansk/amath-ident.ct >utext/dk-ident.dict
	iconv -f ISO-8859-15 -t CP850 catalog/dansk/amath-text.ct >utext/dk-text.dict
	iconv -f ISO-8859-15 -t CP850 catalog/dansk/amath-keyword.ct >utext/dk-keyword.dict

amigacatalogs:
	${MKDIR}  dist/catalog/english
	${FLXCAT} text/help.cd catalog/english/amath-help.ct CATALOG dist/catalog/english/amath-help.catalog
	${FLXCAT} text/ident.cd catalog/english/amath-ident.ct CATALOG dist/catalog/english/amath-ident.catalog
	${FLXCAT} text/text.cd catalog/english/amath-text.ct CATALOG dist/catalog/english/amath-text.catalog
	${MKDIR}  dist/catalog/dansk
	${FLXCAT} text/help.cd catalog/dansk/amath-help.ct CATALOG dist/catalog/dansk/amath-help.catalog
	${FLXCAT} text/ident.cd catalog/dansk/amath-ident.ct CATALOG dist/catalog/dansk/amath-ident.catalog
	${FLXCAT} text/text.cd catalog/dansk/amath-text.ct CATALOG dist/catalog/dansk/amath-text.catalog
	${FLXCAT} text/keyword.cd catalog/dansk/amath-keyword.ct CATALOG dist/catalog/dansk/amath-keyword.catalog

shared-app:	app libs src/main.o
	${CC} ${CFLAGS} -s src/main.o -o amath ${LPATH} ${LFLAGS}

static-app: src/main.o
	cd src/lib && ${MAKE} static
	cd src/clib && ${MAKE} static
	cd src/real && ${MAKE} static
	cd src/cplex && ${MAKE} static
	cd src/main && ${MAKE} static
	cd src/system && ${MAKE} static
	cd src/main/function && ${MAKE} static
	cd src/main/statement && ${MAKE} static
	${CC} ${CFLAGS} -s src/main.o -o amath ${LPATHS} ${LFLAGS}

.PHONY: test
test: static-app
	./amath test

.PHONY: install
install: amath
	cd src/lib && ${MAKE} install
	cd src/clib && ${MAKE} install
	cd src/real && ${MAKE} install
	cd src/cplex && ${MAKE} install
	${INSTALL} amath ${DESTDIR}${PREFIX}/bin

.PHONY: uninstall
uninstall:
	cd src/lib && ${MAKE} uninstall
	cd src/clib && ${MAKE} uninstall
	cd src/real && ${MAKE} uninstall
	cd src/cplex && ${MAKE} uninstall
	${DEL} ${DESTDIR}${PREFIX}/bin/amath

clean:
	cd src/lib && ${MAKE} clean
	cd src/clib && ${MAKE} clean
	cd src/real && ${MAKE} clean
	cd src/cplex && ${MAKE} clean
	cd src/main && ${MAKE} clean
	cd src/system && ${MAKE} clean
	cd src/main/function && ${MAKE} clean
	cd src/main/statement && ${MAKE} clean
	${DEL} src/main.o amath

