#  To get a working aomp compiler:
# module use /home/johnmc/modules
# module load aomp

SRCS	= ../../../src/gputest.cc ../../../src/ompgpu.cc
TARGET	= llvm.gputest

MARCH = -march=gfx90a
# MARCH = -march=gfx906 

default all: $(TARGET)

CXX = amdclang++
OMPFLAGS = -g -lm -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa $(MARCH)

llvm.gputest: ${SRCS}
	$(CXX) -DIGNORE_BAD_INITIAL_DEVICE $(OMPFLAGS) -o llvm.gputest ${SRCS}

run: llvm.gputest
	@@echo "Running llvm.gputest"
	@echo ""
	time ./llvm.gputest

hpct: hpct1 hpct2
# no hpctpc on rocm

hpct1: llvm.gputest
	@echo "Starting \"hpct.1.c.g.t: -e CPUTIME-e gpu=amd -t\""
	@echo ""
	export OMP_NUM_THREADS=1; time hpcrun -e CPUTIME -e gpu=amd -o meas.1.c.g.t -t ./llvm.gputest  > log.1.c.g.t 2>&1
	@echo ""
	time hpcstruct meas.1.c.g.t
	@echo ""
	time hpcprof -o dbase.1.c.g.t meas.1.c.g.t
	@echo ""
	@echo "============================================"
	@echo ""

hpct2: llvm.gputest
	@echo "Starting \"hpct.2.c.g.t: -e CPUTIME-e gpu=amd -t\""
	@echo ""
	export OMP_NUM_THREADS=2; time hpcrun -e CPUTIME -e gpu=amd -o meas.2.c.g.t -t ./llvm.gputest  > log.2.c.g.t 2>&1
	@echo ""
	time hpcstruct meas.2.c.g.t
	@echo ""
	time hpcprof -o dbase.2.c.g.t meas.2.c.g.t
	@echo ""
	@echo "============================================"
	@echo ""

hpctpc: llvm.gputest
	@echo "Starting \"hpct.c.gp.t: -e CPUTIME-e gpu=amd,pc -t\""
	@echo ""
	export OMP_NUM_THREADS=2; time hpcrun -e CPUTIME -e gpu=amd,pc -o meas.c.gp.t -t ./llvm.gputest  > log.2.c.gp.t 2>&1
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
	-/bin/rm -f log.*

clobber: clean
	-/bin/rm -rf *.o llvm.gputest
