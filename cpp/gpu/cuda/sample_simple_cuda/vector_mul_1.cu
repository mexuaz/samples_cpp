#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cuda.h>
#include <cuda_runtime.h>

__host__
__device__
void vector_mul(float *out, float *a,
        float *b, size_t n) {
    for(size_t i = 0; i < n; i ++){
        out[i] = a[i] * b[i];
    }
}

__global__
void vector_mul_gpu(float* d_out, float* d_a,
        float* d_b, size_t n) {
    vector_mul(d_out, d_a, d_b, n);
}

int main(int argc, char** argv){

    size_t N = 1000'000'000;
    if (argc > 1) {
        N = strtoul(argv[1], 0, 0);
    }

    float *a, *b, *out;
    float *d_a, *d_b, *d_out;

    // Allocate host memory
    a   = (float*)malloc(sizeof(float) * N);
    b   = (float*)malloc(sizeof(float) * N);
    out = (float*)malloc(sizeof(float) * N);

    // Initialize host arrays
    std::mt19937 eng{std::random_device()()};
    std::generate(a, a+N, [&eng]() {
        return std::uniform_real_distribution<float>{0.f, 1.f}(eng);
    });

    std::generate(b, b+N, [&eng]() {
        return std::uniform_real_distribution<float>{1.f, 2.f}(eng);
    });


    // Allocate device memory
    cudaMalloc((void**)&d_a, sizeof(float) * N);
    cudaMalloc((void**)&d_b, sizeof(float) * N);
    cudaMalloc((void**)&d_out, sizeof(float) * N);

    // Transfer data from host to device memory
    cudaMemcpy(d_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, sizeof(float) * N, cudaMemcpyHostToDevice);

    // Executing in kernel
    int blockCount = 5;
    int threadCount = 500;
    vector_mul_gpu<<<blockCount, threadCount>>>(d_out, d_a, d_b, N);

    cudaDeviceSynchronize();

    // Transfer data back to host memory
    cudaMemcpy(out, d_out, sizeof(float) * N, cudaMemcpyDeviceToHost);

    // Deallocate device memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_out);

    // profiling for CPU
    auto s = std::chrono::high_resolution_clock::now();

    vector_mul(out, a, b, N);

    auto d = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s).count();
    std::cout << d << " ms CPU" << std::endl;

    // Deallocate host memory
    free(a); 
    free(b); 
    free(out);
}
