cmake_minimum_required(VERSION 2.8.12)

project(textsample)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(textsample textsample.cpp)
target_link_libraries(textsample ${OpenCV_LIBS})
