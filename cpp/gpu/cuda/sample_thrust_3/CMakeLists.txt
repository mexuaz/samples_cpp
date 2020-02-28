cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

option(WITH_CUDA "Compiles the code with nvcc" OFF) #OFF by default

if(WITH_CUDA)
	MESSAGE(STATUS "Compiling with cuda status")
	add_definitions(-DUSE_CUDA)

	project(thrust_simple_2 LANGUAGES CXX CUDA)
	# string(APPEND CMAKE_CUDA_FLAGS " -gencode arch=compute_30,code=compute_30")

	if(NOT DEFINED CMAKE_CUDA_STANDARD)
		set(CMAKE_CUDA_STANDARD 14)
		set(CMAKE_CUDA_STANDARD_REQUIRED ON)
	endif()

	if(NOT DEFINED CMAKE_CXX_STANDARD)
		set(CMAKE_CXX_STANDARD 17)
		set(CMAKE_CXX_STANDARD_REQUIRED ON)
	endif()

	# Enable using lambda function
	set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; --expt-extended-lambda;)

	file(GLOB CPP_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
	add_library(CppBase SHARED ${CPP_SOURCES})
	target_link_libraries(CppBase tbb)

	file(GLOB CU_SOURCES ${PROJECT_SOURCE_DIR}/*.cu)
	list(REMOVE_ITEM ${CU_SOURCES} main.cu) # exclude main.cu
	add_library(CuBase SHARED ${CU_SOURCES})


	file(GLOB APP_SOURCES ${PROJECT_SOURCE_DIR}/main.cu)

	add_executable(${PROJECT_NAME} ${APP_SOURCES})
	set_target_properties(${PROJECT_NAME} PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
	target_link_libraries(${PROJECT_NAME} PUBLIC CppBase)
	target_link_libraries(${PROJECT_NAME} PUBLIC CuBase)

else(WITH_CUDA)

	project(thrust_simple_2 LANGUAGES CXX)


	if(NOT DEFINED CMAKE_CXX_STANDARD)
		set(CMAKE_CXX_STANDARD 17)
		set(CMAKE_CXX_STANDARD_REQUIRED ON)
	endif()

	file(GLOB CPP_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
	add_library(CppBase SHARED ${CPP_SOURCES})
	target_link_libraries(CppBase tbb)

	add_executable(${PROJECT_NAME} ${APP_SOURCES})
	target_link_libraries(${PROJECT_NAME} PUBLIC CppBase)

	file(GLOB APP_SOURCES ${PROJECT_SOURCE_DIR}/main.cu)
	add_executable(${PROJECT_NAME} ${APP_SOURCES})

endif(WITH_CUDA)
unset(WITH_CUDA CACHE) # <---- this is the important!! earse the option form cache















#https://devblogs.nvidia.com/separate-compilation-linking-cuda-device-code/

# https://github.com/Kitware/CMake/tree/master/Tests/Cuda/Complex

