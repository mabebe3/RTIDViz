
#include "cuda_functions.h"
#include <iostream>
#include <cuda_runtime.h>


__global__ void testKernel(int* data, int N)
{
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    if (idx < N) {
        data[idx] = idx * 2;
    }
}

void run_my_cuda_example()
{
    const int N = 5;
    int* d_data = nullptr;

    cudaMalloc(&d_data, N * sizeof(int));
    testKernel << <1, N >> > (d_data, N);

    int h_data[N] = {};
    cudaMemcpy(h_data, d_data, N * sizeof(int), cudaMemcpyDeviceToHost);

    std::cout << "[CUDA] Kernel result: ";
    for (int i = 0; i < N; ++i) {
        std::cout << h_data[i] << (i < N - 1 ? ", " : "\n");
    }

    cudaFree(d_data);
}
