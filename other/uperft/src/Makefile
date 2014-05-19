CC=`cat ../.compiler`
CCFLAGS=-Wall -O2 -I../include
LDFLAGS=-ldl -lpall -lfsop -lfsma
TARGET=uperft

all:
	${CC} ${CCFLAGS} -c cexit.c export.c main.c module.c result.c stack.c unit.c
	${CC} -o ${TARGET} cexit.o export.o main.o module.o result.o stack.o unit.o ${LDFLAGS}

install:
	cp perft /usr/local/bin/

clean:
	rm -f *.o
	rm -f ${TARGET}

