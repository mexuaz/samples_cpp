//
// Created by am on 10/18/19.
//

#ifndef THRUST_SIMPLE_2_PCOM_H
#define THRUST_SIMPLE_2_PCOM_H

#include <iostream>
#include <string>
#include <vector>

#if USE_CUDA
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#endif

typedef unsigned long nid_t;


enum Policy_t {
    pol_seq = 0,
    pol_par,
    pol_par_unseq,
    pol_unseq,
    pol_thrust_par
};

inline std::string to_string(Policy_t pol) {
    switch (pol) {
        case pol_seq:
            return "sequential";
        case pol_par:
            return "parallel";
        case pol_par_unseq:
            return "parallel-unsequential";
        case pol_unseq:
            return "unsequential";
        case pol_thrust_par:
            return "thrust-par";
    }
    throw std::runtime_error("Unknown policy!");
}



#if USE_CUDA
#define vec thrust::device_vector
#define FOR_EACH thrust::for_each
#define SORT thrust::sort
#else
#define vec std::vector // host vector
#define FOR_EACH std::for_each
#define SORT std::sort
#endif


void sort(Policy_t pol, vec<nid_t> &v);


#endif //THRUST_SIMPLE_2_PCOM_H
