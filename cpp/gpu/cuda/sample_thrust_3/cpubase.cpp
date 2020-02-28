#include "cpubase.hpp"

#include <random>
#include <algorithm>

#if __cplusplus >= 201703L
#include <execution>
#endif

using namespace std;

template<class F>
auto execute(F f, Policy_t p) {
    switch (p) {
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
    }
}

void rand(std::vector<nid_t> &v, size_t n, size_t min /*= 0*/, size_t max /*= 10000*/) {
    static std::mt19937 eng{std::random_device()()};
    v.resize(n);
    std::generate(v.begin(), v.end(), [&]() {
        return std::uniform_int_distribution<nid_t>{min, max}(eng);
    });
}

void sort(Policy_t pol, vec<nid_t> &v) {
    execute(
            [&](auto &pol) {
                return sort(pol, v.begin(), v.end());
            }, pol);
}

