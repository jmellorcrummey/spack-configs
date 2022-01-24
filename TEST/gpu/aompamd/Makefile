SRCS	= ../gputest.cc
TARGET	= amd.gputest

default all: $(TARGET)

CXX = $(AOMP_HOME)/bin/clang++
OMPFLAGS = -g -lm -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa -march=gfx906

export OMP_NUM_THREADS=1
export OMP_NUM_THREADS=2

amd.gputest: ${SRCS}
	$(CXX) -DIGNORE_BAD_INITIAL_DEVICE $(OMPFLAGS) -o amd.gputest ${SRCS}

smoke: smoke.cc
	$(CXX) $(OMPFLAGS) -o $@ smoke.cc

run: amd.gputest
	@echo "Running amd.gputest"
	@echo ""
	time ./amd.gputest

hpct: amd.gputest
	@echo "Starting \"hpct.c.g.t: -e CPUTIME-e gpu=amd -t\""
	@echo ""
	time hpcrun -e CPUTIME -e gpu=amd -o meas.c.g.t -t ./amd.gputest
	@echo ""
	time hpcstruct meas.c.g.t
	@echo ""
	time hpcprof -o dbase.c.g.t meas.c.g.t
	@echo ""
	@echo "============================================"
	@echo ""

hpctpc: amd.gputest
	@echo "Starting \"hpct.c.gp.t: -e CPUTIME-e gpu=amd,pc -t\""
	@echo ""
	time hpcrun -e CPUTIME -e gpu=amd,pc -o meas.c.gp.t -t ./amd.gputest
	@echo ""
	time hpcstruct meas.c.gp.t
	@echo ""
	time hpcprof -o dbase.c.gp.t meas.c.gp.t
	@echo ""
	@echo "============================================"
	@echo ""

clean:
	-/bin/rm -rf meas.*
	-/bin/rm -rf dbase.*
	-/bin/rm -f TESTS.log
	-/bin/rm -f *core*

clobber: clean
	-/bin/rm -rf *.o amd.gputest
