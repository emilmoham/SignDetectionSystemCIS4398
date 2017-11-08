project(SignDetection)

add_subdirectory(sd_common)

set(SignDetection_SRC Master.cpp main.cpp)

use_mpi_compiler()
add_executable(SignDetection ${SignDetection_SRC})
target_link_libraries(SignDetection SD_Common ${OpenCV_LIBS})
