SRCS	= ../gputest.cc
TARGET	= llvm.gputest

default all: $(TARGET)

# This version is built with LLVM; ../testnvidia contains the version built with GCC
CXX = clang++
OMPFLAGS = -g -O2 -lm -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda

export OMP_NUM_THREADS=1
export OMP_NUM_THREADS=2

llvm.gputest: ${SRCS}
	$(CXX) $(OMPFLAGS) -o llvm.gputest ${SRCS}

run: llvm.gputest
	echo "Running llvm.gputest"
	echo ""
	time ./llvm.gputest

hpct: llvm.gputest
	echo "Starting \"hpct.c.g.t: -e CPUTIME-e gpu=nvidia -t\""
	echo ""
	time hpcrun -e CPUTIME -e gpu=nvidia -o meas.c.g.t -t ./llvm.gputest
	echo ""
	time hpcstruct meas.c.g.t
	echo ""
	time hpcprof -o dbase.c.g.t meas.c.g.t
	echo ""
	echo "============================================"
	echo ""

hpctpc: llvm.gputest
	echo "Starting \"hpct.c.gp.t: -e CPUTIME-e gpu=nvidia,pc -t\""
	echo ""
	time hpcrun -e CPUTIME -e gpu=nvidia,pc -o meas.c.gp.t -t ./llvm.gputest
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
	-/bin/rm -rf *.o llvm.gputest
