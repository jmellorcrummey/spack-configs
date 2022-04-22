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

hip.gputest: gputest.o hipgpu.o
	$(HIPCXX) -fopenmp gputest.o hipgpu.o -o hip.gputest ${LDFLAGS}

struct: hip.gputest
	@echo "Starting \"hpcstruct hip.gputest\""
	/bin/time -p hpcstruct hip.gputest
	@echo ""
	@echo ""

run: hip.gputest
	@echo "Running \"hip.gputest\""
	@echo ""
	/bin/time -p ./hip.gputest
	@echo ""
	@echo ""

hpct: hpct1 hpct2 hpct3

hpct1: hip.gputest
	@echo "Starting \"hpct.1.c.g.t: -e CPUTIME-e gpu=amd -t\"" > log.1.c.g.t
	pwd >> log.1.c.g.t
	@echo "" >> log.1.c.g.t
	@echo ""
	export OMP_NUM_THREADS=1; /bin/time -p hpcrun -e CPUTIME -e gpu=amd -o meas.1.c.g.t -t ./hip.gputest >> log.1.c.g.t 2>&1
	@echo ""
	/bin/time -p hpcstruct --gpucfg no meas.1.c.g.t
	@echo ""
	/bin/time -p hpcprof -o dbase.1.c.g.t meas.1.c.g.t
	@echo ""
	@echo ""

hpct2: hip.gputest
	@echo "Starting \"hpct.2.c.g.t: -e CPUTIME-e gpu=amd -t\"" > log.2.c.g.t
	pwd >> log.2.c.g.t
	@echo "" >> log.2.c.g.t
	@echo ""
	export OMP_NUM_THREADS=2; /bin/time -p hpcrun -e CPUTIME -e gpu=amd -o meas.2.c.g.t -t ./hip.gputest >>  log.2.c.g.t 2>&1
	@echo ""
	/bin/time -p hpcstruct --gpucfg yes meas.2.c.g.t
	@echo ""
	/bin/time -p hpcprof -o dbase.2.c.g.t meas.2.c.g.t
	@echo ""
	@echo ""

hpct3: hip.gputest
	@echo "Starting \"hpct.3.c.g.t: -e CPUTIME-e gpu=amd -t\"" > log.3.c.g.t
	pwd >> log.3.c.g.t
	@echo "" >> log.3.c.g.t
	@echo ""
	export OMP_NUM_THREADS=3; /bin/time -p hpcrun -e CPUTIME -e gpu=amd -o meas.3.c.g.t -t ./hip.gputest >> log.3.c.g.t 2>&1
	@echo ""
	/bin/time -p hpcstruct --gpucfg no --nocache meas.3.c.g.t
	@echo ""
	/bin/time -p hpcprof -o dbase.3.c.g.t meas.3.c.g.t
	@echo ""
	@echo ""

hpctpc1: hip.gputest
	@echo "Starting \"hpct.1.c.gp.t: -e CPUTIME-e gpu=amd,pc -t\"" > log.1.c.gp.t
	pwd >> log.1.c.gp.t
	@echo "" >> log.1.c.gp.t
	@echo ""
	export OMP_NUM_THREADS=1; /bin/time -p hpcrun -e CPUTIME -e gpu=amd,pc -o meas.1.c.gp.t -t ./hip.gputest >>  log.1.c.gp.t 2>&1
	@echo ""
	/bin/time -p hpcstruct --gpucfg no meas.1.c.gp.t
	@echo ""
	/bin/time -p hpcprof -o dbase.1.c.gp.t meas.1.c.gp.t
	@echo ""
	@echo ""

hpctpc2: hip.gputest
	@echo "Starting \"hpct.2.c.gp.t: -e CPUTIME-e gpu=nvidia,pc -t\"" > log.2.c.gp.t
	pwd >> log.2.c.gp.t
	@echo "" >> log.2.c.gp.t
	@echo ""
	export OMP_NUM_THREADS=2; /bin/time -p hpcrun -e CPUTIME -e gpu=amd,pc -o meas.2.c.gp.t -t ./hip.gputest >>  log.2.c.gp.t 2>&1
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
	-/bin/rm -rf *.o hip.gputest
	@echo ""
	@echo ""
