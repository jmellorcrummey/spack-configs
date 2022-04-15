SRCS	= ../../src/gputest.cc ../../src/cudagpu.cc
TARGET	= cuda.gputest

default all: $(TARGET)

# This version is built with GCC; ../omp.llvm contains the version built with LLVM
CUDA = /usr/local/cuda-11.2/
CXX = g++
CUDACXX = $(CUDA)/bin/nvcc
CUDACXXFLAGS = -g -O2 -DHAVE_CUDA -std=c++11 -I${CUDA}/include/ $(OPTFLAGS) -Xptxas -v -gencode=arch=compute_60,code=\"sm_60,compute_60\"
LDFLAGS = -lm -L${CUDA}/lib64/ -lcuda -lcudart
OMPFLAGS = -g -O2 -fopenmp -lm
OMPFLAGS = -g -v -O2 -fopenmp -foffload=nvptx-none="-O2 -lm -misa=sm_35"

gputest.o: ../../src/gputest.cc
	$(CXX) $(OMPFLAGS) -c -o gputest.o  ../../src/gputest.cc

cudagpu.o: ../../src/cudagpu.cc
	$(CUDACXX) $(CUDACXXFLAGS) -c -x cu -o cudagpu.o ../../src/cudagpu.cc

cuda.gputest: gputest.o cudagpu.o
	$(CXX) -fopenmp gputest.o cudagpu.o -o cuda.gputest ${LDFLAGS}

struct: cuda.gputest
	@echo "Starting \"hpcstruct cuda.gputest\""
	/bin/time -p hpcstruct cuda.gputest
	@echo ""
	@echo ""
	@echo "Starting \"hpcstruct 205259747422e8dcb2b6f2b6794e44e3.gpubin\" "
	/bin/time -p hpcstruct --gpucfg no 205259747422e8dcb2b6f2b6794e44e3.gpubin
	@echo ""
	@echo ""

run: cuda.gputest
	@echo "Running \"cuda.gputest\""
	@echo ""
	/bin/time -p ./cuda.gputest
	@echo ""
	@echo ""

hpct: hpct1 hpct2 hpctpc1 hpctpc2

hpct1: cuda.gputest
	@echo "Starting \"hpct.1.c.g.t: -e CPUTIME-e gpu=nvidia -t\""
	@echo ""
	export OMP_NUM_THREADS=1; /bin/time -p hpcrun -e CPUTIME -e gpu=nvidia -o meas.1.c.g.t -t ./cuda.gputest | tee log.1.c.g.t 2>&1
	@echo ""
	/bin/time -p hpcstruct --gpucfg no meas.1.c.g.t
	@echo ""
	/bin/time -p hpcprof -o dbase.1.c.g.t meas.1.c.g.t
	@echo ""
	@echo ""

hpct2: cuda.gputest
	@echo "Starting \"hpct.2.c.g.t: -e CPUTIME-e gpu=nvidia -t\""
	@echo ""
	export OMP_NUM_THREADS=2; /bin/time hpcrun -e CPUTIME -e gpu=nvidia -o meas.2.c.g.t -t ./cuda.gputest | tee  log.2.c.g.t 2>&1
	@echo ""
	/bin/time -p hpcstruct --gpucfg yes meas.2.c.g.t
	@echo ""
	/bin/time -p hpcprof -o dbase.2.c.g.t meas.2.c.g.t
	@echo ""
	@echo ""

hpct3: cuda.gputest
	@echo "Starting \"hpct.3.c.g.t: -e CPUTIME-e gpu=nvidia -t\""
	@echo ""
	export OMP_NUM_THREADS=1; /bin/time -p hpcrun -e CPUTIME -e gpu=nvidia -o meas.3.c.g.t -t ./cuda.gputest | tee log.3.c.g.t 2>&1
	@echo ""
	/bin/time -p hpcstruct --gpucfg no --nocache meas.3.c.g.t
	@echo ""
	/bin/time -p hpcprof -o dbase.3.c.g.t meas.3.c.g.t
	@echo ""
	@echo ""

hpctpc1: cuda.gputest
	@echo "Starting \"hpct.1.c.gp.t: -e CPUTIME-e gpu=nvidia,pc -t\""
	@echo ""
	export OMP_NUM_THREADS=1; /bin/time -p hpcrun -e CPUTIME -e gpu=nvidia,pc -o meas.1.c.gp.t -t ./cuda.gputest | tee  log.1.c.gp.t 2>&1
	@echo ""
	/bin/time -p hpcstruct --gpucfg no meas.1.c.gp.t
	@echo ""
	/bin/time -p hpcprof -o dbase.1.c.gp.t meas.1.c.gp.t
	@echo ""
	@echo ""

hpctpc2: cuda.gputest
	@echo "Starting \"hpct.2.c.gp.t: -e CPUTIME-e gpu=nvidia,pc -t\""
	@echo ""
	export OMP_NUM_THREADS=2; /bin/time -p hpcrun -e CPUTIME -e gpu=nvidia,pc -o meas.2.c.gp.t -t ./cuda.gputest | tee  log.2.c.gp.t 2>&1
	@echo ""
	/bin/time -p hpcstruct --gpucfg yes meas.2.c.gp.t
	@echo ""
	/bin/time -p hpcprof -o dbase.2.c.gp.t meas.2.c.gp.t
	@echo ""
	@echo ""

clean:
	-/bin/rm -rf meas.*
	-/bin/rm -rf dbase.*
	-/bin/rm -f *core*
	-/bin/rm -f *log.*
	-/bin/rm -f TEST.log*
	-/bin/rm -f *.hpcstruct
	@echo ""
	@echo ""

clobber: clean
	-/bin/rm -rf *.o cuda.gputest
	@echo ""
	@echo ""
