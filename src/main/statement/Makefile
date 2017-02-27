CXX      = g++
CXXFLAGS = -O2 -DWITHTEST  -I. -I../.. -Wall
AR       = ar
RANLIB   = ranlib
DEL      = rm -f

all: lib
static: lib

about.o:	about.cpp
	${CXX} ${CXXFLAGS} -c about.cpp

clear.o:	clear.cpp
	${CXX} ${CXXFLAGS} -c clear.cpp

delete.o:	delete.cpp
	${CXX} ${CXXFLAGS} -c delete.cpp

digits.o:	digits.cpp
	${CXX} ${CXXFLAGS} -c digits.cpp

draw.o:	draw.cpp
	${CXX} ${CXXFLAGS} -c draw.cpp

empty.o:	empty.cpp
	${CXX} ${CXXFLAGS} -c empty.cpp

eval.o:	eval.cpp
	${CXX} ${CXXFLAGS} -c eval.cpp

execute.o:	execute.cpp
	${CXX} ${CXXFLAGS} -c execute.cpp

exit.o:	exit.cpp
	${CXX} ${CXXFLAGS} -c exit.cpp

funcdef.o:	funcdef.cpp
	${CXX} ${CXXFLAGS} -c funcdef.cpp

funclist.o:	funclist.cpp
	${CXX} ${CXXFLAGS} -c funclist.cpp

help.o:	help.cpp
	${CXX} ${CXXFLAGS} -c help.cpp

input.o:	input.cpp
	${CXX} ${CXXFLAGS} -c input.cpp

license.o:	license.cpp
	${CXX} ${CXXFLAGS} -c license.cpp

list.o:	list.cpp
	${CXX} ${CXXFLAGS} -c list.cpp

load.o:	load.cpp
	${CXX} ${CXXFLAGS} -c load.cpp

memory.o:	memory.cpp
	${CXX} ${CXXFLAGS} -c memory.cpp

node.o:	node.cpp
	${CXX} ${CXXFLAGS} -c node.cpp

output.o:	output.cpp
	${CXX} ${CXXFLAGS} -c output.cpp

plot.o:	plot.cpp
	${CXX} ${CXXFLAGS} -c plot.cpp

prefs.o:	prefs.cpp
	${CXX} ${CXXFLAGS} -c prefs.cpp

prompt.o:	prompt.cpp
	${CXX} ${CXXFLAGS} -c prompt.cpp

save.o:	save.cpp
	${CXX} ${CXXFLAGS} -c save.cpp

show.o:	show.cpp
	${CXX} ${CXXFLAGS} -c show.cpp

silent.o:	silent.cpp
	${CXX} ${CXXFLAGS} -c silent.cpp

version.o:	version.cpp
	${CXX} ${CXXFLAGS} -c version.cpp

lib:	 about.o clear.o delete.o digits.o draw.o empty.o eval.o execute.o exit.o funcdef.o funclist.o help.o input.o license.o list.o load.o memory.o node.o output.o plot.o prefs.o prompt.o save.o show.o silent.o version.o
	${AR} rcs libstatement.a  about.o clear.o delete.o digits.o draw.o empty.o eval.o execute.o exit.o funcdef.o funclist.o help.o input.o license.o list.o load.o memory.o node.o output.o plot.o prefs.o prompt.o save.o show.o silent.o version.o
	${RANLIB} libstatement.a

clean:
	${DEL} libstatement.a  about.o clear.o delete.o digits.o draw.o empty.o eval.o execute.o exit.o funcdef.o funclist.o help.o input.o license.o list.o load.o memory.o node.o output.o plot.o prefs.o prompt.o save.o show.o silent.o version.o

