cmake_minimum_required(VERSION 3.29)
project(openCV4Study)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

add_executable(openCV4Study ch00_start/main.cpp)
target_link_libraries(openCV4Study ${OpenCV_LIBS})