# This code is used to print arguments and environment, to help debug
# application environment variable invocations

CCTYPE = GNU

CC-GNU          = gcc
CC              = ${CC-${CCTYPE}}

ARCH-GNU        = -m64
ARCH            = ${ARCH-${CCTYPE}}

LLDLIBS 	= $(LD_OPTS)

OFLAGS-GNU 	= -g -v
OFLAGS          = ${OFLAGS-${CCTYPE}}

OPTS		= $(OFLAGS) $(ARCH)

TARGETS= testcpu

SRCS=  \
	../testcpu.c \
	$(NULL)

default all: $(TARGETS)

testcpu: ${SRCS}
	$(CC) $(OPTS) -o testcpu ${SRCS} $(LLDLIBS)

run: testcpu
	time ./testcpu

hpct: testcpu
	time hpcrun -o meas.testcpu -t ./testcpu
	echo ""
	time hpcstruct meas.testcpu
	echo ""
	time hpcprof -o dbase.testcpu meas.testcpu
	echo ""

clobber: clean
	-rm -f $(TARGETS)

clean:
	-rm -rf meas.*
	-rm -rf dbase.*
	-rm -f *core*
