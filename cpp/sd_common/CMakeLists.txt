project(libsd_common)

set(SDCommon_SRC ConfigParser.cpp Frame.cpp Region.cpp FrameResult.cpp Log.cpp LogHelper.cpp SHA256.c)

use_mpi_compiler()
add_library(SD_Common STATIC ${SDCommon_SRC})
