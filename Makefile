# Portable Makefile generated by configure

all:	libs app

CC     = gcc
AR     = ar
RANLIB = ranlib
CFLAGS =  -DWITHTEST -I. -Wall -Werror
LFLAGS = -lstdc++ -lamathapp -lcamath -lcomplex -lamath

FLXCAT = flexcat
MKDIR  = mkdir
COPY   = cp
DEL    = rm -f
DELREC = rm -Rf

evaluator.o:	app/main/evaluator.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/main/evaluator.cpp

functions.o:	app/main/functions.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/main/functions.cpp

graphlist.o:	app/main/graphlist.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/main/graphlist.cpp

lexer.o:	app/main/lexer.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/main/lexer.cpp

nodes.o:	app/main/nodes.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/main/nodes.cpp

operators.o:	app/main/operators.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/main/operators.cpp

optimizer.o:	app/main/optimizer.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/main/optimizer.cpp

parser.o:	app/main/parser.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/main/parser.cpp

statements.o:	app/main/statements.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/main/statements.cpp

token.o:	app/main/token.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/main/token.cpp

values.o:	app/main/values.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/main/values.cpp

viewer.o:	app/main/viewer.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/main/viewer.cpp

console.o:	app/system/console.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/console.cpp

console_amiga.o:	app/system/console_amiga.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/console_amiga.cpp

console_stdc.o:	app/system/console_stdc.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/console_stdc.cpp

filesystem_amiga.o:	app/system/filesystem_amiga.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/filesystem_amiga.cpp

filesystem_stdc.o:	app/system/filesystem_stdc.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/filesystem_stdc.cpp

graph.o:	app/system/graph.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/graph.cpp

graph_amiga.o:	app/system/graph_amiga.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/graph_amiga.cpp

graph_gtk.o:	app/system/graph_gtk.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/graph_gtk.cpp

language.o:	app/system/language.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/language.cpp

language_amiga.o:	app/system/language_amiga.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/language_amiga.cpp

language_stdc.o:	app/system/language_stdc.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/language_stdc.cpp

preferences.o:	app/system/preferences.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/preferences.cpp

preferences_amiga.o:	app/system/preferences_amiga.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/preferences_amiga.cpp

preferences_stdc.o:	app/system/preferences_stdc.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/preferences_stdc.cpp

proc_amiga.o:	app/system/proc_amiga.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/proc_amiga.cpp

program.o:	app/system/program.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/program.cpp

program_amiga.o:	app/system/program_amiga.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/program_amiga.cpp

program_stdc.o:	app/system/program_stdc.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/program_stdc.cpp

program_test.o:	app/system/program_test.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/program_test.cpp

task_amiga.o:	app/system/task_amiga.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/task_amiga.cpp

task_stdc.o:	app/system/task_stdc.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/task_stdc.cpp

window_amiga.o:	app/system/window_amiga.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/window_amiga.cpp

io.o:	app/system/base/io.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/system/base/io.cpp

main.o:	app/main.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/main.cpp

aengine.o:	app/lib/aengine.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/lib/aengine.cpp

charbuf.o:	app/lib/charbuf.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/lib/charbuf.cpp

cplex.o:	app/lib/cplex.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/lib/cplex.cpp

fgrid.o:	app/lib/fgrid.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/lib/fgrid.cpp

ntext.o:	app/lib/ntext.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/lib/ntext.cpp

real.o:	app/lib/real.cpp
	${CC} -O0 -g ${CFLAGS} -Ilib -Iapp -Wall -Werror -c app/lib/real.cpp

acos.o:	lib/real/acos.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/acos.c

acosh.o:	lib/real/acosh.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/acosh.c

asin.o:	lib/real/asin.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/asin.c

asinh.o:	lib/real/asinh.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/asinh.c

atan.o:	lib/real/atan.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/atan.c

atan2.o:	lib/real/atan2.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/atan2.c

atanh.o:	lib/real/atanh.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/atanh.c

cbrt.o:	lib/real/cbrt.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/cbrt.c

ceil.o:	lib/real/ceil.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/ceil.c

copysign.o:	lib/real/copysign.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/copysign.c

