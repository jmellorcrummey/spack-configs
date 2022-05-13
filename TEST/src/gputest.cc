#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <omp.h>

#include "gputest.h"
double **lptr;
double **rptr;
double **pptr;


#ifdef USE_MPI
#include <mpi.h>
#endif

/* Parameters governing the size of the test */
#define        N 40000000      /* size of the data arrays used */
#define        NITER 3         /* number of iterations performed by each thread */

void output(int threadnum, double *p, size_t size, const char *label);
void init(double *p, size_t size);

size_t nn = N;
int niter = NITER;
int omp_num_t;

int
main(int argc, char *argv[], char **envp)
{
  //fprintf(stderr, "sizeof(double) = %d; sizeof(double *) = %d\n", sizeof(double), sizeof(double*) );

  /* check number and accessibility of GPU devices */
  checkgpu();

  /* determine thread count */
  omp_num_t = omp_get_max_threads();
  fprintf(stderr, "This run of gputest will use %d thread%s with data array size = %ld\n",
    omp_num_t, (omp_num_t==1 ? "" : "s"), nn );

#ifdef USE_MPI
  int numtasks, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  fprintf(stderr, "MPI task %d/%d\n", rank, numtasks);
#endif

  /* allocate pointer arrays for the threads */
  rptr = (double **) calloc(omp_num_t, sizeof(double *) );
  lptr = (double **) calloc(omp_num_t, sizeof(double *) );
  pptr = (double **) calloc(omp_num_t, sizeof(double *) );

  /* allocate the l, r, and p arrays for each thread */
  for ( int k = 0; k < omp_num_t; k++) {
    /* allocate and initialize the l and r arrays */
    lptr[k] = (double *) malloc (nn * sizeof(double) );
    if(lptr[k] == NULL) {
      fprintf(stderr, "Allocation for lptr[%d] failed; aborting\n", k);
      abort();
    }
    init(lptr[k], nn);

    rptr[k] = (double *) malloc (nn * sizeof(double) );
    if(rptr[k] == NULL) {
      fprintf(stderr, "Allocation for rptr[%d] failed; aborting\n", k);
      abort();
    }
    init(rptr[k], nn);

    /* allocate and clear the result array */
    pptr[k] = (double *) calloc(nn, sizeof(double) );
    if(pptr[k] == NULL) {
      fprintf(stderr, "Allocation for pptr[%d] failed; aborting\n", k);
      abort();
    }
  }

  // DEBUG -- print addresses and result contents
#if 0
  fprintf(stderr, "Initial allocation of arrays\n");
  for ( int k = 0; k < omp_num_t; k++) {
    fprintf(stderr,  "Thread %d,      lptr[%d] = %p; rptr[%d] = %p, pptr[%d] = %p\n",
      k, k, lptr[k], k, rptr[k], k, pptr[k] );
  }
#endif

  for ( int k = 0; k < omp_num_t; k++) {
    /* write out the last element in each thread's result array */
    // output(k, lptr[k], nn, "initial l array");
    // output(k, rptr[k], nn, "initial r array");
    // output(k, pptr[k], nn, "initial p array");
  }
  fprintf(stderr, "\n");

  /* perform the number of iterations requested */
  for (int k = 0; k < NITER; k++) {
    #pragma omp parallel
    {
      /* invoke the GPU-specific offloaded computation */
      twork(k, omp_get_thread_num() );
    }

#if 0
    for ( int k = 0; k < omp_num_t; k++) {
      /* write out the last element in each thread's result array */
      // output(k, lptr[k], nn, "current l array");
      // output(k, rptr[k], nn, "current r array");
      output(k, pptr[k], nn, "current p array");
    }
#endif
    fprintf(stderr, " end iteration %d\n", k);
  }

  /* write out various elements in each thread's result array */
  for (int k = 0; k < omp_num_t; k++) {
    output(k, pptr[k], nn, "result p array");
  }

#ifdef USE_MPI
  MPI_Finalize();
#endif
  return 0;
}

/* initialize a double array with each element set to its index */
void
init(double *p, size_t size)
{
  for (size_t i = 0; i < size; ++i) {
    p[i] = (double) (i+1);
  }
}

/* write out the last element from a double array, with a label */
void
output( int threadnum, double *p, size_t size, const char *label)
{
  size_t i = size -1;
  size_t j = size/8;
  size_t k = size/16;
  fprintf(stderr, "%s -- t %d, p[%zu]=%g; p[%zu]=%g; p[%zu]=%g; p[%zu]=%g; p[%zu]=%g\n",
    label, threadnum, 0UL, p[0], 1UL, p[1], k, p[k], j, p[j], i, p[i]);
  int cnt = 0;
  for( int m = 0; m < size; m++) {
    if (p[m] != p[0]) {
      fprintf(stderr, "     ==> ERROR -- thread %d: p[%d]=%g != p[0]\n",
        threadnum, m, p[m]);
      cnt ++;
      if (cnt >= 5) {
        fprintf(stderr, "  and possibly many more ERRORs\n");
        return;
      }
    }
  }
}
