all: show tool.so run

run:
	LD_PRELOAD=./tool.so ./show
tool.so:
	gcc -o tool.so -shared -fPIC tool.c

show:
	gcc -o show -fopenmp show.c

clean:
	rm -f show tool.so