cos.o:	lib/real/cos.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/cos.c

cosh.o:	lib/real/cosh.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/cosh.c

exp.o:	lib/real/exp.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/exp.c

expm1.o:	lib/real/expm1.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/expm1.c

fabs.o:	lib/real/fabs.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/fabs.c

finite.o:	lib/real/finite.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/finite.c

floor.o:	lib/real/floor.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/floor.c

fmod.o:	lib/real/fmod.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/fmod.c

hypot.o:	lib/real/hypot.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/hypot.c

isnan.o:	lib/real/isnan.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/isnan.c

kcos.o:	lib/real/kcos.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/kcos.c

kremp2.o:	lib/real/kremp2.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/kremp2.c

ksin.o:	lib/real/ksin.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/ksin.c

ktan.o:	lib/real/ktan.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/ktan.c

log.o:	lib/real/log.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/log.c

log10.o:	lib/real/log10.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/log10.c

log1p.o:	lib/real/log1p.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/log1p.c

pow.o:	lib/real/pow.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/pow.c

remp2.o:	lib/real/remp2.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/remp2.c

round.o:	lib/real/round.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/round.c

scalbn.o:	lib/real/scalbn.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/scalbn.c

sin.o:	lib/real/sin.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/sin.c

sinh.o:	lib/real/sinh.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/sinh.c

sqrt.o:	lib/real/sqrt.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/sqrt.c

tan.o:	lib/real/tan.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/tan.c

tanh.o:	lib/real/tanh.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/tanh.c

trunc.o:	lib/real/trunc.c
	${CC} -O0 -g -std=c9x -fno-builtin -fno-strict-aliasing -ffloat-store -Wall -Werror -Ilib -Ilib/real -c lib/real/trunc.c

cacos.o:	lib/cplex/cacos.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/cacos.c

cacosh.o:	lib/cplex/cacosh.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/cacosh.c

cacot.o:	lib/cplex/cacot.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/cacot.c

cacoth.o:	lib/cplex/cacoth.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/cacoth.c

cacsc.o:	lib/cplex/cacsc.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/cacsc.c

cacsch.o:	lib/cplex/cacsch.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/cacsch.c

casec.o:	lib/cplex/casec.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/casec.c

casech.o:	lib/cplex/casech.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/casech.c

casin.o:	lib/cplex/casin.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/casin.c

casinh.o:	lib/cplex/casinh.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/casinh.c

catan.o:	lib/cplex/catan.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/catan.c

catanh.o:	lib/cplex/catanh.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/catanh.c

ccbrt.o:	lib/cplex/ccbrt.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/ccbrt.c

ccos.o:	lib/cplex/ccos.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/ccos.c

ccosh.o:	lib/cplex/ccosh.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/ccosh.c

ccot.o:	lib/cplex/ccot.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/ccot.c

ccoth.o:	lib/cplex/ccoth.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/ccoth.c

ccsc.o:	lib/cplex/ccsc.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/ccsc.c

ccsch.o:	lib/cplex/ccsch.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/ccsch.c

cexp.o:	lib/cplex/cexp.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/cexp.c

clog.o:	lib/cplex/clog.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/clog.c

clog10.o:	lib/cplex/clog10.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/clog10.c

clogb.o:	lib/cplex/clogb.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/clogb.c

cpow.o:	lib/cplex/cpow.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/cpow.c

csec.o:	lib/cplex/csec.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/csec.c

csech.o:	lib/cplex/csech.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/csech.c

csgn.o:	lib/cplex/csgn.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/csgn.c

csin.o:	lib/cplex/csin.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/csin.c

csinh.o:	lib/cplex/csinh.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/csinh.c

csqrt.o:	lib/cplex/csqrt.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/csqrt.c

ctan.o:	lib/cplex/ctan.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/ctan.c

ctanh.o:	lib/cplex/ctanh.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/ctanh.c

prim.o:	lib/cplex/prim.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -Ilib/cplex -c lib/cplex/prim.c

alloccpy.o:	lib/clib/alloccpy.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -c lib/clib/alloccpy.c

mem.o:	lib/clib/mem.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -c lib/clib/mem.c

