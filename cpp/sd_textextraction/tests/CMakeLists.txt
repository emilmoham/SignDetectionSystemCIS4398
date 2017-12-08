project(TextExtraction)

cmake_minimum_required(VERSION 2.8.12)

find_package(OpenCV REQUIRED)

set(Tesseract_INCLUDE_DIRS /usr/include/tesseract /usr/include/leptonica)
find_library(Leptonica_LIBRARY lept HINTS /usr/lib64 /usr/lib)
find_library(Tesseract_LIBRARY tesseract HINTS /usr/lib64 /usr/lib)

include_directories(${OpenCV_INCLUDE_DIRS} ${Tesseract_INCLUDE_DIRS})

add_executable(TextExtraction-Test text-test.cpp)

target_link_libraries(TextExtraction-Test ${OpenCV_LIBS} ${Leptonica_LIBRARY} ${Tesseract_LIBRARY})
