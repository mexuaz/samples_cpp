# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/am/repos/samples/cpp/binary_serialization/binary_serialization_vectors_hdf5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/am/repos/samples/cpp/binary_serialization/build-binary_serialization_vectors_hdf5-Desktop_Qt_5_14_1_GCC_64bit-Debug

# Include any dependencies generated for this target.
include CMakeFiles/bsv_h5.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bsv_h5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bsv_h5.dir/flags.make

CMakeFiles/bsv_h5.dir/binary_serialization_vectors_hdf5.cpp.o: CMakeFiles/bsv_h5.dir/flags.make
CMakeFiles/bsv_h5.dir/binary_serialization_vectors_hdf5.cpp.o: /home/am/repos/samples/cpp/binary_serialization/binary_serialization_vectors_hdf5/binary_serialization_vectors_hdf5.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/am/repos/samples/cpp/binary_serialization/build-binary_serialization_vectors_hdf5-Desktop_Qt_5_14_1_GCC_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bsv_h5.dir/binary_serialization_vectors_hdf5.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bsv_h5.dir/binary_serialization_vectors_hdf5.cpp.o -c /home/am/repos/samples/cpp/binary_serialization/binary_serialization_vectors_hdf5/binary_serialization_vectors_hdf5.cpp

CMakeFiles/bsv_h5.dir/binary_serialization_vectors_hdf5.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bsv_h5.dir/binary_serialization_vectors_hdf5.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/am/repos/samples/cpp/binary_serialization/binary_serialization_vectors_hdf5/binary_serialization_vectors_hdf5.cpp > CMakeFiles/bsv_h5.dir/binary_serialization_vectors_hdf5.cpp.i

CMakeFiles/bsv_h5.dir/binary_serialization_vectors_hdf5.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bsv_h5.dir/binary_serialization_vectors_hdf5.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/am/repos/samples/cpp/binary_serialization/binary_serialization_vectors_hdf5/binary_serialization_vectors_hdf5.cpp -o CMakeFiles/bsv_h5.dir/binary_serialization_vectors_hdf5.cpp.s

# Object files for target bsv_h5
bsv_h5_OBJECTS = \
"CMakeFiles/bsv_h5.dir/binary_serialization_vectors_hdf5.cpp.o"

# External object files for target bsv_h5
bsv_h5_EXTERNAL_OBJECTS =

bsv_h5: CMakeFiles/bsv_h5.dir/binary_serialization_vectors_hdf5.cpp.o
bsv_h5: CMakeFiles/bsv_h5.dir/build.make
bsv_h5: /usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5_cpp.so
bsv_h5: /usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5.so
bsv_h5: /usr/lib/x86_64-linux-gnu/libpthread.so
bsv_h5: /usr/lib/x86_64-linux-gnu/libsz.so
bsv_h5: /usr/lib/x86_64-linux-gnu/libz.so
bsv_h5: /usr/lib/x86_64-linux-gnu/libdl.so
bsv_h5: /usr/lib/x86_64-linux-gnu/libm.so
bsv_h5: /usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5_cpp.so
bsv_h5: /usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5.so
bsv_h5: /usr/lib/x86_64-linux-gnu/libpthread.so
bsv_h5: /usr/lib/x86_64-linux-gnu/libsz.so
bsv_h5: /usr/lib/x86_64-linux-gnu/libz.so
bsv_h5: /usr/lib/x86_64-linux-gnu/libdl.so
bsv_h5: /usr/lib/x86_64-linux-gnu/libm.so
bsv_h5: CMakeFiles/bsv_h5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/am/repos/samples/cpp/binary_serialization/build-binary_serialization_vectors_hdf5-Desktop_Qt_5_14_1_GCC_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bsv_h5"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bsv_h5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bsv_h5.dir/build: bsv_h5

.PHONY : CMakeFiles/bsv_h5.dir/build

CMakeFiles/bsv_h5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bsv_h5.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bsv_h5.dir/clean

CMakeFiles/bsv_h5.dir/depend:
	cd /home/am/repos/samples/cpp/binary_serialization/build-binary_serialization_vectors_hdf5-Desktop_Qt_5_14_1_GCC_64bit-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/am/repos/samples/cpp/binary_serialization/binary_serialization_vectors_hdf5 /home/am/repos/samples/cpp/binary_serialization/binary_serialization_vectors_hdf5 /home/am/repos/samples/cpp/binary_serialization/build-binary_serialization_vectors_hdf5-Desktop_Qt_5_14_1_GCC_64bit-Debug /home/am/repos/samples/cpp/binary_serialization/build-binary_serialization_vectors_hdf5-Desktop_Qt_5_14_1_GCC_64bit-Debug /home/am/repos/samples/cpp/binary_serialization/build-binary_serialization_vectors_hdf5-Desktop_Qt_5_14_1_GCC_64bit-Debug/CMakeFiles/bsv_h5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bsv_h5.dir/depend
