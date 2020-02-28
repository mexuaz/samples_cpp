cmake_minimum_required(VERSION 3.12 FATAL_ERROR)



option(WITH_CUDA "Compiles the code with nvcc" OFF) #OFF by default
if(WITH_CUDA)

	MESSAGE(STATUS "Compiling with cuda status")
	add_definitions(-DUSE_CUDA)
	project(thrust_test LANGUAGES CXX CUDA)

	if(NOT DEFINED CMAKE_CUDA_STANDARD)
		set(CMAKE_CUDA_STANDARD 14)
		set(CMAKE_CUDA_STANDARD_REQUIRED ON)
	endif()

	# Enable using lambda function
	set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; --expt-extended-lambda;)



	file(GLOB CU_SOURCES ${PROJECT_SOURCE_DIR}/foo.cu)

	add_library(CudaMain SHARED ${CU_SOURCES})



	#file(GLOB CPP_SOURCES ${PROJECT_SOURCE_DIR}/foo.cpp)

	#add_library(CppMain SHARED ${CPP_SOURCES})

	#target_link_libraries(CudaMain PUBLIC CppMain)



	add_executable(${PROJECT_NAME} main.cpp)
	target_link_libraries(${PROJECT_NAME} PUBLIC CudaMain)

	# string(APPEND CMAKE_CUDA_FLAGS " -gencode arch=compute_30,code=compute_30")

else(WITH_CUDA)

endif(WITH_CUDA)

if(NOT DEFINED CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
















#[[
# force nvcc to accept *.cpp as *.cu
set_source_files_properties(
		${SOURCES}
		PROPERTIES
		CUDA_SOURCE_PROPERTY_FORMAT
		OBJ)

set_target_properties(CudaFoo PROPERTIES POSITION_INDEPENDENT_CODE ON)
]]

#set_target_properties(CudaFoo PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

#target_link_libraries(${PROJECT_NAME} PUBLIC CudaMain)

#https://devblogs.nvidia.com/separate-compilation-linking-cuda-device-code/

# https://github.com/Kitware/CMake/tree/master/Tests/Cuda/Complex

#[[
set(CMAKE_CXX_STANDARD 17)

#------------------------------Generic flags
set(CMAKE_CXX_FLAGS					"-Wall -Wextra -Werror")

set(CMAKE_CXX_FLAGS_DEBUG			"-O0 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL		"-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE			"-O4 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO	"-O2 -g")
]]

#-DCMAKE_CXX_COMPILER=g++-8
# ------------------------------Force release build type if not defined

#[[
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING
			"Choose the type of build, options are: Debug Release
RelWithDebInfo MinSizeRel."
			FORCE)
endif(NOT CMAKE_BUILD_TYPE)
]]


# ------ Cuda
#find_package(CUDA 10.0 REQUIRED)
#message(STATUS "Found CUDA ${CUDA_VERSION_STRING} at ${CUDA_TOOLKIT_ROOT_DIR}")
#set(CUDA_LINK_LIBRARIES_KEYWORD PUBLIC)

#include_directories(${CUDA_INCLUDE_DIRS})
#link_directories(${CUDA_LIBRARY_DIRS})




#set(CUDA_SEPARABLE_COMPILATION ON)
#set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} ${CUDA_ARCH} -g -G)
#cuda_select_nvcc_arch_flags(ARCH_FLAGS) # optional argument for arch to add
# Pass options to NVCC
#set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; -O3 -gencode arch=compute_22,code=sm_22)



# ------ OpenMP support required
#[[
find_package(OpenMP REQUIRED)
include_directories(${OPENMP_INCLUDE_DIRS})
link_directories(${OPENMP_LIBRARY_DIRS})
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")


set_source_files_properties(
		main.cpp
		PROPERTIES
		CUDA_SOURCE_PROPERTY_FORMAT
		OBJ)

]]
#add_executable(${PROJECT_NAME} ${SOURCES})


#target_link_libraries(${PROJECT_NAME} PUBLIC CudaFoo)
