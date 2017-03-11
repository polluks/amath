
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
INSTALLP = install -m 0755
INSTALLM = install -m 0644
PREFIX   = /usr
INSTDIRP  = ${DESTDIR}${PREFIX}/bin
INSTDIRM  = ${DESTDIR}${PREFIX}/share/man/man1

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

localize:
	cd build/flexcat && ${MAKE}
	${FLXCAT} text/keyword.cd src/localize/kword.h=text/keyword.sd
	${FLXCAT} text/help.cd src/localize/help.h=text/help.sd
	${FLXCAT} text/ident.cd src/localize/ident.h=text/ident.sd
	${FLXCAT} text/text.cd src/localize/text.h=text/text.sd

catalogs:
	cd build/flexcat && ${MAKE}
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
test: amath
	LD_LIBRARY_PATH=src/clib/:src/lib:src/cplex:scr/real
	./amath test

.PHONY: install
install: shared-app
	cd src/lib && ${MAKE} install
	cd src/clib && ${MAKE} install
	cd src/real && ${MAKE} install
	cd src/cplex && ${MAKE} install
	${INSTALLP} amath ${INSTDIRP}/amath
	${INSTALLM} amath.1 ${INSTDIRM}/amath.1

.PHONY: uninstall
uninstall:
	cd src/lib && ${MAKE} uninstall
	cd src/clib && ${MAKE} uninstall
	cd src/real && ${MAKE} uninstall
	cd src/cplex && ${MAKE} uninstall
	${DEL} ${INSTDIRP}/amath
	${DEL} ${INSTDIRM}/amath.1

.PHONY: clean
clean:
	cd src/lib && ${MAKE} clean
	cd src/clib && ${MAKE} clean
	cd src/real && ${MAKE} clean
	cd src/cplex && ${MAKE} clean
	cd src/main && ${MAKE} clean
	cd src/system && ${MAKE} clean
	cd src/main/function && ${MAKE} clean
	cd src/main/statement && ${MAKE} clean
	cd build/flexcat && ${MAKE} clean
	${DEL} src/main.o amath

