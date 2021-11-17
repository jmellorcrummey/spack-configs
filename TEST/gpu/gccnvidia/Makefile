SRCS	= ../gputest.cc
TARGET	= gcc.gputest

default all: $(TARGET)

# This version is built with GCC; ../llvmnvidia contains the version built with LLVM
CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm
OMPFLAGS = -g -O2 -fopenmp -foffload=nvptx-none="-O2 -lm -misa=sm_35"

export OMP_NUM_THREADS=1
export OMP_NUM_THREADS=2

gcc.gputest: ${SRCS}
	$(CXX) $(OMPFLAGS) -o gcc.gputest ${SRCS}

run: gcc.gputest
	echo "Running gcc.gputest"
	echo ""
	time gcc.gputest

hpct: gcc.gputest
	echo "Starting \"hpct.c.g.t: -e CPUTIME-e gpu=nvidia -t\""
	echo ""
	time hpcrun -e CPUTIME -e gpu=nvidia -o meas.c.g.t -t gcc.gputest
	echo ""
	time hpcstruct meas.c.g.t
	echo ""
	time hpcprof -o dbase.c.g.t meas.c.g.t
	echo ""
	echo "============================================"
	echo ""

hpctpc: gcc.gputest
	echo "Starting \"hpct.c.gp.t: -e CPUTIME-e gpu=nvidia,pc -t\""
	echo ""
	time hpcrun -e CPUTIME -e gpu=nvidia,pc -o meas.c.gp.t -t gcc.gputest
	echo ""
	time hpcstruct --gpucfg "yes" meas.c.gp.t
	echo ""
	time hpcprof -o dbase.c.gp.t meas.c.gp.t
	echo ""
	echo "============================================"
	echo ""

clean:
	-/bin/rm -rf meas.*
	-/bin/rm -rf dbase.*
	-/bin/rm -f *core*

clobber: clean
	-/bin/rm -rf *.o gcc.gputest
