cmake_minimum_required(VERSION 2.8.12)

project(main)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(main main.cpp contour.cpp ../sd_render/render.cpp ../sd_shapedetection/shapedetection.cpp)
target_link_libraries(main ${OpenCV_LIBS})
