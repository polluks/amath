all:	flexcat

CFLAGS += -I. -Wall

asprintf.o:	asprintf.c
	${CC} ${CFLAGS} -c asprintf.c

createcat.o:	createcat.c
	${CC} ${CFLAGS} -c createcat.c

createcatsrc.o:	createcatsrc.c
	${CC} ${CFLAGS} -c createcatsrc.c

createct.o:	createct.c
	${CC} ${CFLAGS} -c createct.c

globals.o:	globals.c
	${CC} ${CFLAGS} -c globals.c

locale_other.o:	locale_other.c
	${CC} ${CFLAGS} -c locale_other.c

main.o:	main.c
	${CC} ${CFLAGS} -c main.c

openlibs.o:	openlibs.c
	${CC} ${CFLAGS} -c openlibs.c

readprefs.o:	readprefs.c
	${CC} ${CFLAGS} -c readprefs.c

scancd.o:	scancd.c
	${CC} ${CFLAGS} -c scancd.c

scanct.o:	scanct.c
	${CC} ${CFLAGS} -c scanct.c

scanpo.o:	scanpo.c
	${CC} ${CFLAGS} -c scanpo.c

showfuncs.o:	showfuncs.c
	${CC} ${CFLAGS} -c showfuncs.c

strptime.o:	strptime.c
	${CC} ${CFLAGS} -c strptime.c

swapfuncs.o:	swapfuncs.c
	${CC} ${CFLAGS} -c swapfuncs.c

utils.o:	utils.c
	${CC} ${CFLAGS} -c utils.c

vastubs.o:	vastubs.c
	${CC} ${CFLAGS} -c vastubs.c


flexcat:	 asprintf.o createcat.o createcatsrc.o createct.o globals.o locale_other.o main.o openlibs.o readprefs.o scancd.o scanct.o scanpo.o showfuncs.o strptime.o swapfuncs.o utils.o vastubs.o
	${CC} ${CFLAGS} -o flexcat  asprintf.o createcat.o createcatsrc.o createct.o globals.o locale_other.o main.o openlibs.o readprefs.o scancd.o scanct.o scanpo.o showfuncs.o strptime.o swapfuncs.o utils.o vastubs.o -lm

clean:
	rm -f  asprintf.o createcat.o createcatsrc.o createct.o globals.o locale_other.o main.o openlibs.o readprefs.o scancd.o scanct.o scanpo.o showfuncs.o strptime.o swapfuncs.o utils.o vastubs.o flexcat

