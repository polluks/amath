CC       = gcc
CFLAGS   = -std=c9x -O3 -DWITHTEST -I. -I.. -Wall
AR       = ar
RANLIB   = ranlib
MKDIR    = mkdir -p
DEL      = rm -f
INSTALL  = install -m 0644
PREFIX   = /usr

alib     = libamath.a
solib    = libamath.so

all: static shared

static: ${alib}

shared: ${solib}

static/acos.o:	acos.c
	${CC} ${CFLAGS} -fno-builtin -c acos.c -o static/acos.o

shared/acos.o:	acos.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c acos.c -o shared/acos.o

static/acosh.o:	acosh.c
	${CC} ${CFLAGS} -fno-builtin -c acosh.c -o static/acosh.o

shared/acosh.o:	acosh.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c acosh.c -o shared/acosh.o

static/acvs.o:	acvs.c
	${CC} ${CFLAGS} -fno-builtin -c acvs.c -o static/acvs.o

shared/acvs.o:	acvs.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c acvs.c -o shared/acvs.o

static/ahv.o:	ahv.c
	${CC} ${CFLAGS} -fno-builtin -c ahv.c -o static/ahv.o

shared/ahv.o:	ahv.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c ahv.c -o shared/ahv.o

static/ahvc.o:	ahvc.c
	${CC} ${CFLAGS} -fno-builtin -c ahvc.c -o static/ahvc.o

shared/ahvc.o:	ahvc.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c ahvc.c -o shared/ahvc.o

static/asin.o:	asin.c
	${CC} ${CFLAGS} -fno-builtin -c asin.c -o static/asin.o

shared/asin.o:	asin.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c asin.c -o shared/asin.o

static/asinh.o:	asinh.c
	${CC} ${CFLAGS} -fno-builtin -c asinh.c -o static/asinh.o

shared/asinh.o:	asinh.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c asinh.c -o shared/asinh.o

static/atan.o:	atan.c
	${CC} ${CFLAGS} -fno-builtin -c atan.c -o static/atan.o

shared/atan.o:	atan.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c atan.c -o shared/atan.o

static/atan2.o:	atan2.c
	${CC} ${CFLAGS} -fno-builtin -c atan2.c -o static/atan2.o

shared/atan2.o:	atan2.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c atan2.c -o shared/atan2.o

static/atanh.o:	atanh.c
	${CC} ${CFLAGS} -fno-builtin -c atanh.c -o static/atanh.o

shared/atanh.o:	atanh.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c atanh.c -o shared/atanh.o

static/aver.o:	aver.c
	${CC} ${CFLAGS} -fno-builtin -c aver.c -o static/aver.o

shared/aver.o:	aver.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c aver.c -o shared/aver.o

static/cbrt.o:	cbrt.c
	${CC} ${CFLAGS} -fno-builtin -c cbrt.c -o static/cbrt.o

shared/cbrt.o:	cbrt.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c cbrt.c -o shared/cbrt.o

static/ceil.o:	ceil.c
	${CC} ${CFLAGS} -fno-builtin -c ceil.c -o static/ceil.o

shared/ceil.o:	ceil.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c ceil.c -o shared/ceil.o

static/copysign.o:	copysign.c
	${CC} ${CFLAGS} -fno-builtin -c copysign.c -o static/copysign.o

shared/copysign.o:	copysign.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c copysign.c -o shared/copysign.o

static/cos.o:	cos.c
	${CC} ${CFLAGS} -fno-builtin -c cos.c -o static/cos.o

shared/cos.o:	cos.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c cos.c -o shared/cos.o

static/cosh.o:	cosh.c
	${CC} ${CFLAGS} -fno-builtin -c cosh.c -o static/cosh.o

shared/cosh.o:	cosh.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c cosh.c -o shared/cosh.o

static/exp.o:	exp.c
	${CC} ${CFLAGS} -fno-builtin -c exp.c -o static/exp.o

shared/exp.o:	exp.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c exp.c -o shared/exp.o

static/expm1.o:	expm1.c
	${CC} ${CFLAGS} -fno-builtin -c expm1.c -o static/expm1.o

shared/expm1.o:	expm1.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c expm1.c -o shared/expm1.o

static/fabs.o:	fabs.c
	${CC} ${CFLAGS} -fno-builtin -c fabs.c -o static/fabs.o

shared/fabs.o:	fabs.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c fabs.c -o shared/fabs.o

static/finite.o:	finite.c
	${CC} ${CFLAGS} -fno-builtin -c finite.c -o static/finite.o

shared/finite.o:	finite.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c finite.c -o shared/finite.o

static/floor.o:	floor.c
	${CC} ${CFLAGS} -fno-builtin -c floor.c -o static/floor.o

shared/floor.o:	floor.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c floor.c -o shared/floor.o

