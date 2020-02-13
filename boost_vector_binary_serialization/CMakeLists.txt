cmake_minimum_required(VERSION 3.15)
project(boost_serialization_sample)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.67.0  REQUIRED COMPONENTS system serialization)


add_executable(${PROJECT_NAME} boost_vector_binary_serialization.cpp)
target_link_libraries( ${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES} )
