cmake_minimum_required(VERSION 3.15)
project(proto3_serialization_sample)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf 3.6.1 REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS proto/vectors.proto)

add_executable(${PROJECT_NAME} ${PROTO_SRCS} ${PROTO_HDRS} proto3_vector_serialization.cpp)
target_link_libraries(${PROJECT_NAME} protobuf)

