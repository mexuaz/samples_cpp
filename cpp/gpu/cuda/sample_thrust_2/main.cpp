#include "foo.hpp"

#include <random>
#include <algorithm>


#if USE_CUDA
	#include <thrust/version.h>
#endif



int main(void) {

	size_t n = size_t(1e5); // or vec1.max_size();

	std::mt19937 eng{std::random_device()()};

	std::vector<nid_t> vec1, vec2;
	vec1.resize(n);
	std::generate(vec1.begin(), vec1.end(), [&eng]() {
		return std::uniform_int_distribution<long>{0, 100000}(eng);
	});


	vec2.resize(n);
	std::generate(vec2.begin(), vec2.end(), [&eng, &n]() {
		return std::uniform_int_distribution<size_t>{0, n}(eng);
	});

#if USE_CUDA
	std::cout << "Thrust v" <<  THRUST_MAJOR_VERSION << "." << THRUST_MINOR_VERSION << std::endl;
	thrust::device_vector<nid_t> vec1d = vec1, vec2d = vec2, vec3d;
	assign(pol_thrust_dev, vec1d, vec2d, vec3d);
#else
	std::vector<nid_t> vec3;
	assign(pol_par_unseq, vec1, vec2, vec3);
#endif


	return 0;

}