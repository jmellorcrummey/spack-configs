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
#define	N 40000000	/* size of the data arrays used */
#define	NITER 3		/* number of iterations performed by each thread */

void output(int threadnum, double *p, size_t size, const char *label);
void init(double *p, size_t size);

size_t nn = N;
int niter = NITER;
int omp_num_t;

int
main(int argc, char *argv[], char **envp)
{
  // printf("sizeof(double) = %d; sizeof(double *) = %d\n", sizeof(double), sizeof(double*) );

  /* check number and accessibility of GPU devices */
  checkgpu();

  /* determine thread count */
  omp_num_t = omp_get_max_threads();
  printf ("This run of gputest will use %d thread%s with data array size = %ld\n",
    omp_num_t, (omp_num_t==1 ? "" : "s"), nn );

#ifdef USE_MPI
  int numtasks, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  printf("MPI task %d/%d\n", rank, numtasks);
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
      printf("Allocation for lptr[%d] failed; aborting\n", k);
      abort();
    }
    init(lptr[k], nn);

    rptr[k] = (double *) malloc (nn * sizeof(double) );
    if(rptr[k] == NULL) {
      printf("Allocation for rptr[%d] failed; aborting\n", k);
      abort();
    }
    init(rptr[k], nn);

    /* allocate and clear the result array */
    pptr[k] = (double *) calloc(nn, sizeof(double) );
    if(pptr[k] == NULL) {
      printf("Allocation for pptr[%d] failed; aborting\n", k);
      abort();
    }
  }

  // DEBUG -- print addresses and result contents
  printf("Initial allocation of arrays\n");
  for ( int k = 0; k < omp_num_t; k++) {
    printf( "Thread %d,      lptr[%d] = 0x%016llx; rptr[%d] = 0x%016llx, pptr[%d] = 0x%016llx\n",
      k, k, lptr[k], k, rptr[k], k, pptr[k] );
  }

  for ( int k = 0; k < omp_num_t; k++) {
    /* write out the last element in each thread's result array */
    // output(k, lptr[k], nn, "initial l array");
    // output(k, rptr[k], nn, "initial r array");
    output(k, pptr[k], nn, "initial p array");
  }
  printf("\n");

  /* perform the number of iterations requested */
  for (int k = 0; k < NITER; k++) {
    #pragma omp parallel
    {
      /* invoke the GPU-specific offloaded computation */
      twork(k, omp_get_thread_num() );
    }

    for ( int k = 0; k < omp_num_t; k++) {
      /* write out the last element in each thread's result array */
      // output(k, lptr[k], nn, "current l array");
      // output(k, rptr[k], nn, "current r array");
      output(k, pptr[k], nn, "current p array");
    }
    printf(" end iteration %d\n\n", k);
  }

  /* write out the last element in each thread's result array */
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
    p[i] = i+1;
  }
}

/* write out the last element from a double array, with a label */
void
output( int threadnum, double *p, size_t size, const char *label)
{
  size_t i = size -1;
  printf("%s -- thread %d, index %zu: %g; index %zu: %g\n", label, threadnum, 0, p[0], i, p[i]);
}