memcpy.o:	lib/clib/memcpy.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -c lib/clib/memcpy.c

memset.o:	lib/clib/memset.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -c lib/clib/memset.c

strcmp.o:	lib/clib/strcmp.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -c lib/clib/strcmp.c

strlen.o:	lib/clib/strlen.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -c lib/clib/strlen.c

untag.o:	lib/clib/untag.c
	${CC} -O0 -g -std=c9x -fno-builtin -Wall -Werror -Ilib -c lib/clib/untag.c

dragon4.o:	lib/dconv/dragon4.cpp
	${CC} -O0 -g -fno-builtin -Wall -Werror -Ilib -Ilib/dconv -c lib/dconv/dragon4.cpp

dmath.o:	lib/dconv/dmath.cpp
	${CC} -O0 -g -fno-builtin -Wall -Werror -Ilib -Ilib/dconv -c lib/dconv/dmath.cpp

dprint.o:	lib/dconv/dprint.cpp
	${CC} -O0 -g -fno-builtin -Wall -Werror -Ilib -Ilib/dconv -c lib/dconv/dprint.cpp

libs:	libamath libcomplex libcamath libamathapp

catalogs:	
	${FLXCAT} text/keyword.cd app/localize/kword.h=text/keyword.sd
	${FLXCAT} text/help.cd app/localize/help.h=text/help.sd
	${FLXCAT} text/ident-clean.cd app/localize/ident.h=text/ident.sd
	${FLXCAT} text/text.cd app/localize/text.h=text/text.sd

libamathapp:	 aengine.o charbuf.o cplex.o fgrid.o ntext.o real.o
	${AR} rcs libamathapp.a  aengine.o charbuf.o cplex.o fgrid.o ntext.o real.o
	${RANLIB} libamathapp.a

libamath:	 acos.o acosh.o asin.o asinh.o atan.o atan2.o atanh.o cbrt.o ceil.o copysign.o cos.o cosh.o exp.o expm1.o fabs.o finite.o floor.o fmod.o hypot.o isnan.o kcos.o kremp2.o ksin.o ktan.o log.o log10.o log1p.o pow.o remp2.o round.o scalbn.o sin.o sinh.o sqrt.o tan.o tanh.o trunc.o
	${AR} rcs libamath.a  acos.o acosh.o asin.o asinh.o atan.o atan2.o atanh.o cbrt.o ceil.o copysign.o cos.o cosh.o exp.o expm1.o fabs.o finite.o floor.o fmod.o hypot.o isnan.o kcos.o kremp2.o ksin.o ktan.o log.o log10.o log1p.o pow.o remp2.o round.o scalbn.o sin.o sinh.o sqrt.o tan.o tanh.o trunc.o
	${RANLIB} libamath.a

libcomplex:	 cacos.o cacosh.o cacot.o cacoth.o cacsc.o cacsch.o casec.o casech.o casin.o casinh.o catan.o catanh.o ccbrt.o ccos.o ccosh.o ccot.o ccoth.o ccsc.o ccsch.o cexp.o clog.o clog10.o clogb.o cpow.o csec.o csech.o csgn.o csin.o csinh.o csqrt.o ctan.o ctanh.o prim.o
	${AR} rcs libcomplex.a  cacos.o cacosh.o cacot.o cacoth.o cacsc.o cacsch.o casec.o casech.o casin.o casinh.o catan.o catanh.o ccbrt.o ccos.o ccosh.o ccot.o ccoth.o ccsc.o ccsch.o cexp.o clog.o clog10.o clogb.o cpow.o csec.o csech.o csgn.o csin.o csinh.o csqrt.o ctan.o ctanh.o prim.o
	${RANLIB} libcomplex.a

libcamath:	 alloccpy.o mem.o memcpy.o memset.o strcmp.o strlen.o untag.o dragon4.o dmath.o dprint.o
	${AR} rcs libcamath.a  alloccpy.o mem.o memcpy.o memset.o strcmp.o strlen.o untag.o dragon4.o dmath.o dprint.o
	${RANLIB} libcamath.a

