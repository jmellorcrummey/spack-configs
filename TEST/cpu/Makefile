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
	../src/testcpu.c \
	$(NULL)

default all: $(TARGETS)

testcpu: ${SRCS}
	$(CC) $(OPTS) -o testcpu ${SRCS} $(LLDLIBS)

run: testcpu
	time ./testcpu

hpct: hpctclk hpctcyc

hpctclk: testcpu
	time hpcrun -o meas.clk -t ./testcpu
	echo ""
	time hpcstruct meas.clk
	echo ""
	time hpcprof -o dbase.clk meas.clk
	echo ""

hpctcyc: testcpu
	time hpcrun -o meas.cyc -e cycles -t ./testcpu
	echo ""
	time hpcstruct meas.cyc
	echo ""
	time hpcprof -o dbase.cyc meas.cyc
	echo ""

clobber: clean
	-rm -f $(TARGETS)

clean:
	-rm -rf meas.*
	-rm -rf dbase.*
	-rm -f *core*
