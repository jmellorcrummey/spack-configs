#  A working aomp compiler is in the rocm module

SRCS	= ../../../src/gputest.cc ../../../src/ompgpu.cc
TARGET	= llvm.gputest

MARCH = -march=gfx90a
MARCH = -march=gfx906 

default all: $(TARGET)

CXX = amdclang++
OMPFLAGS = -g -lm -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa $(MARCH)

llvm.gputest: ${SRCS}
	$(CXX) -DGPU_SMALL -DIGNORE_BAD_INITIAL_DEVICE $(OMPFLAGS) -o llvm.gputest ${SRCS}

run: llvm.gputest
	@@echo "Running llvm.gputest"
	@echo ""
	export OMP_NUM_THREADS=1; /bin/time -p ./llvm.gputest

hpct: hpct1 hpct2 hpct3
# no hpctpc on rocm

hpct1: llvm.gputest
	@echo "Starting \"hpct.1.c.g.t: -e CPUTIME-e gpu=openmp -t\"" > log.1.c.g.t
	pwd >> log.1.c.g.t
	@echo "" >> log.1.c.g.t
	@echo ""
	export OMP_NUM_THREADS=1; /bin/time -p hpcrun -e CPUTIME -e gpu=openmp -o meas.1.c.g.t -t ./llvm.gputest  >> log.1.c.g.t 2>&1
	@echo ""
	/bin/time -p hpcstruct meas.1.c.g.t
	@echo ""
	/bin/time -p hpcprof -o dbase.1.c.g.t meas.1.c.g.t
	@echo ""
	@echo "============================================"
	@echo ""

hpct2: llvm.gputest
	@echo "Starting \"hpct.2.c.g.t: -e CPUTIME-e gpu=openmp -t\"" > log.2.c.g.t
	pwd >> log.2.c.g.t
	@echo "" >> log.2.c.g.t
	@echo ""
	export OMP_NUM_THREADS=2; /bin/time -p hpcrun -e CPUTIME -e gpu=openmp -o meas.2.c.g.t -t ./llvm.gputest  >> log.2.c.g.t 2>&1
	@echo ""
	/bin/time -p hpcstruct meas.2.c.g.t
	@echo ""
	/bin/time -p hpcprof -o dbase.2.c.g.t meas.2.c.g.t
	@echo ""
	@echo "============================================"
	@echo ""

hpct3: llvm.gputest
	@echo "Starting \"hpct.3.c.g.t: -e CPUTIME-e gpu=openmp -t\"" > log.3.c.g.t
	pwd >> log.3.c.g.t
	@echo "" >> log.3.c.g.t
	@echo ""
	export OMP_NUM_THREADS=3; /bin/time -p hpcrun -e CPUTIME -e gpu=openmp -o meas.3.c.g.t -t ./llvm.gputest  >> log.3.c.g.t 2>&1
	@echo ""
	/bin/time -p hpcstruct meas.3.c.g.t
	@echo ""
	/bin/time -p hpcprof -o dbase.3.c.g.t meas.3.c.g.t
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
