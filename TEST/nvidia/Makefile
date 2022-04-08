TARGET	= struct

default all: $(TARGET)

struct: gcc.gputest 205259747422e8dcb2b6f2b6794e44e3.gpubin
	@echo "Starting \"hpcstruct gcc.gputest\""
	/bin/time -p hpcstruct gcc.gputest
	@echo ""
	@echo ""
	@echo "Starting \"hpcstruct 205259747422e8dcb2b6f2b6794e44e3.gpubin\" --gpucfg no"
	/bin/time -p hpcstruct --gpucfg no 205259747422e8dcb2b6f2b6794e44e3.gpubin
	@echo ""
	@echo ""
	@echo "Starting \"hpcstruct 205259747422e8dcb2b6f2b6794e44e3.gpubin\" --gpucfg yes"
	/bin/time -p hpcstruct --gpucfg yes 205259747422e8dcb2b6f2b6794e44e3.gpubin
	@echo ""
	grep "<LM" *.hpcstruct
	@echo ""
	@echo ""

nocache: gcc.gputest 205259747422e8dcb2b6f2b6794e44e3.gpubin
	@echo "Starting \"hpcstruct gcc.gputest\""
	/bin/time -p hpcstruct --nocache gcc.gputest
	@echo ""
	@echo ""
	@echo "Starting \"hpcstruct 205259747422e8dcb2b6f2b6794e44e3.gpubin\" "
	/bin/time -p hpcstruct --nocache --gpucfg no 205259747422e8dcb2b6f2b6794e44e3.gpubin
	@echo ""
	grep "<LM" *.hpcstruct
	@echo ""
	@echo ""

clean clobber: 
	-/bin/rm -f *.hpcstruct
	@echo ""
	@echo ""
