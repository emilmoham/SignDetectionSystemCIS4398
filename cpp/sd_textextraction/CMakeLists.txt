project(SD_TextExtraction)

include_directories(../sd_common ${OpenCV_INCLUDE_DIRS} ${Tesseract_INCLUDE_DIRS})

use_std_compiler()
set(TextExtraction_SRC TextExtractor.cpp TextExtractor.h)
add_library(SD_TextExtraction STATIC ${TextExtraction_SRC})
