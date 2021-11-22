SRCS	= ../gputest.cc
TARGET	= amd.gputest

default all: $(TARGET)

CXX = clang++
OMPFLAGS = -g -lm -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa -march=gfx906

amd.gputest: ${SRCS}
	$(CXX) -DIGNORE_BAD_INITIAL_DEVICE $(OMPFLAGS) -o amd.gputest ${SRCS}

run: amd.gputest
	echo "Running amd.gputest"
	echo ""
	time ./amd.gputest

hpct: hpct1 hpct2

hpct1: amd.gputest
	echo "Starting \"hpct1.c.g.t: -e CPUTIME-e gpu=amd -t\""
	echo ""
	time export OMP_NUM_THREADS=1; hpcrun -e CPUTIME -e gpu=amd -o meas.1.c.g.t -t ./amd.gputest
	echo ""
	time hpcstruct meas.1.c.g.t
	echo ""
	time hpcprof -o dbase.1.c.g.t meas.1.c.g.t
	echo ""
	echo "============================================"
	echo ""

hpct2: amd.gputest
	echo "Starting \"hpct2.c.g.t: -e CPUTIME-e gpu=amd -t\""
	echo ""
	time export OMP_NUM_THREADS=2; hpcrun -e CPUTIME -e gpu=amd -o meas.2.c.g.t -t ./amd.gputest
	echo ""
	time hpcstruct meas.2.c.g.t
	echo ""
	time hpcprof -o dbase.2.c.g.t meas.2.c.g.t
	echo ""
	echo "============================================"
	echo ""

hpctpc: amd.gputest
	echo "Starting \"hpct.c.gp.t: -e CPUTIME-e gpu=amd,pc -t\""
	echo ""
	time hpcrun -e CPUTIME -e gpu=amd,pc -o meas.c.gp.t -t ./amd.gputest
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
	-/bin/rm -rf *.o amd.gputest
