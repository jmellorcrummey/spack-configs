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

  {
    #pragma omp parallel for
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
  fprintf(stderr, "This run does not use any GPU devices\n");
}

int
checkxfers()
{
  return 0;
}
