#include "gpubase.cuh"

#include <iostream>
#include <iterator>
#include <chrono>
#include <vector>

#include <thrust/version.h>
#include <thrust/device_vector.h>

#include "cpubase.hpp"


typedef unsigned long nid_t;


void print(const std::vector<nid_t>& v) {
    copy(v.cbegin(), v.cend(), std::ostream_iterator<nid_t>(std::cout, " "));
    std::cout << std::endl;
}

int main(void) {

    std::cout << "Thrust v" <<  THRUST_MAJOR_VERSION << "." << THRUST_MINOR_VERSION << std::endl;

    size_t n = size_t(1e8); // or vec1.max_size();

    std::vector<nid_t> vec1;
    rand(vec1, n);

    auto print_time = [](const std::string& name, const std::chrono::system_clock::time_point& s) {
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s).count();
        std::cout << dur << "\t" << name << std::endl;
    };

	std::vector<nid_t> res = vec1;

	auto s = std::chrono::high_resolution_clock::now();

	sort(pol_par_unseq, res);
	print_time("cpu sort", s);


    thrust::device_vector<nid_t> vec1d;
	s = std::chrono::high_resolution_clock::now();
	read(vec1, vec1d);
	print_time("copy to device", s);



	s = std::chrono::high_resolution_clock::now();
	gpu_sort(vec1d);
    print_time("gpu sort", s);
    std::vector<nid_t> resd(vec1.size());



    s = std::chrono::high_resolution_clock::now();
    write(vec1d, resd);
    print_time("copy back to host", s);




    std::cout << "Validating result ...";

    if(res == resd) {
        std::cout << "\b\b\bPASS" << std::endl;
    } else {
        std::cout << "\b\b\bFAILED" << std::endl;
    }


    return 0;

}