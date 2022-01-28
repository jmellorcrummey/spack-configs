HIP_PATH?= $(wildcard /opt/rocm/hip)
ifeq (,$(HIP_PATH))
	HIP_PATH=../../..
endif

HIPCC=$(HIP_PATH)/bin/hipcc

TARGET=hcc

SOURCES = HelloWorld.cpp

EXECUTABLE=./HelloWorld

all: $(EXECUTABLE)

CXX=$(HIPCC)

$(EXECUTABLE): $(SOURCES)
	echo "HIPCC = ${HIPCC}"
	$(HIPCC) -g $(SOURCES) -o $@


run: $(EXECUTABLE)
	time $(EXECUTABLE)
	echo ""

hpct: $(EXECUTABLE)
	time hpcrun -e CPUTIME -e gpu=amd -o meas.HelloWorld -t $(EXECUTABLE)
	echo ""
	time hpcstruct meas.HelloWorld
	echo ""
	time hpcprof -o dbase.HelloWorld meas.HelloWorld
	echo ""
	echo "============================================"
	echo ""


clobber: clean
	rm -f $(EXECUTABLE)

clean:
	-rm -rf dbase* meas*

