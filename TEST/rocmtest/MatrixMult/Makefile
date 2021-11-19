HIP_PATH?= $(wildcard /opt/rocm/hip)
ifeq (,$(HIP_PATH))
	HIP_PATH=../../..
endif

HIPCC=$(HIP_PATH)/bin/hipcc

TARGET=hcc

SOURCES = MatrixMultiplication.cpp
OBJECTS = $(SOURCES:.cpp=.o)

MAKE_INCLUDE = ..


EXECUTABLE=./MatrixMultiplication

all: $(EXECUTABLE)

CXXFLAGS =-g
CXX=$(HIPCC)


$(EXECUTABLE): $(OBJECTS)
	$(HIPCC) -I ${MAKE_INCLUDE} $(OBJECTS) -o $@


run: $(EXECUTABLE)
	time $(EXECUTABLE)
	echo ""

hpct:  $(EXECUTABLE)
	# echo "Starting \"hpct.c.g.t: -e CPUTIME-e gpu=amd -t\""
	echo ""
	time hpcrun -e CPUTIME -e gpu=amd -o meas.c.g.t -t $(EXECUTABLE)
	echo ""
	time hpcstruct meas.c.g.t
	echo ""
	time hpcprof -o dbase.c.g.t meas.c.g.t
	echo ""
	echo "============================================"
	echo ""

clean:
	rm -f $(OBJECTS)
	-/bin/rm -rf meas.*
	-/bin/rm -rf dbase.*
	-/bin/rm -f *core*

clobber: clean
	rm -f $(EXECUTABLE)

