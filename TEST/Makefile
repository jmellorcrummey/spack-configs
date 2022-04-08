TARGET	= struct

default all: $(TARGET)

struct: gcc.gputest
	@echo "Starting \"hpcstruct gcc.gputest\""
	/bin/time -p hpcstruct gcc.gputest
	@echo ""
	grep "<LM" *.hpcstruct
	@echo ""
	@echo ""

nocache: gcc.gputest
	@echo "Starting \"hpcstruct gcc.gputest\""
	/bin/time -p hpcstruct --nocache gcc.gputest
	@echo ""
	grep "<LM" *.hpcstruct
	@echo ""
	@echo ""

clean: 
	-/bin/rm -f *.hpcstruct
	(cd nvidia; make clean)
	(cd nvidia/omp.gcc; make clean)
	@echo ""
	@echo ""

clobber: clean
	-/bin/rm -rf log*
	-/bin/rm -rf MYCACHE
	@echo ""
	@echo ""

#  setup cleans up everything, and the goes into nvidia/omp.gcc, runs make, and copied the gcc.gputest
#	to the this directory

setup: clobber
	(cd nvidia/omp.gcc; make)
	cp nvidia/omp.gcc/gcc.gputest .
