project(SignDetection)

add_subdirectory(sd_common)
add_subdirectory(sd_textextraction)

set(SignDetection_SRC Master.cpp SysInfo.cpp main.cpp)

use_mpi_compiler()
include_directories(sd_common sd_textextraction ${OpenCV_INCLUDE_DIRS} ${Tesseract_INCLUDE_DIRS})
add_executable(SignDetection ${SignDetection_SRC})
target_link_libraries(SignDetection SD_Common SD_TextExtraction ${OpenCV_LIBS} ${Leptonica_LIBRARY} ${Tesseract_LIBRARY} Threads::Threads)
