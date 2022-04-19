#include <string.h>
#include "gputest.h"

int checkxfers();

void
twork( int iter, int threadnum)
{
  double *l1 = lptr[threadnum];
  double *r1 = rptr[threadnum];
  double *p1 = pptr[threadnum];

#if 0
  fprintf(stderr, "Iteration %3d,   l1[%d] = 0x%016llx;   r1[%d] = 0x%016llx;   p1[%d] = 0x%016llx\n",
    iter, threadnum, l1, threadnum, r1, threadnum, p1 );
#endif

  #pragma omp target map(to:l1[0:nn-1], r1[0:nn-1]) map(tofrom: p1[0:nn-1])
  #pragma omp teams num_teams(4) thread_limit(64)
  {
    #pragma omp distribute parallel for
    for (size_t i = 0; i < nn; ++i) {
      p1[i] = p1[i] + 1.+ (sqrt( exp( log (l1[i]*l1[i]) ) + exp( log (r1[i]*r1[i]) ) ) ) /
        ( sqrt (exp( log(l1[i]*r1[i]) ) + exp( log( (r1[i]*l1[i]) )) ) );
    }
  }
}

void
checkgpu()
{
  /* determine number of GPU's */
  int numdev = omp_get_num_devices();
  printf ("Machine has %d GPU device%s\n", numdev, (numdev==1 ? "" : "s") );

  /* Test if GPU is available */
  int	idev = omp_is_initial_device();

  int runningOnGPU = -1;
  #pragma omp target map(from:runningOnGPU)
  {
    runningOnGPU = omp_is_initial_device();
  }

  /* If still running on CPU, GPU must not be available */
  if (runningOnGPU != 0) {
#ifndef IGNORE_BAD_INITIAL_DEVICE
    fprintf(stderr, " ERROR unable to use the GPU! idev = %d, runningOnGpU -- omp_is_initial_device() = %d; exiting\n", idev, runningOnGPU);
    exit(1);
#else
    fprintf(stderr, " ERROR IGNORED idev = %d, runningOnGpU -- omp_is_initial_device() = %d; trying anyway\n", idev, runningOnGPU);
#endif
  } else {
    fprintf(stderr, "    gputest is able to use the GPU! idev = %d, runningOnGpU -- omp_is_initial_device()\n", idev );
  }

  int ret = checkxfers();
  if (ret != 0 ) {
    fprintf(stderr, "Return from checkxfers = %d\n", ret);
  }
}

int
checkxfers()
{
  int to = 11;
  int from = 13;
  int tofrom = 17;

  fprintf(stderr, "ON HOST before: to = %d, from = %d, tofrom = %d\n", to, from, tofrom);

  #pragma omp target map (to:to) map(from:from) map(tofrom:tofrom)
  {
    fprintf(stderr, "ON GPU: enter to = %d, from = %d, tofrom = %d\n", to, from, tofrom); 

    to = 4;
    from = 5;
    tofrom = 6; 

    fprintf(stderr, "ON GPU: exit to = %d, from = %d, tofrom = %d\n", to, from, tofrom); 
  }

  fprintf(stderr, "ON HOST after: to = %d, from = %d, tofrom = %d\n", to, from, tofrom);

  return 0;
}
