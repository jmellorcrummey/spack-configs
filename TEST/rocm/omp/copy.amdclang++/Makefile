#  To get a working aomp compiler:
# module use /home/johnmc/modules
# module load aomp

SRCS	= ../../../src/copy.cc 
TARGET	= copy

MARCH = -march=gfx90a
MARCH = -march=gfx906 

default all: $(TARGET)

CXX = amdclang++
OMPFLAGS = -g -lm -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa $(MARCH)

$(TARGET): ${SRCS}
	$(CXX) -DIGNORE_BAD_INITIAL_DEVICE $(OMPFLAGS) -o $(TARGET) ${SRCS}

run: $(TARGET)
	@@echo "Running $(TARGET)"
	@echo ""
	time ./$(TARGET)

hpct: hpct1 

hpct1: $(TARGET)
	@echo "Starting \"hpct.1.c.g.t: -e CPUTIME-e gpu=amd -t\""
	@echo ""
	export OMP_NUM_THREADS=1; time hpcrun -e CPUTIME -e gpu=amd -o meas.1.c.g.t -t ./$(TARGET)  > log.1.c.g.t 2>&1
	@echo ""
	time hpcstruct meas.1.c.g.t
	@echo ""
	time hpcprof -o dbase.1.c.g.t meas.1.c.g.t
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
	-/bin/rm -rf *.o $(TARGET)
