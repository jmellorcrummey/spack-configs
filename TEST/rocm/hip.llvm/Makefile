SRCS	= ../../src/gputest.cc ../../src/hipgpu.cu
TARGET	= hip.gputest

default all: $(TARGET)

# This version is built with GCC; ../omp.llvm contains the version built with LLVM
HIP = /opt/rocm-5.1.0
CXX = g++
HIPCXX = $(HIP)/bin/hipcc
HIPCXXFLAGS = -g -opt-info -O2 -std=c++11 -I${HIP}/hip/include/hip/ -offload-arch=gfx906
LDFLAGS = -lm -L${HIP}/lib64/
OMPFLAGS = -g -O2 -fopenmp -lm

gputest.o: ../../src/gputest.cc
	@echo " HIP = ${HIP} \n"
	$(CXX) $(OMPFLAGS) -c -o gputest.o  ../../src/gputest.cc

hipgpu.o: ../../src/hipgpu.cu
	$(HIPCXX) $(HIPCXXFLAGS) -c -o hipgpu.o ../../src/hipgpu.cu

$(TARGET): gputest.o hipgpu.o
	$(HIPCXX) -fopenmp gputest.o hipgpu.o -o $(TARGET) ${LDFLAGS}

run: $(TARGET)
	@echo "Running \"$(TARGET)\""
	@echo ""
	export OMP_NUM_THREADS=1; /bin/time -p ./$(TARGET)
	@echo ""
	@echo ""

hpct: hpct1 hpct2 hpct3

hpct1: $(TARGET)
	export OMP_NUM_THREADS=1; runhpct $(TARGET) "-e CPUTIME -e gpu=amd -t" hpct1.cg

hpct2: $(TARGET)
	export OMP_NUM_THREADS=2; runhpct $(TARGET) "-e CPUTIME -e gpu=amd -t" hpct2.cg

hpct3: $(TARGET)
	export OMP_NUM_THREADS=3; runhpct $(TARGET) "-e CPUTIME -e gpu=amd -t" hpct3.cg

clean:
	-/bin/rm -rf meas.*
	-/bin/rm -rf dbase.*
	-/bin/rm -f *core*
	-/bin/rm -f *log.*
	-/bin/rm -f TEST.log*
	-/bin/rm -f *.hpcstruct
	-/bin/rm -rf test.*.er
	@echo ""
	@echo ""

clobber: clean
	-/bin/rm -rf *.o $(TARGET)
	@echo ""
	@echo ""
