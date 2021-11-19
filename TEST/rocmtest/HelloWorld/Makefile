HIP_PATH?= $(wildcard /opt/rocm/hip)
ifeq (,$(HIP_PATH))
	HIP_PATH=../../..
endif

HIPCC=$(HIP_PATH)/bin/hipcc

TARGET=hcc

SOURCES = HelloWorld.cpp
OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE=./HelloWorld

all: $(EXECUTABLE)

CXXFLAGS =-g
CXX=$(HIPCC)

$(EXECUTABLE): $(OBJECTS)
	echo "HIPCC = ${HIPCC}"
	$(HIPCC) $(OBJECTS) -o $@


test: $(EXECUTABLE)
	$(EXECUTABLE)


clean: clobber
	rm -f $(EXECUTABLE)

clobber:
	-rm -f $(OBJECTS)
	-rm -f $(HIP_PATH)/src/*.o
	-rm -rf dbase* meas*

