#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <omp.h>

extern size_t nn;

extern double **lptr;
extern double **rptr;
extern double **pptr;

/* routine to determine if GPU is available, and how many devices */
void checkgpu();

/* routine to do the off-loaded work on the GPU */
void twork(int iter, int threadnum);

