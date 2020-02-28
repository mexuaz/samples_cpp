#ifndef THRUST_TEST_GPUBASE_HPP
#define THRUST_TEST_GPUBASE_HPP

#include "pcom.h"

void read(const std::vector<nid_t>& v_host, thrust::device_vector<nid_t>& v_dev);
void write(const thrust::device_vector<nid_t>& v_dev, std::vector<nid_t>& v_host);


#endif //THRUST_TEST_GPUBASE_HPP
