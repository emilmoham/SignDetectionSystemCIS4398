project(libsd_common)

set(SDCommon_SRC Frame.cpp Region.cpp SHA256.c)

use_mpi_compiler()
add_library(SD_Common STATIC ${SDCommon_SRC})
