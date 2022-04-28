#include <stdio.h>
#include <omp.h>

void check_copy(int *, int *);
void targ_par(int *, int *);
void team_par(int *, int *);
int rc = 0;
#define N 1000000
#define NITER 10

int main()
{

  int i;
  int a[N];
  int b[N];

  fprintf(stderr,"Initializing a[i] to 0; b[i] to i+1\n" );
  for (i=0; i<N; i++) {
    a[i]=0;
  }

  for (i=0; i<N; i++) {
    b[i]=i+1;
  }

  fprintf(stderr,"Invoking team_par\n" );
  team_par(a,b);
  check_copy(a, b);
  fprintf(stderr,"team_par and check_copy complete\n" );

  fprintf(stderr,"Reinitializing a[i] to 0\n" );

  for (i=0; i<N; i++) {
    a[i]=0;
  }

  fprintf(stderr,"Invoking targ_par\n" );
  targ_par (a, b);

  check_copy(a, b);
  fprintf(stderr,"targ_par and check_copy complete\n" );

  if (!rc)
    fprintf(stderr,"Success\n");
  else {
    fprintf(stderr, "  %d ERRORS detected\n", rc);
  }

  return rc;
}

void
check_copy(int *a, int *b)
{
  for (int i=0; i<N; i++)
    if (a[i] != b[i] ) {
      rc++;
      fprintf(stderr,"ERROR -- Wrong value: a[%d]=%d, not %d\n", i, a[i], b[i]);
    }
}

void
targ_par(int *a, int *b)
{
  int threadsPerBlock = 4;
  int blocksPerGrid = ( N + threadsPerBlock -1 ) / threadsPerBlock;

  #pragma omp target map(tofrom: a[0:N]) map(to: b[0:N])
  #pragma omp teams num_teams(blocksPerGrid) thread_limit(threadsPerBlock)
  #pragma omp distribute parallel for
  for (int i=0; i<1; i++) {
    for (int m = 0; m < NITER; m++ ) {
      for (int j = 0; j< N; j++) {
        a[j]=b[j];
      }
    }
  }
  return;
}

void
team_par(int *a, int *b)
{
  int threadsPerBlock = 256;
  int blocksPerGrid = ( N + threadsPerBlock -1 ) / threadsPerBlock;

  #pragma omp target map(tofrom: a[0:N]) map(to: b[0:N])
  #pragma omp teams num_teams(blocksPerGrid) thread_limit(threadsPerBlock)
  #pragma omp distribute parallel for
  for (int i=0; i<1; i++) {
    for (int m = 0; m < NITER; m++ ) {
      for (int j = 0; j< N; j++) {
        a[j]=b[j];
      }
    }
  }
  return;
}

  /// CHECK: Callback Init:
  /// CHECK: Callback Load:
  /// CHECK: Callback Target: target_id=[[TARGET_ID:[0-9]+]] kind=1 endpoint=1
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=1
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=2
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=1
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=2
  /// CHECK: Callback Submit: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] req_num_teams=1
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=3
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=3
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=4
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=4
  /// CHECK: Callback Target: target_id=[[TARGET_ID:[0-9]+]] kind=1 endpoint=2

  /// CHECK: Callback Target: target_id=[[TARGET_ID:[0-9]+]] kind=1 endpoint=1
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=1
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=2
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=1
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=2
  /// CHECK: Callback Submit: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] req_num_teams=0
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=3
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=3
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=4
  /// CHECK: Callback DataOp: target_id=[[TARGET_ID:[0-9]+]] host_op_id=[[HOST_OP_ID:[0-9]+]] optype=4
  /// CHECK: Callback Target: target_id=[[TARGET_ID:[0-9]+]] kind=1 endpoint=2
  /// CHECK: Callback Fini:
