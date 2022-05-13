#  To get a working aomp compiler:
# module use /home/johnmc/modules
# module load aomp

SRCS	= ../../../src/copy.cc 
TARGET	= copy.aomp

MARCH = -march=gfx90a
MARCH = -march=gfx906 

default all: $(TARGET)

CXX = amdclang++
OMPFLAGS = -g -lm -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa
OMPFLAGS = -g -lm -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa $(MARCH)

$(TARGET): ${SRCS}
	$(CXX) -DIGNORE_BAD_INITIAL_DEVICE $(OMPFLAGS) -o $(TARGET) ${SRCS}

run: $(TARGET)
	@@echo "Running $(TARGET)"
	@echo ""
	time ./$(TARGET)

hpct: hpct1 

hpct1: $(TARGET)
	export OMP_NUM_THREADS=1;  runhpct $(TARGET) "-e CPUTIME -e gpu=amd -t" hpct1.cg

clean:
	-/bin/rm -rf meas.*
	-/bin/rm -rf dbase.*
	-/bin/rm -f TESTS.log
	-/bin/rm -f *core*
	-/bin/rm -f log.*

clobber: clean
	-/bin/rm -rf *.o $(TARGET)
