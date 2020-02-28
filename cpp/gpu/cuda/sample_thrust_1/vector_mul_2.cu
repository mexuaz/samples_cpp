#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cuda.h>
#include <cuda_runtime.h>

#include <thrust/version.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/transform.h>
#include <thrust/execution_policy.h>

// nvcc --expt-extended-lambda -std=c++14 vector_mul_2.cu -o vector_mul2

int main(int argc, char** argv){

    size_t N = 100'000'000;
    if (argc > 1) {
        N = strtoul(argv[1], 0, 0);
    }

    thrust::host_vector<float> a(N), b(N), out(N);
    thrust::device_vector<float> d_a, d_b, d_out(N);

    // Initialize host arrays
    std::mt19937 eng{std::random_device()()};
    std::generate(a.begin(), a.end(), [&eng]() {
        return std::uniform_real_distribution<float>{0.f, 1.f}(eng);
    });

    std::generate(b.begin(), b.end(), [&eng]() {
        return std::uniform_real_distribution<float>{1.f, 2.f}(eng);
    });

    // Transfer data from host to device memory
    d_a = a;
    d_b = b;
    auto fm = [=]  __device__ (float a, float b) {return a*b;};

    thrust::transform(thrust::cuda::par,
            d_a.begin(), d_a.end(),
            d_b.begin(),
            d_out.begin(), fm);


    // Transfer data back to host memory
    thrust::copy(d_out.cbegin(), d_out.cend(), out.begin());

    // profiling for CPU
    auto s = std::chrono::high_resolution_clock::now();

    std::transform(a.begin(), a.end(),
                      d_b.begin(),
                      d_out.begin(), std::multiplies<float>());

    auto d = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s).count();
    std::cout << d << " ms CPU" << std::endl;

    return 0;
}
