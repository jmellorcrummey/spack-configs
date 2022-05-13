HIP_PATH?= $(wildcard /opt/rocm/hip)
ifeq (,$(HIP_PATH))
	HIP_PATH=../../..
endif

HIPCC=$(HIP_PATH)/bin/hipcc

ARGS = -q -x 4096

SOURCES = MatrixMultiplication.cpp

MAKE_INCLUDE = ..

EXECUTABLE=./MatrixMultiplication

ARGS=-q -x 4096

default all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(HIPCC) -g -I ${MAKE_INCLUDE} $(SOURCES) -o $@


run: $(EXECUTABLE)
	time $(EXECUTABLE) $(ARGS)
	echo ""

hpctrun:  $(EXECUTABLE)
	# echo "Starting \"hpct.c.g.t: -e CPUTIME-e gpu=amd -t\""
	echo ""
	time hpcrun -e CPUTIME -e gpu=openmp -o meas.c.g.t -t $(EXECUTABLE) $(ARGS)
	echo ""
	echo "============================================"

hpct:  $(EXECUTABLE)
	# echo "Starting \"hpct.c.g.t: -e CPUTIME-e gpu=amd -t\""
	echo ""
	time hpcrun -e CPUTIME -e gpu=openmp -o meas.c.g.t -t $(EXECUTABLE) $(ARGS)
	echo ""
	time hpcstruct meas.c.g.t
	echo ""
	time hpcprof -o dbase.c.g.t meas.c.g.t
	echo ""
	echo "============================================"
	echo ""

clean:
	-/bin/rm -rf meas.*
	-/bin/rm -rf dbase.*
	-/bin/rm -f *core*

clobber: clean
	rm -f $(EXECUTABLE)

