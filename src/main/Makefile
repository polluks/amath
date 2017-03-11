CXX      = g++
CXXFLAGS = -O2 -DWITHTEST  -I. -I.. -Wall
AR       = ar
RANLIB   = ranlib
DEL      = rm -f

all: lib
static: lib

evaluator.o:	evaluator.cpp
	${CXX} ${CXXFLAGS} -c evaluator.cpp

functionlist.o:	functionlist.cpp
	${CXX} ${CXXFLAGS} -c functionlist.cpp

fgrid.o:	fgrid.cpp
	${CXX} ${CXXFLAGS} -c fgrid.cpp

lexer.o:	lexer.cpp
	${CXX} ${CXXFLAGS} -c lexer.cpp

nodes.o:	nodes.cpp
	${CXX} ${CXXFLAGS} -c nodes.cpp

operators.o:	operators.cpp
	${CXX} ${CXXFLAGS} -c operators.cpp

optimizer.o:	optimizer.cpp
	${CXX} ${CXXFLAGS} -c optimizer.cpp

parser.o:	parser.cpp
	${CXX} ${CXXFLAGS} -c parser.cpp

token.o:	token.cpp
	${CXX} ${CXXFLAGS} -c token.cpp

userfunction.o:	userfunction.cpp
	${CXX} ${CXXFLAGS} -c userfunction.cpp

values.o:	values.cpp
	${CXX} ${CXXFLAGS} -c values.cpp

viewer.o:	viewer.cpp
	${CXX} ${CXXFLAGS} -c viewer.cpp

lib:	 evaluator.o functionlist.o fgrid.o lexer.o nodes.o operators.o optimizer.o parser.o token.o userfunction.o values.o viewer.o
	${AR} rcs libappmain.a  evaluator.o functionlist.o fgrid.o lexer.o nodes.o operators.o optimizer.o parser.o token.o userfunction.o values.o viewer.o
	${RANLIB} libappmain.a

clean:
	${DEL} libappmain.a  evaluator.o functionlist.o fgrid.o lexer.o nodes.o operators.o optimizer.o parser.o token.o userfunction.o values.o viewer.o

