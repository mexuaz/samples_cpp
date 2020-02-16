cmake_minimum_required(VERSION 3.15)
project(bsv_flatbuffers)

set(CMAKE_CXX_STANDARD 17)

#--------------------------------Include all source files and Flatbuffers sources
file(GLOB SOURCES
		${PROJECT_SOURCE_DIR}/*.cpp
		${PROJECT_SOURCE_DIR}/fb/flatbuffers/*.cpp)

include_directories(${PROJECT_SOURCE_DIR}/fb)

add_executable(${PROJECT_NAME} ${SOURCES})

