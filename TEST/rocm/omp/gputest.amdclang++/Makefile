#  A working aomp compiler is in the rocm module

SRCS	= ../../../src/gputest.cc ../../../src/ompgpu.cc
TARGET	= llvm.gputest

MARCH = -march=gfx90a
MARCH = -march=gfx906 

default all: $(TARGET)

CXX = amdclang++
OMPFLAGS = -g -lm -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa $(MARCH)

${TARGET}: ${SRCS}
	$(CXX) -DGPU_SMALL -DIGNORE_BAD_INITIAL_DEVICE $(OMPFLAGS) -o ${TARGET} ${SRCS}

run: ${TARGET}
	@@echo "Running ${TARGET}"
	@echo ""
	export OMP_NUM_THREADS=1; /bin/time -p ./${TARGET}

hpct: hpct1 hpct2 hpct3
# no hpctpc on rocm

hpct1: ${TARGET}
	export OMP_NUM_THREADS=1; runhpct $(TARGET) "-e CPUTIME -e gpu=openmp -t" hpct1.cg

hpct2: ${TARGET}
	export OMP_NUM_THREADS=2; runhpct $(TARGET) "-e CPUTIME -e gpu=openmp -t" hpct2.cg

hpct3: ${TARGET}
	export OMP_NUM_THREADS=3; runhpct $(TARGET) "-e CPUTIME -e gpu=openmp -t" hpct3.cg

clean:
	-/bin/rm -rf meas.*
	-/bin/rm -rf dbase.*
	-/bin/rm -f *core*
	-/bin/rm -f log.*

clobber: clean
	-/bin/rm -rf *.o ${TARGET}
