#include "gputest.h"
#include <cuda.h>
#include <cuda_runtime_api.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

int checkxfers();

#if 1
__global__ void
xcompute(const double *d_l1, const double *d_r1, double *d_p1, int nelements )
{
  int i = blockDim.x * blockIdx.x + threadIdx.x;
  if (i < nelements) {
    d_p1[i] = d_p1[i] + 1.+ (sqrt( exp( log (d_l1[i]*d_l1[i]) ) + exp( log (d_r1[i]*d_r1[i]) ) ) ) /
        ( sqrt (exp( log(d_l1[i]*d_r1[i]) ) + exp( log( (d_r1[i]*d_l1[i]) )) ) );
  }
}
#endif

void
twork( int iter, int threadnum)
{
  double *l1 = lptr[threadnum];
  double *r1 = rptr[threadnum];
  double *p1 = pptr[threadnum];

  cudaError_t err = cudaSuccess;

  //allocate device memory for copying in l1 and r1, copying out p1
  size_t size = nn * sizeof(double);
  double *d_l1 = NULL;
  double *d_r1 = NULL;
  double *d_p1 = NULL;
  err = cudaMalloc((void **)&d_l1, size);
  if (err != cudaSuccess) {
    fprintf(stderr, "Failed to allocate device vector d_l1 (error code %s)!\n", cudaGetErrorString(err));
    exit(-1);
#if 1
  } else {
    fprintf(stderr, "Allocated device vector d_l1\n" );
#endif
  }
  err = cudaMalloc((void **)&d_r1, size);
  if (err != cudaSuccess) {
    fprintf(stderr, "Failed to allocate device vector d_r1 (error code %s)!\n", cudaGetErrorString(err));
    exit(-1);
#if 1
  } else {
    fprintf(stderr, "Allocated device vector d_r1\n" );
#endif
  }
  err = cudaMalloc((void **)&d_p1, size);
  if (err != cudaSuccess) {
    fprintf(stderr, "Failed to allocate device vector d_p1 (error code %s)!\n", cudaGetErrorString(err));
    exit(-1);
#if 1
  } else {
    fprintf(stderr, "Allocated device vector d_p1\n" );
#endif
  }

  // Copy l1 and r1 to the device
  err = cudaMemcpy(d_l1, l1, size, cudaMemcpyHostToDevice);
  if (err != cudaSuccess) {
    fprintf(stderr, "Failed to copy device l1 to d_l1 (error code %s)!\n", cudaGetErrorString(err));
    exit(-1);
#if 1
  } else {
    fprintf(stderr, "Copied l1 to device vector d_l1\n" );
#endif
  }
  err = cudaMemcpy(d_r1, r1, size, cudaMemcpyHostToDevice);
  if (err != cudaSuccess) {
    fprintf(stderr, "Failed to copy device r1 to d_r1 (error code %s)!\n", cudaGetErrorString(err));
    exit(-1);
#if 1
  } else {
    fprintf(stderr, "Copied r1 to device vector d_r1\n" );
#endif
  }

  // Set up and launch the CUDA kernel
  int threadsPerBlock = 256;
  int blocksPerGrid = ( nn + threadsPerBlock -1 ) / threadsPerBlock;
#if 1
  xcompute<<<blocksPerGrid, threadsPerBlock>>>(d_l1, d_r1, d_p1, nn);
  err = cudaGetLastError();
  if (err != cudaSuccess) {
    fprintf(stderr, "Failed to launch compute kernel (error code %s)!\n", cudaGetErrorString(err));
    exit(-1);
#if 1
  } else {
    fprintf(stderr, "Ran GPU kernel for xcompute\n" );
#endif
  }
#endif

  // Copy p1 back to the host
  err = cudaMemcpy(p1, d_p1, size, cudaMemcpyDeviceToHost);
  if (err != cudaSuccess) {
    fprintf(stderr, "Failed to copy p1 from device (error code %s)!\n", cudaGetErrorString(err));
    exit(-1);
#if 1
  } else {
    fprintf(stderr, "Copied d_p1 back to host\n" );
#endif
  }

  // Free the device memory
  err = cudaFree(d_l1);
  if (err != cudaSuccess) {
    fprintf(stderr, "Failed to free d_l1 from device (error code %s)!\n", cudaGetErrorString(err));
    exit(-1);
#if 1
  } else {
    fprintf(stderr, "Freed device vector d_l1\n" );
#endif
  }
  err = cudaFree(d_r1);
  if (err != cudaSuccess) {
    fprintf(stderr, "Failed to free d_r1 from device (error code %s)!\n", cudaGetErrorString(err));
    exit(-1);
#if 1
  } else {
    fprintf(stderr, "Freed device vector d_r1\n" );
#endif
  }
  err = cudaFree(d_p1);
  if (err != cudaSuccess) {
    fprintf(stderr, "Failed to free d_p1 from device (error code %s)!\n", cudaGetErrorString(err));
    exit(-1);
#if 1
  } else {
    fprintf(stderr, "Freed device vector d_p1\n" );
#endif
  }
  fprintf(stderr, "\nCompleted iteration %d, thread %d\n\n", iter, threadnum);

}

void
checkgpu()
{
#if 0
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
    printf(" ERROR unable to use the GPU! idev = %d, runningOnGpU -- omp_is_initial_device() = %d; exiting\n", idev, runningOnGPU);
    exit(1);
#else
    printf(" ERROR IGNORED idev = %d, runningOnGpU -- omp_is_initial_device() = %d; trying anyway\n", idev, runningOnGPU);
#endif
  } else {
    printf("    gputest is able to use the GPU! idev = %d, runningOnGpU -- omp_is_initial_device()\n", idev );
  }

  int ret = checkxfers();
  if (ret != 0 ) {
    printf("Return from checkxfers = %d\n", ret);
  }
#endif
}

int
checkxfers()
{
#if 0
  int to = 11;
  int from = 13;
  int tofrom = 17;

  printf("ON HOST before: to = %d, from = %d, tofrom = %d\n", to, from, tofrom);

  #pragma omp target map (to:to) map(from:from) map(tofrom:tofrom)
  {
    printf("ON GPU: enter to = %d, from = %d, tofrom = %d\n", to, from, tofrom); 

    to = 4;
    from = 5;
    tofrom = 6; 

    printf("ON GPU: exit to = %d, from = %d, tofrom = %d\n", to, from, tofrom); 
  }

  printf("ON HOST after: to = %d, from = %d, tofrom = %d\n", to, from, tofrom);
#endif

  return 0;
}
