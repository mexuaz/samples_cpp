cmake_minimum_required(VERSION 3.15)
project(bsv_h5)

set(CMAKE_CXX_STANDARD 17)

find_package(HDF5 REQUIRED COMPONENTS C CXX)

include_directories(${HDF5_INCLUDE_DIR})

add_executable(${PROJECT_NAME} binary_serialization_vectors_hdf5.cpp)
target_link_libraries( ${PROJECT_NAME} PUBLIC  ${HDF5_CXX_LIBRARIES} ${HDF5_LIBRARIES})
