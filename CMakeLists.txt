cmake_minimum_required(VERSION 2.8.12)

find_package(OpenCV REQUIRED)
find_package(MPI REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CURRENT_COMPILER "STD")

macro(use_std_compiler)
  if (${CURRENT_COMPILER) STREQUAL "MPI")
    # Change compiler
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")
    set(CURRENT_COMPILER "STD")
  endif()
endmacro()

macro(use_mpi_compiler)
  if (${CURRENT_COMPILER) STREQUAL "STD")
    # Change compiler
    set(CMAKE_C_COMPILER "mpicc")
    set(CMAKE_CXX_COMPILER "mpiCC")
    set(CURRENT_COMPILER "MPI")
  endif()
endmacro()


add_subdirectory(cpp)
