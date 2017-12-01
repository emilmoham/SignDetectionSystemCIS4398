add_executable( objectDetection objectDetection.cpp )
target_link_libraries( objectDetection ${OpenCV_LIBS} )

add_executable( redDetection redDetection.cpp )
target_link_libraries( redDetection ${OpenCV_LIBS} )
