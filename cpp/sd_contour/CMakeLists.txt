cmake_minimum_required(VERSION 2.8.12)

project(contourdrawing)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# This directive is useful when there is only one file in the directory with an "int main() { ... }"
# file( GLOB Contour_SRCS *.cpp *.h )
set(Countour_SRC contour.cpp contour.h)

add_executable(contourdrawing contourdrawing.cpp ${Contour_SRC})
target_link_libraries(contourdrawing ${OpenCV_LIBS})



project(main)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(main main.cpp contour.cpp ../sd_render/render.cpp ../sd_shapedetection/shapedetection.cpp)

target_link_libraries(main ${OpenCV_LIBS})
