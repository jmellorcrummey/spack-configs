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
	testcpu.c \
	$(NULL)

default all: $(TARGETS)

testcpu: testcpu.c
	$(CC) $(OPTS) -o testcpu testcpu.c $(LLDLIBS)

hpct: testcpu
	time hpcrun -t ./testcpu
	echo ""
	time hpcstruct ./hpctoolkit-testcpu-measurements
	echo ""
	time hpcprof ./hpctoolkit-testcpu-measurements
	echo ""

clobber: clean
	-rm -f $(TARGETS)

clean:
	-rm -rf hpctoolkit*
	-rm -f core* ipc_log
	-rm -f hs_err*.log
	-rm -f *binstrdata*
	-rm -f *.binstr
	-rm -f out
	-rm -f core.* javacore.* jitdump.* Snap.*
