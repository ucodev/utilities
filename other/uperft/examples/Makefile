CC=`cat ../.compiler`
CCFLAGS=-O0 -fPIC -shared
LDFLAGS=

all:
	${CC} ${CCFLAGS} ${LDFLAGS} -o add.so add.c
	${CC} ${CCFLAGS} ${LDFLAGS} -o mul.so mul.c
	${CC} ${CCFLAGS} ${LDFLAGS} -o sal.so sal.c
	cp *.so ../tu/

clean:
	rm -f *.so
	rm -f ../tu/*.so
