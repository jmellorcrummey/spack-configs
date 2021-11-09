SRCS	= gputest.cc
TARGET	= gputest

default all: $(TARGET)

# ARCHFLAGS := -mcpu=pwr9 -mtune=pwr9

# This version is built with GCC; ../llvm contains the version built with LLVM
CXX = g++
OMPFLAGS = -g -fopenmp -foffload=nvptx-none="-Ofast -lm -misa=sm_35"

export OMP_NUM_THREADS=2

gputest: ${SRCS}
	$(CXX) $(OMPFLAGS) -o gputest gputest.cc

run: gputest
	echo "Running gputest"
	echo ""
	time gputest

hpct: gputest
	echo "Starting \"hpct.c.g.t: -e CPUTIME-e gpu=nvidia -t\""
	echo ""
	time hpcrun -e CPUTIME -e gpu=nvidia -o meas.c.g.t -t gputest
	echo ""
	time hpcstruct meas.c.g.t
	echo ""
	time hpcprof -o dbase.c.g.t meas.c.g.t
	echo ""
	echo "============================================"
	echo ""

hpctpc: gputest
	echo "Starting \"hpct.c.gp.t: -e CPUTIME-e gpu=nvidia,pc -t\""
	echo ""
	time hpcrun -e CPUTIME -e gpu=nvidia,pc -o meas.c.gp.t -t gputest
	echo ""
	time hpcstruct meas.c.gp.t
	echo ""
	time hpcprof -o dbase.c.gp.t meas.c.gp.t
	echo ""
	echo "============================================"
	echo ""

clean:
	-/bin/rm -rf meas.*
	-/bin/rm -rf dbase.*
	-/bin/rm -f TESTS.log
	-/bin/rm -f *core*

clobber: clean
	-/bin/rm -rf *.o gputest
