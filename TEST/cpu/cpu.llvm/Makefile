# This code is used to print arguments and environment, to help debug
# application environment variable invocations

CCTYPE = LLVM

CC-GNU          = gcc
CC-LLVM         = clang
CC              = ${CC-${CCTYPE}}

ARCH-GNU        = -m64
ARCH-LLVM       = -m64
ARCH            = ${ARCH-${CCTYPE}}

LLDLIBS 	= $(LD_OPTS)

OFLAGS-GNU 	= -g
OFLAGS-LLVM 	= -g
OFLAGS          = ${OFLAGS-${CCTYPE}}

OPTS		= $(OFLAGS) $(ARCH)

TARGET=testcpu

SRCS=  \
	../../src/testcpu.c \
	$(NULL)

default all: $(TARGET)

${TARGET}: ${SRCS}
	$(CC) $(OPTS) -o ${TARGET} ${SRCS} $(LLDLIBS)

run: ${TARGET}
	time ./$(TARGET)

hpct: hpctclk hpctcyc

hpctclk: ${TARGET}
	runhpct $(TARGET) "-e CPUTIME -t" hpct.clk

hpctcyc: ${TARGET}
	runhpct $(TARGET) "-e cycles -t" hpct.cyc

clobber: clean
	-rm -f $(TARGET)

clean:
	-rm -rf meas.*
	-rm -rf dbase.*
	-rm -f *core*
	-rm -f log*
