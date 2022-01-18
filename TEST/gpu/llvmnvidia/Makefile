SRCS	= ../gputest.cc
TARGET	= llvm.gputest

default all: $(TARGET)

# This version is built with LLVM; ../testnvidia contains the version built with GCC
CXX = clang++
OMPFLAGS = -g -O2 -lm -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda

llvm.gputest: ${SRCS}
	$(CXX) $(OMPFLAGS) -o llvm.gputest ${SRCS}

run: llvm.gputest
	echo "Running llvm.gputest"
	echo ""
	time ./llvm.gputest

hpct: hpct1 hpct2

hpct1: llvm.gputest
	echo "Starting \"hpct.1.c.g.t: -e CPUTIME -e gpu=nvidia -t\""
	echo ""
	export OMP_NUM_THREADS=1; time hpcrun -e CPUTIME -e gpu=nvidia -o meas.1.c.g.t -t ./llvm.gputest
	echo ""
	time hpcstruct meas.1.c.g.t
	echo ""
	time hpcprof -o dbase.1.c.g.t meas.1.c.g.t
	echo ""
	echo "============================================"
	echo ""

hpct2: llvm.gputest
	echo "Starting \"hpct.2.c.g.t: -e CPUTIME -e gpu=nvidia -t\""
	echo ""
	export OMP_NUM_THREADS=2; time hpcrun -e CPUTIME -e gpu=nvidia -o meas.2.c.g.t -t ./llvm.gputest
	echo ""
	time hpcstruct meas.2.c.g.t
	echo ""
	time hpcprof -o dbase.2.c.g.t meas.2.c.g.t
	echo ""
	echo "============================================"
	echo ""

hpctpc: llvm.gputest
	echo "Starting \"hpct.c.gp.t: -e CPUTIME -e gpu=nvidia,pc -t\""
	echo ""
	export OMP_NUM_THREADS=2; time hpcrun -e CPUTIME -e gpu=nvidia,pc -o meas.c.gp.t -t ./llvm.gputest
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
