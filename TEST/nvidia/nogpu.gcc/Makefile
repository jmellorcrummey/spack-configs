SRCS	= ../../src/gputest.cc ../../src/nogpu.cc
TARGET	= gcc.gputest

default all: $(TARGET)

# This version is built with GCC; ../omp.llvm contains the version built with LLVM
CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm

gcc.gputest: ${SRCS}
	$(CXX) $(OMPFLAGS) -o gcc.gputest ${SRCS}

struct: gcc.gputest
	@echo "Starting \"hpcstruct gcc.gputest\""
	/bin/time -p hpcstruct gcc.gputest
	@echo ""
	@echo ""

run: gcc.gputest
	@echo "Running \"gcc.gputest\""
	@echo ""
	/bin/time -p ./gcc.gputest
	@echo ""
	@echo ""

hpct: hpct1 hpct2 hpctpc1 hpctpc2

hpct1: gcc.gputest
	@echo "Starting \"hpct.1.c.g.t: -e CPUTIME -t\""
	@echo ""
	export OMP_NUM_THREADS=1; /bin/time -p hpcrun -e CPUTIME -o meas.1.c.g.t -t ./gcc.gputest | tee log.1.c.g.t 2>&1
	@echo ""
	/bin/time -p hpcstruct meas.1.c.g.t
	@echo ""
	/bin/time -p hpcprof -o dbase.1.c.g.t meas.1.c.g.t
	@echo ""
	@echo ""

hpct2: gcc.gputest
	@echo "Starting \"hpct.2.c.g.t: -e CPUTIME -t\""
	@echo ""
	export OMP_NUM_THREADS=2; /bin/time hpcrun -e CPUTIME -o meas.2.c.g.t -t ./gcc.gputest | tee  log.2.c.g.t 2>&1
	@echo ""
	/bin/time -p hpcstruct meas.2.c.g.t
	@echo ""
	/bin/time -p hpcprof -o dbase.2.c.g.t meas.2.c.g.t
	@echo ""
	@echo ""

hpct3: gcc.gputest
	@echo "Starting \"hpct.3.c.g.t: -e CPUTIME -t\""
	@echo ""
	export OMP_NUM_THREADS=1; /bin/time -p hpcrun -e CPUTIME -o meas.3.c.g.t -t ./gcc.gputest | tee log.3.c.g.t 2>&1
	@echo ""
	/bin/time -p hpcstruct --nocache meas.3.c.g.t
	@echo ""
	/bin/time -p hpcprof -o dbase.3.c.g.t meas.3.c.g.t
	@echo ""
	@echo ""

hpctpc1: gcc.gputest
	@echo "Starting \"hpct.1.c.gp.t: -e CPUTIME -t\""
	@echo ""
	export OMP_NUM_THREADS=1; /bin/time -p hpcrun -e CPUTIME -o meas.1.c.gp.t -t ./gcc.gputest | tee  log.1.c.gp.t 2>&1
	@echo ""
	/bin/time -p hpcstruct meas.1.c.gp.t
	@echo ""
	/bin/time -p hpcprof -o dbase.1.c.gp.t meas.1.c.gp.t
	@echo ""
	@echo ""

hpctpc2: gcc.gputest
	@echo "Starting \"hpct.2.c.gp.t: -e CPUTIME -t\""
	@echo ""
	export OMP_NUM_THREADS=2; /bin/time -p hpcrun -e CPUTIME -o meas.2.c.gp.t -t ./gcc.gputest | tee  log.2.c.gp.t 2>&1
	@echo ""
	/bin/time -p hpcstruct meas.2.c.gp.t
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
	-/bin/rm -rf *.o gcc.gputest
	@echo ""
	@echo ""
