cmake_minimum_required(VERSION 2.8.12)

project(detect_triangles)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(detect_triangles detect_triangles.cpp)
target_link_libraries(detect_triangles ${OpenCV_LIBS})
