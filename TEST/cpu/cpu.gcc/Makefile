# This code is used to print arguments and environment, to help debug
# application environment variable invocations

CC = gcc

ARCH-GNU        = -m64
ARCH            = ${ARCH-${CCTYPE}}

LLDLIBS 	= $(LD_OPTS)

OFLAGS 	= -g -m64

TARGET=testcpu.gcc

SRCS=  \
	../../src/testcpu.c \
	$(NULL)

default all: $(TARGET)

${TARGET}:: ${SRCS}
	$(CC) $(OFLAGS) -o ${TARGET} ${SRCS} $(LLDLIBS)

run: testcpu
	time ./${TARGET}

hpct: hpctclk hpctcyc

hpctclk: ${TARGET}
	runhpct $(TARGET) "-e CPUTIME -t" hpct.clk

hpctcyc: ${TARGET}
	runhpct $(TARGET) "-e cycles -t" hpct.cyc

clean:
	-rm -rf meas.*
	-rm -rf dbase.*
	-rm -f *core*
	-rm -f log*

clobber: clean
	-rm -f $(TARGET)

