#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <omp.h>

#ifdef USE_MPI
#include <mpi.h>
#endif

#define	N 10000000
#define	NITER 3
#define	INNERITER 2

void output(double *p, size_t size, const char *label);
void init(double *p, size_t size);
void t1work();
void t2work();

double l1[N], l2[N];
double r1[N], r2[N];
double p1[N], p2[N];
size_t nn = N;
int niter = NITER;
int omp_num_t;

int
main(int argc, char *argv[], char **envp)
{

  printf ("main entered N = %ld\n", nn);
  init(l1, nn);
  printf ("init of l1 done\n");
  init(r1, nn);
  printf ("init of r1 done\n");
  init(l2, nn);
  printf ("init of l2 done\n");
  init(r2, nn);
  printf ("init of r2 done\n");

  /* Test if GPU is available using OpenMP4.5 */
  int	numdev = omp_get_num_devices();
  printf ("Machine has %d GPU device%s\n", numdev, (numdev==1 ? "" : "s") );
  int	idev = omp_is_initial_device();

  int runningOnGPU = -1;
  #pragma omp target data map(from:runningOnGPU)
  #pragma omp target
  {
    runningOnGPU = omp_is_initial_device();
  }

  /* If still running on CPU, GPU must not be available */
  if (runningOnGPU != 0) {
    printf("### gputest is unable to use the GPU! idev = %d, runningOnGpU -- omp_is_initial_device() = %d\n", idev, runningOnGPU);
    exit(1);
  } else {
    printf("### gputest is able to use the GPU! idev = %d, runningOnGpU -- omp_is_initial_device()\n", idev );
    omp_num_t = omp_get_max_threads();
    printf("-- launching omp target loops on %d CPU thread%s\n", omp_num_t, omp_num_t ==1? "":"s" );
  }

#ifdef USE_MPI
  int numtasks, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  printf("MPI task %d/%d\n", rank, numtasks);
#endif
  for (int k = 0; k < NITER; k++) {
    #pragma omp parallel
    {
      if (omp_get_thread_num() == 0) {
        t1work();
      } else if (omp_get_thread_num() == 1) {
        t2work();
      }
    }

  }
  output(p1, nn, "p1");
  if ( omp_num_t != 1) {
    output(p2, nn, "p2");
  }

#ifdef USE_MPI
  MPI_Finalize();
#endif
  return 0;
}

void
init(double *p, size_t size)
{
  for (size_t i = 0; i < size; ++i) {
    p[i] = i;
  }
}

void
output(double *p, size_t size, const char *label)
{
  size_t i = size -1;
  printf("%s -- index %zu: %g\n", label, i, p[i]);
}

void
t1work()
{
        #pragma omp target data map(to:l1[0:nn], r1[0:nn]) map(tofrom: p1[0:nn])
        {
        #pragma omp target
        #pragma omp teams num_teams(4) thread_limit(64)
        {
          #pragma omp distribute parallel for
          for (size_t i = 0; i < nn; ++i) {
	    for (int j = 0; j < INNERITER; j++ ) {
              p1[i] = sqrt( exp( log (l1[i]*l1[i]) ) + exp( log (r1[i]*r1[i]) ) /
                exp( log(l2[i]*l2[i]) ) + exp( log( (r2[i]*r2[i]) )) );
	    }
          }
        }
        }
}

void
t2work()
{
        #pragma omp target data map(to:l2[0:nn], r2[0:nn]) map(tofrom: p2[0:nn])
        {
        #pragma omp target
        #pragma omp teams num_teams(4) thread_limit(64)
        {
          #pragma omp distribute parallel for
          for (size_t i = 0; i < nn; ++i) {
            p2[i] = sqrt( exp( log (l1[i]*l1[i]) ) + exp( log (r1[i]*r1[i])) ) /
              sqrt( exp( log(l2[i]*l2[i]) ) + exp( log( (r2[i]*r2[i]) )) );
          }
        }
        }
}
