# This code is used to print arguments and environment, to help debug
# application environment variable invocations

CC =clang

LLDLIBS 	= $(LD_OPTS)
OFLAGS 	= -g -m64

TARGET=testcpu.llvm

SRCS=  \
	../../src/testcpu.c \
	$(NULL)

default all: $(TARGET)

${TARGET}: ${SRCS}
	$(CC) $(OFLAGS) -o ${TARGET} ${SRCS} $(LLDLIBS)

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
