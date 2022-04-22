SRCS	= ../../src/gputest.cc ../../src/ompgpu.cc
TARGET	= gcc.gputest

default all: $(TARGET)

# This version is built with GCC; ../omp.llvm contains the version built with LLVM
CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm
OMPFLAGS = -g -O2 -fopenmp -foffload=nvptx-none="-O2 -lm -misa=sm_35"

gcc.gputest: ${SRCS}
	$(CXX) $(OMPFLAGS) -o gcc.gputest ${SRCS}

run: gcc.gputest
	@echo "Running \"gcc.gputest\""
	@echo ""
	/bin/time -p ./gcc.gputest
	@echo ""
	@echo ""

hpct: hpct1 hpct2 hpct3 hpctpc1 hpctpc2
	 -grep avg log*

hpct1: gcc.gputest
	@echo "Starting \"hpct.1.c.g.t: -e CPUTIME-e gpu=nvidia -t\"" > log.1.c.g.t
	pwd >> log.1.c.g.t
	@echo "" >> log.1.c.g.t
	@echo ""
	export OMP_NUM_THREADS=1; /bin/time -p hpcrun -e CPUTIME -e gpu=nvidia -o meas.1.c.g.t -t ./gcc.gputest >> log.1.c.g.t 2>&1
	@echo ""
	/bin/time -p hpcstruct --gpucfg no meas.1.c.g.t
	@echo ""
	/bin/time -p hpcprof -o dbase.1.c.g.t meas.1.c.g.t
	@echo ""
	@echo ""

hpct2: gcc.gputest
	@echo "Starting \"hpct.2.c.g.t: -e CPUTIME-e gpu=nvidia -t\"" > log.2.c.g.t
	pwd >> log.1.c.g.t
	@echo "" >> log.1.c.g.t
	@echo ""
	export OMP_NUM_THREADS=2; /bin/time -p hpcrun -e CPUTIME -e gpu=nvidia -o meas.2.c.g.t -t ./gcc.gputest >>  log.2.c.g.t 2>&1
	@echo ""
	/bin/time -p hpcstruct --gpucfg yes meas.2.c.g.t
	@echo ""
	/bin/time -p hpcprof -o dbase.2.c.g.t meas.2.c.g.t
	@echo ""
	@echo ""

hpct3: gcc.gputest
	@echo "Starting \"hpct.3.c.g.t: -e CPUTIME-e gpu=nvidia -t\"" > log.3.c.g.t
	pwd >> log.1.c.g.t
	@echo "" >> log.1.c.g.t
	@echo ""
	export OMP_NUM_THREADS=3; /bin/time -p hpcrun -e CPUTIME -e gpu=nvidia -o meas.3.c.g.t -t ./gcc.gputest >> log.3.c.g.t 2>&1
	@echo ""
	/bin/time -p hpcstruct --gpucfg no --nocache meas.3.c.g.t
	@echo ""
	/bin/time -p hpcprof -o dbase.3.c.g.t meas.3.c.g.t
	@echo ""
	@echo ""

hpctpc1: gcc.gputest
	@echo "Starting \"hpct.1.c.gp.t: -e CPUTIME-e gpu=nvidia,pc -t\"" > log.1.c.gp.t
	pwd >> log.1.c.gp.t
	@echo "" >> log.1.c.gp.t
	@echo ""
	export OMP_NUM_THREADS=1; /bin/time -p hpcrun -e CPUTIME -e gpu=nvidia,pc -o meas.1.c.gp.t -t ./gcc.gputest >>  log.1.c.gp.t 2>&1
	@echo ""
	/bin/time -p hpcstruct --gpucfg no meas.1.c.gp.t
	@echo ""
	/bin/time -p hpcprof -o dbase.1.c.gp.t meas.1.c.gp.t
	@echo ""
	@echo ""

hpctpc2: gcc.gputest
	@echo "Starting \"hpct.2.c.gp.t: -e CPUTIME-e gpu=nvidia,pc -t\"" > log.2.c.gp.t
	pwd >> log.2.c.gp.t
	@echo "" >> log.2.c.gp.t
	@echo ""
	export OMP_NUM_THREADS=2; /bin/time -p hpcrun -e CPUTIME -e gpu=nvidia,pc -o meas.2.c.gp.t -t ./gcc.gputest >>  log.2.c.gp.t 2>&1
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
	-/bin/rm -f test.*.er
	@echo ""
	@echo ""

clobber: clean
	-/bin/rm -rf *.o gcc.gputest
	@echo ""
	@echo ""
