CXX      = g++
CXXFLAGS = -O2 -DWITHTEST  -I. -I.. -Wall
AR       = ar
RANLIB   = ranlib
DEL      = rm -f

all: lib
static: lib

console.o:	console.cpp
	${CXX} ${CXXFLAGS} -c console.cpp

console_amiga.o:	console_amiga.cpp
	${CXX} ${CXXFLAGS} -c console_amiga.cpp

console_stdc.o:	console_stdc.cpp
	${CXX} ${CXXFLAGS} -c console_stdc.cpp

filesystem_amiga.o:	filesystem_amiga.cpp
	${CXX} ${CXXFLAGS} -c filesystem_amiga.cpp

filesystem_stdc.o:	filesystem_stdc.cpp
	${CXX} ${CXXFLAGS} -c filesystem_stdc.cpp

language.o:	language.cpp
	${CXX} ${CXXFLAGS} -c language.cpp

language_amiga.o:	language_amiga.cpp
	${CXX} ${CXXFLAGS} -c language_amiga.cpp

language_posix.o:	language_posix.cpp
	${CXX} ${CXXFLAGS} -c language_posix.cpp

language_stdc.o:	language_stdc.cpp
	${CXX} ${CXXFLAGS} -c language_stdc.cpp

preferences.o:	preferences.cpp
	${CXX} ${CXXFLAGS} -c preferences.cpp

preferences_amiga.o:	preferences_amiga.cpp
	${CXX} ${CXXFLAGS} -c preferences_amiga.cpp

preferences_stdc.o:	preferences_stdc.cpp
	${CXX} ${CXXFLAGS} -c preferences_stdc.cpp

proc_amiga.o:	proc_amiga.cpp
	${CXX} ${CXXFLAGS} -c proc_amiga.cpp

program.o:	program.cpp
	${CXX} ${CXXFLAGS} -c program.cpp

program_amiga.o:	program_amiga.cpp
	${CXX} ${CXXFLAGS} -c program_amiga.cpp

program_stdc.o:	program_stdc.cpp
	${CXX} ${CXXFLAGS} -c program_stdc.cpp

program_test.o:	program_test.cpp
	${CXX} ${CXXFLAGS} -c program_test.cpp

task_amiga.o:	task_amiga.cpp
	${CXX} ${CXXFLAGS} -c task_amiga.cpp

task_stdc.o:	task_stdc.cpp
	${CXX} ${CXXFLAGS} -c task_stdc.cpp

window_amiga.o:	window_amiga.cpp
	${CXX} ${CXXFLAGS} -c window_amiga.cpp

lib:	 console.o console_amiga.o console_stdc.o filesystem_amiga.o filesystem_stdc.o language.o language_amiga.o language_posix.o language_stdc.o preferences.o preferences_amiga.o preferences_stdc.o proc_amiga.o program.o program_amiga.o program_stdc.o program_test.o task_amiga.o task_stdc.o window_amiga.o
	${AR} rcs libappsystem.a  console.o console_amiga.o console_stdc.o filesystem_amiga.o filesystem_stdc.o language.o language_amiga.o language_posix.o language_stdc.o preferences.o preferences_amiga.o preferences_stdc.o proc_amiga.o program.o program_amiga.o program_stdc.o program_test.o task_amiga.o task_stdc.o window_amiga.o
	${RANLIB} libappsystem.a

clean:
	${DEL} libappsystem.a  console.o console_amiga.o console_stdc.o filesystem_amiga.o filesystem_stdc.o language.o language_amiga.o language_posix.o language_stdc.o preferences.o preferences_amiga.o preferences_stdc.o proc_amiga.o program.o program_amiga.o program_stdc.o program_test.o task_amiga.o task_stdc.o window_amiga.o