app:	libs  evaluator.o functions.o graphlist.o lexer.o nodes.o operators.o optimizer.o parser.o statements.o token.o values.o viewer.o console.o console_amiga.o console_stdc.o filesystem_amiga.o filesystem_stdc.o graph.o graph_amiga.o graph_gtk.o language.o language_amiga.o language_stdc.o preferences.o preferences_amiga.o preferences_stdc.o proc_amiga.o program.o program_amiga.o program_stdc.o program_test.o task_amiga.o task_stdc.o window_amiga.o io.o main.o
	${CC} ${CFLAGS}  -L. -o amath  evaluator.o functions.o graphlist.o lexer.o nodes.o operators.o optimizer.o parser.o statements.o token.o values.o viewer.o console.o console_amiga.o console_stdc.o filesystem_amiga.o filesystem_stdc.o graph.o graph_amiga.o graph_gtk.o language.o language_amiga.o language_stdc.o preferences.o preferences_amiga.o preferences_stdc.o proc_amiga.o program.o program_amiga.o program_stdc.o program_test.o task_amiga.o task_stdc.o window_amiga.o io.o main.o ${LFLAGS}

dist: app
	${MKDIR} dist
	${MKDIR} dist/catalog
	${MKDIR} dist/catalog/english
	${FLXCAT} text/help.cd catalog/english/amath-help.ct CATALOG dist/catalog/english/amath-help.catalog
	${FLXCAT} text/ident.cd catalog/english/amath-ident.ct CATALOG dist/catalog/english/amath-ident.catalog
	${FLXCAT} text/text.cd catalog/english/amath-text.ct CATALOG dist/catalog/english/amath-text.catalog
	${MKDIR} dist/catalog/dansk
	${FLXCAT} text/help.cd catalog/dansk/amath-help.ct CATALOG dist/catalog/dansk/amath-help.catalog
	${FLXCAT} text/ident.cd catalog/dansk/amath-ident.ct CATALOG dist/catalog/dansk/amath-ident.catalog
	${FLXCAT} text/text.cd catalog/dansk/amath-text.ct CATALOG dist/catalog/dansk/amath-text.catalog
	${FLXCAT} text/keyword.cd catalog/dansk/amath-keyword.ct CATALOG dist/catalog/dansk/amath-keyword.catalog
	${COPY} amath dist/
	${COPY} LICENSE dist/
	${COPY} COPYRIGHT dist/
	${COPY} catalog/LICENSE dist/catalog/

clean:
	${DEL}  aengine.o charbuf.o cplex.o fgrid.o ntext.o real.o  acos.o acosh.o asin.o asinh.o atan.o atan2.o atanh.o cbrt.o ceil.o copysign.o cos.o cosh.o exp.o expm1.o fabs.o finite.o floor.o fmod.o hypot.o isnan.o kcos.o kremp2.o ksin.o ktan.o log.o log10.o log1p.o pow.o remp2.o round.o scalbn.o sin.o sinh.o sqrt.o tan.o tanh.o trunc.o  cacos.o cacosh.o cacot.o cacoth.o cacsc.o cacsch.o casec.o casech.o casin.o casinh.o catan.o catanh.o ccbrt.o ccos.o ccosh.o ccot.o ccoth.o ccsc.o ccsch.o cexp.o clog.o clog10.o clogb.o cpow.o csec.o csech.o csgn.o csin.o csinh.o csqrt.o ctan.o ctanh.o prim.o  alloccpy.o mem.o memcpy.o memset.o strcmp.o strlen.o untag.o dragon4.o dmath.o dprint.o  evaluator.o functions.o graphlist.o lexer.o nodes.o operators.o optimizer.o parser.o statements.o token.o values.o viewer.o console.o console_amiga.o console_stdc.o filesystem_amiga.o filesystem_stdc.o graph.o graph_amiga.o graph_gtk.o language.o language_amiga.o language_stdc.o preferences.o preferences_amiga.o preferences_stdc.o proc_amiga.o program.o program_amiga.o program_stdc.o program_test.o task_amiga.o task_stdc.o window_amiga.o io.o main.o libamath.a libcamath.a libcomplex.a libamathapp.a amath
	${DELREC} dist

depend:
	@echo Dependencies already done