static/fmod.o:	fmod.c
	${CC} ${CFLAGS} -fno-builtin -c fmod.c -o static/fmod.o

shared/fmod.o:	fmod.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c fmod.c -o shared/fmod.o

static/hypot.o:	hypot.c
	${CC} ${CFLAGS} -fno-builtin -c hypot.c -o static/hypot.o

shared/hypot.o:	hypot.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c hypot.c -o shared/hypot.o

static/isnan.o:	isnan.c
	${CC} ${CFLAGS} -fno-builtin -c isnan.c -o static/isnan.o

shared/isnan.o:	isnan.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c isnan.c -o shared/isnan.o

static/kcos.o:	kcos.c
	${CC} ${CFLAGS} -fno-builtin -c kcos.c -o static/kcos.o

shared/kcos.o:	kcos.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c kcos.c -o shared/kcos.o

static/kremp2.o:	kremp2.c
	${CC} ${CFLAGS} -fno-builtin -c kremp2.c -o static/kremp2.o

shared/kremp2.o:	kremp2.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c kremp2.c -o shared/kremp2.o

static/ksin.o:	ksin.c
	${CC} ${CFLAGS} -fno-builtin -c ksin.c -o static/ksin.o

shared/ksin.o:	ksin.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c ksin.c -o shared/ksin.o

static/ktan.o:	ktan.c
	${CC} ${CFLAGS} -fno-builtin -c ktan.c -o static/ktan.o

shared/ktan.o:	ktan.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c ktan.c -o shared/ktan.o

static/log.o:	log.c
	${CC} ${CFLAGS} -fno-builtin -c log.c -o static/log.o

shared/log.o:	log.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c log.c -o shared/log.o

static/log10.o:	log10.c
	${CC} ${CFLAGS} -fno-builtin -c log10.c -o static/log10.o

shared/log10.o:	log10.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c log10.c -o shared/log10.o

static/log1p.o:	log1p.c
	${CC} ${CFLAGS} -fno-builtin -c log1p.c -o static/log1p.o

shared/log1p.o:	log1p.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c log1p.c -o shared/log1p.o

static/pow.o:	pow.c
	${CC} ${CFLAGS} -fno-builtin -c pow.c -o static/pow.o

shared/pow.o:	pow.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c pow.c -o shared/pow.o

static/remp2.o:	remp2.c
	${CC} ${CFLAGS} -fno-builtin -c remp2.c -o static/remp2.o

shared/remp2.o:	remp2.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c remp2.c -o shared/remp2.o

static/round.o:	round.c
	${CC} ${CFLAGS} -fno-builtin -c round.c -o static/round.o

shared/round.o:	round.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c round.c -o shared/round.o

static/scalbn.o:	scalbn.c
	${CC} ${CFLAGS} -fno-builtin -c scalbn.c -o static/scalbn.o

shared/scalbn.o:	scalbn.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c scalbn.c -o shared/scalbn.o

static/sin.o:	sin.c
	${CC} ${CFLAGS} -fno-builtin -c sin.c -o static/sin.o

shared/sin.o:	sin.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c sin.c -o shared/sin.o

static/sinh.o:	sinh.c
	${CC} ${CFLAGS} -fno-builtin -c sinh.c -o static/sinh.o

shared/sinh.o:	sinh.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c sinh.c -o shared/sinh.o

static/sqrt.o:	sqrt.c
	${CC} ${CFLAGS} -fno-builtin -c sqrt.c -o static/sqrt.o

shared/sqrt.o:	sqrt.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c sqrt.c -o shared/sqrt.o

static/tan.o:	tan.c
	${CC} ${CFLAGS} -fno-builtin -c tan.c -o static/tan.o

shared/tan.o:	tan.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c tan.c -o shared/tan.o

static/tanh.o:	tanh.c
	${CC} ${CFLAGS} -fno-builtin -c tanh.c -o static/tanh.o

shared/tanh.o:	tanh.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c tanh.c -o shared/tanh.o

static/trunc.o:	trunc.c
	${CC} ${CFLAGS} -fno-builtin -c trunc.c -o static/trunc.o

shared/trunc.o:	trunc.c
	${CC} ${CFLAGS} -fPIC -fno-builtin -c trunc.c -o shared/trunc.o

.PHONY: build
build:
	${MKDIR} static
	${MKDIR} shared

