#ifndef __KERNELS_CUH__
#define __KERNELS_CUH__

#include <curand_kernel.h>

__global__ void setup_kernel(curandState *state);
__global__ void monti_carlo_pi_kernel(curandState *state, int *count, int m);

#endif


