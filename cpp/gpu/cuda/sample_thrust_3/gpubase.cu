#include "gpubase.cuh"

#include <stdexcept> // runtime_error
#include <thrust/sort.h>

using namespace thrust;

template<class F>
auto execute(F f, Policy_t p) {
    switch (p) {
        case pol_thrust_par:
            return f(thrust::cuda::par);
        default:
            throw std::runtime_error("Policy not supported!");
    }
}

void read(const std::vector<nid_t>& v_host, device_vector<nid_t>& v_dev) {
    v_dev = v_host;
}

void write(const device_vector<nid_t>& v_dev, std::vector<nid_t>& v_host) {
    v_host.resize(v_dev.size());
    thrust::copy(v_dev.cbegin(), v_dev.cend(), v_host.begin());
}

void sort(Policy_t pol, vec<nid_t>& v) {
    execute(
            [&](auto &pol) {
                return sort(pol, v.begin(), v.end());
            }, pol);
}

