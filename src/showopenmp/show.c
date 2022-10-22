#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
#pragma omp parallel num_threads(2)
	{
	printf("hello world from thread %d\n", omp_get_thread_num());
	}
	return 0;
}
