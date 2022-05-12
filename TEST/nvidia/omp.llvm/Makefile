SRCS	= ../../src/gputest.cc ../../src/ompgpu.cc
TARGET	= omp.llvm.gputest

default all: $(TARGET)

CUDA = /usr/local/cuda-11.6/
NVCC = $(CUDA)/bin/nvcc
CXX = clang++
OMPFLAGS =  -DIGNORE_BAD_INITIAL_DEVICE -g -O2 -lm -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda
OMPFLAGS =  -g -O2 -lm -fopenmp -x cuda --cuda-gpu-arch=sm_70 -L$(CUDA)/lib64 -lcudart_static -ldl -lrt -pthread
OMPFLAGS =  -DIGNORE_BAD_INITIAL_DEVICE -g -O2 -lm -fopenmp -x cuda --cuda-gpu-arch=sm_70 -L$(CUDA)/lib64 -lcudart_static -ldl -lrt -pthread

$(TARGET): ${SRCS}
	$(CXX) $(OMPFLAGS) -o $(TARGET) ${SRCS}

run: $(TARGET)
	@echo "Running \"$(TARGET)\""
	@echo ""
	/bin/time -p ./$(TARGET)
	@echo ""
	@echo ""

hpct: hpct1 hpct2 hpct3 hpctpc1 hpctpc2

hpct1: $(TARGET)
	export OMP_NUM_THREADS=1; runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia -t" hpct1.cg

hpct2: $(TARGET)
	export OMP_NUM_THREADS=2; runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia -t" hpct2.cg

hpct3: $(TARGET)
	export OMP_NUM_THREADS=3; runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia -t" hpct3.cg

hpctpc1: $(TARGET)
	export OMP_NUM_THREADS=1; runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia,pc -t" hpct1.cgp "--gpucfg yes"

hpctpc2: $(TARGET)
	export OMP_NUM_THREADS=2; runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia,pc -t" hpct2.cgp "--gpucfg yes"

collect: $(TARGET)
	collect -p hi $(TARGET)
	er_print -func test.1.er

clean:
	-/bin/rm -rf meas.*
	-/bin/rm -rf dbase.*
	-/bin/rm -f *core*
	-/bin/rm -f *log.*
	-/bin/rm -rf test.*.er
	@echo ""
	@echo ""

clobber: clean
	-/bin/rm -rf *.o $(TARGET)
	@echo ""
	@echo ""
