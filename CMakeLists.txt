cmake_minimum_required(VERSION 3.26)
project(openCV4Study)
set(CUDA_DIR "/usr/local/cuda")
set(OpenCV_DIR "/usr/local/lib/cmake/opencv4")

set(CMAKE_PREFIX_PATH "${CUDA_DIR}/lib64/cmake/cuda" "${OpenCV_DIR}")
find_package(CUDAToolkit)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

add_executable(openCV4Study ch15/svmdigits/main.cpp)
target_link_libraries(openCV4Study ${OpenCV_LIBS})