SRCS	= ../../src/copy.cc 
TARGET	= nvidia.copy.gcc

MARCH = -march=gfx90a
MARCH = -march=gfx906

default all: $(TARGET)

CXX = gcc
OMPFLAGS = -g -lm -fopenmp -foffload=nvptx-none="-O2 -lm"
OMPFLAGS = -g -lm -fopenmp -foffload="-O2 -lm -misa=sm_35"

$(TARGET): ${SRCS}
	$(CXX) -DIGNORE_BAD_INITIAL_DEVICE $(OMPFLAGS) -o $(TARGET) ${SRCS}

run: $(TARGET)
	@@echo "Running $(TARGET)"
	@echo ""
	/bin/time -p ./$(TARGET)

hpct: hpct1  hpctpc1

hpct1: $(TARGET)
	export OMP_NUM_THREADS=1; runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia -t" hpct1.cg

hpctpc1: $(TARGET)
	export OMP_NUM_THREADS=1; runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia,pc -t" hpct1.cgp

collect: $(TARGET)
	collect -p hi $(TARGET)
	er_print -func test.1.er

clean:
	-/bin/rm -rf meas.*
	-/bin/rm -rf dbase.*
	-/bin/rm -f *core*
	-/bin/rm -f log.*
	-/bin/rm -rf test.*.er

clobber: clean
	-/bin/rm -rf *.o $(TARGET)
