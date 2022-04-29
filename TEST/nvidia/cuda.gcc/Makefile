SRCS	= ../../src/gputest.cc ../../src/cudagpu.cc
TARGET	= cuda.gputest

default all: $(TARGET)

CUDA = /usr/local/cuda-11.6
CXX = g++
CUDACXX = `which nvcc`
CUDACXXFLAGS = -g -O2 -DHAVE_CUDA -std=c++11 -I${CUDA}/include/ $(OPTFLAGS) -Xptxas -v -gencode=arch=compute_60,code=\"sm_60,compute_60\"
CUDACXXFLAGS = -g -lineinfo -opt-info inline -O2 -std=c++11 -I${CUDA}/include/ -Xptxas -v -gencode=arch=compute_60,code=\"sm_60,compute_60\"
CUDACXXFLAGS = -g -lineinfo -opt-info inline -O2 -std=c++11 -I${CUDA}/include/
LDFLAGS = -lm -L${CUDA}/lib64/ -lcuda -lcudart
OMPFLAGS = -g -O2 -fopenmp -lm

gputest.o: ../../src/gputest.cc
	$(CXX) $(OMPFLAGS) -c -o gputest.o  ../../src/gputest.cc

cudagpu.o: ../../src/cudagpu.cc
	$(CUDACXX) $(CUDACXXFLAGS) -c -x cu -o cudagpu.o ../../src/cudagpu.cc

$(TARGET): gputest.o cudagpu.o
	$(CXX) -fopenmp gputest.o cudagpu.o -o $(TARGET) ${LDFLAGS}

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