${solib}:	build  shared/acos.o shared/acosh.o shared/acvs.o shared/ahv.o shared/ahvc.o shared/asin.o shared/asinh.o shared/atan.o shared/atan2.o shared/atanh.o shared/aver.o shared/cbrt.o shared/ceil.o shared/copysign.o shared/cos.o shared/cosh.o shared/exp.o shared/expm1.o shared/fabs.o shared/finite.o shared/floor.o shared/fmod.o shared/hypot.o shared/isnan.o shared/kcos.o shared/kremp2.o shared/ksin.o shared/ktan.o shared/log.o shared/log10.o shared/log1p.o shared/pow.o shared/remp2.o shared/round.o shared/scalbn.o shared/sin.o shared/sinh.o shared/sqrt.o shared/tan.o shared/tanh.o shared/trunc.o
	${CC} -shared -fPIC -Wl,-soname,${solib} -o ${solib}  shared/acos.o shared/acosh.o shared/acvs.o shared/ahv.o shared/ahvc.o shared/asin.o shared/asinh.o shared/atan.o shared/atan2.o shared/atanh.o shared/aver.o shared/cbrt.o shared/ceil.o shared/copysign.o shared/cos.o shared/cosh.o shared/exp.o shared/expm1.o shared/fabs.o shared/finite.o shared/floor.o shared/fmod.o shared/hypot.o shared/isnan.o shared/kcos.o shared/kremp2.o shared/ksin.o shared/ktan.o shared/log.o shared/log10.o shared/log1p.o shared/pow.o shared/remp2.o shared/round.o shared/scalbn.o shared/sin.o shared/sinh.o shared/sqrt.o shared/tan.o shared/tanh.o shared/trunc.o

${alib}:	build  static/acos.o static/acosh.o static/acvs.o static/ahv.o static/ahvc.o static/asin.o static/asinh.o static/atan.o static/atan2.o static/atanh.o static/aver.o static/cbrt.o static/ceil.o static/copysign.o static/cos.o static/cosh.o static/exp.o static/expm1.o static/fabs.o static/finite.o static/floor.o static/fmod.o static/hypot.o static/isnan.o static/kcos.o static/kremp2.o static/ksin.o static/ktan.o static/log.o static/log10.o static/log1p.o static/pow.o static/remp2.o static/round.o static/scalbn.o static/sin.o static/sinh.o static/sqrt.o static/tan.o static/tanh.o static/trunc.o
	${AR} rcs static/${alib}  static/acos.o static/acosh.o static/acvs.o static/ahv.o static/ahvc.o static/asin.o static/asinh.o static/atan.o static/atan2.o static/atanh.o static/aver.o static/cbrt.o static/ceil.o static/copysign.o static/cos.o static/cosh.o static/exp.o static/expm1.o static/fabs.o static/finite.o static/floor.o static/fmod.o static/hypot.o static/isnan.o static/kcos.o static/kremp2.o static/ksin.o static/ktan.o static/log.o static/log10.o static/log1p.o static/pow.o static/remp2.o static/round.o static/scalbn.o static/sin.o static/sinh.o static/sqrt.o static/tan.o static/tanh.o static/trunc.o
	${RANLIB} static/${alib}

.PHONY: install
install:	${alib} ${solib}
	${MKDIR} ${DESTDIR}${PREFIX}/lib
	${INSTALL} static/${alib} ${DESTDIR}${PREFIX}/lib/${alib}
	${INSTALL} ${solib} ${DESTDIR}${PREFIX}/lib/${solib}

.PHONY:	uninstall
uninstall:
	${DEL} ${DESTDIR}${PREFIX}/lib/${alib}
	${DEL} ${DESTDIR}${PREFIX}/lib/${solib}

clean:
	${DEL} static/${alib} ${solib}  static/acos.o static/acosh.o static/acvs.o static/ahv.o static/ahvc.o static/asin.o static/asinh.o static/atan.o static/atan2.o static/atanh.o static/aver.o static/cbrt.o static/ceil.o static/copysign.o static/cos.o static/cosh.o static/exp.o static/expm1.o static/fabs.o static/finite.o static/floor.o static/fmod.o static/hypot.o static/isnan.o static/kcos.o static/kremp2.o static/ksin.o static/ktan.o static/log.o static/log10.o static/log1p.o static/pow.o static/remp2.o static/round.o static/scalbn.o static/sin.o static/sinh.o static/sqrt.o static/tan.o static/tanh.o static/trunc.o  shared/acos.o shared/acosh.o shared/acvs.o shared/ahv.o shared/ahvc.o shared/asin.o shared/asinh.o shared/atan.o shared/atan2.o shared/atanh.o shared/aver.o shared/cbrt.o shared/ceil.o shared/copysign.o shared/cos.o shared/cosh.o shared/exp.o shared/expm1.o shared/fabs.o shared/finite.o shared/floor.o shared/fmod.o shared/hypot.o shared/isnan.o shared/kcos.o shared/kremp2.o shared/ksin.o shared/ktan.o shared/log.o shared/log10.o shared/log1p.o shared/pow.o shared/remp2.o shared/round.o shared/scalbn.o shared/sin.o shared/sinh.o shared/sqrt.o shared/tan.o shared/tanh.o shared/trunc.o

