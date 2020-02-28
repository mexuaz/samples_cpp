#ifndef THRUST_TEST_FOO_HPP
#define THRUST_TEST_FOO_HPP

#if USE_CUDA
	#include <thrust/device_vector.h>
	#include <thrust/for_each.h>
	#include <thrust/execution_policy.h>
	#define __COMM__ __device__
#else
	#include <vector>
	#include <algorithm>
	#define __COMM__ __host__
#endif

typedef unsigned long nid_t; // node id type

enum Policy_t {
	pol_seq = 0,
	pol_par,
	pol_par_unseq,
	pol_unseq,
	pol_thrust_dev,
	pol_thrust_host
};

template<class F>
__device__
__host__
auto execute_(F f, Policy_t p) {
	switch (p) {
#if USE_CUDA
		case pol_thrust_dev:
			return f(thrust::device);
		//case pol_thrust_host:
			//return f(thrust::host);
		default:
			return f(thrust::device);
			//cudaErrorAssert("Policy not supported");
#else
		case pol_seq:
			return f(std::execution::seq);
		case pol_par:
			return f(std::execution::par);
		case pol_par_unseq:
			return f(std::execution::par_unseq);
		case pol_unseq:
			return f(std::execution::unseq);
		default:
			throw std::runtime_error("Policy not supported!");
#endif
	}
}


#if USE_CUDA
	#define vec thrust::device_vector
	#define FOR_EACH thrust::for_each
	#define SORT thrust::sort
#else
	#define vec std::vector
	#define FOR_EACH std::for_each
	#define SORT std::sort
#endif

template <typename T, typename U>
__device__
__host__
void assign(Policy_t pol, const vec<T> &src, const vec<U> &idx, vec<T> &dst) {
	assert(src.size() >= idx.size());
	execute_([&](auto &pol) {
				 return FOR_EACH(pol, idx.begin(), idx.end(), [&](const U &i) {
					 dst[i] = src[thrust::device_ptr<const T>(&i) - &idx[0]];
				 });
			 },
			 pol);
}



#endif //THRUST_TEST_FOO_HPP
