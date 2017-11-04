cmake_minimum_required(VERSION 2.8.12)

project(frame_demo)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(frame_demo main.cpp read_from_camera.cpp open_image.cpp read_from_video.cpp)
target_link_libraries(frame_demo ${OpenCV_LIBS})
