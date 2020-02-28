cmake_minimum_required(VERSION 3.1)

project(cvrtsp)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror")



if(BUILD_SHARED_LIBS)

    find_package(OpenCV REQUIRED PATHS /usr/local/opencv-cpu NO_DEFAULT_PATH)
    include_directories(${OpenCV_INCLUDE_DIRS})

else(BUILD_SHARED_LIBS)

    find_package(OpenCV REQUIRED PATHS /usr/local/opencv-cpu-static NO_DEFAULT_PATH)
    include_directories(${OpenCV_INCLUDE_DIRS})


    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    SET(CMAKE_EXE_LINKER_FLAGS "-static")


    #include_directories(/usr/local/opencv-cpu-static/include/opencv4)
    #link_directories(/usr/local/opencv-cpu-static/lib/)
    #target_link_libraries(${PROJECT_NAME} /usr/local/opencv-cpu-static/lib/libopencv_imgcodecs.a -static)
    #target_link_libraries(${PROJECT_NAME} /usr/local/opencv-cpu-static/lib/libopencv_imgproc.a -static)
    #target_link_libraries(${PROJECT_NAME} /usr/local/opencv-cpu-static/lib/libopencv_video.a -static)
    #target_link_libraries(${PROJECT_NAME} /usr/local/opencv-cpu-static/lib/libopencv_videoio.a -static)
    #target_link_libraries(${PROJECT_NAME} /usr/local/opencv-cpu-static/lib/libopencv_highgui.a -static)
    #target_link_libraries(${PROJECT_NAME} /usr/local/opencv-cpu-static/lib/libopencv_core.a -static) # this should be the last one

    #target_link_libraries(${PROJECT_NAME} webp)
    #target_link_libraries(${PROJECT_NAME} dl)
    #target_link_libraries(${PROJECT_NAME} z)
    #target_link_libraries(${PROJECT_NAME} jpeg)
    #target_link_libraries(${PROJECT_NAME} png)



    #target_link_libraries(${PROJECT_NAME} ${GKT_LIBRARIES})

    #target_link_libraries(${PROJECT_NAME} gtk+3)

    #target_link_libraries(${PROJECT_NAME} avcodec)
    #target_link_libraries(${PROJECT_NAME} avutil)

    #include_directories(/usr/local/opencv-cpu/include/opencv4)
    ##link_directories(/usr/local/opencv-cpu/lib)


    #find_package(PkgConfig REQUIRED)
    #pkg_check_modules(GTK REQUIRED gtk+-3.0)
endif(BUILD_SHARED_LIBS)

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
#message(STATUS "    libraries: ${OpenCV_LIBS}")
#message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

add_executable(${PROJECT_NAME} "main.cpp")

# Common libraries
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

if(BUILD_STATIC_LIBS)
    target_link_libraries(${PROJECT_NAME} )
endif(BUILD_STATIC_LIBS)

