# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ben/SignDetectionSystemCIS4398

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ben/SignDetectionSystemCIS4398/build

# Include any dependencies generated for this target.
include CMakeFiles/contourdrawing.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/contourdrawing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/contourdrawing.dir/flags.make

CMakeFiles/contourdrawing.dir/contourdrawing.cpp.o: CMakeFiles/contourdrawing.dir/flags.make
CMakeFiles/contourdrawing.dir/contourdrawing.cpp.o: ../contourdrawing.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ben/SignDetectionSystemCIS4398/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/contourdrawing.dir/contourdrawing.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/contourdrawing.dir/contourdrawing.cpp.o -c /home/ben/SignDetectionSystemCIS4398/contourdrawing.cpp

CMakeFiles/contourdrawing.dir/contourdrawing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/contourdrawing.dir/contourdrawing.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ben/SignDetectionSystemCIS4398/contourdrawing.cpp > CMakeFiles/contourdrawing.dir/contourdrawing.cpp.i

CMakeFiles/contourdrawing.dir/contourdrawing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/contourdrawing.dir/contourdrawing.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ben/SignDetectionSystemCIS4398/contourdrawing.cpp -o CMakeFiles/contourdrawing.dir/contourdrawing.cpp.s

CMakeFiles/contourdrawing.dir/contourdrawing.cpp.o.requires:

.PHONY : CMakeFiles/contourdrawing.dir/contourdrawing.cpp.o.requires

CMakeFiles/contourdrawing.dir/contourdrawing.cpp.o.provides: CMakeFiles/contourdrawing.dir/contourdrawing.cpp.o.requires
	$(MAKE) -f CMakeFiles/contourdrawing.dir/build.make CMakeFiles/contourdrawing.dir/contourdrawing.cpp.o.provides.build
.PHONY : CMakeFiles/contourdrawing.dir/contourdrawing.cpp.o.provides

CMakeFiles/contourdrawing.dir/contourdrawing.cpp.o.provides.build: CMakeFiles/contourdrawing.dir/contourdrawing.cpp.o


# Object files for target contourdrawing
contourdrawing_OBJECTS = \
"CMakeFiles/contourdrawing.dir/contourdrawing.cpp.o"

# External object files for target contourdrawing
contourdrawing_EXTERNAL_OBJECTS =

contourdrawing: CMakeFiles/contourdrawing.dir/contourdrawing.cpp.o
contourdrawing: CMakeFiles/contourdrawing.dir/build.make
contourdrawing: /usr/local/lib/libopencv_dnn.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_ml.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_objdetect.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_shape.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_stitching.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_superres.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_videostab.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_viz.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_calib3d.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_features2d.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_flann.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_highgui.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_photo.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_video.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_videoio.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_imgcodecs.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_imgproc.so.3.3.0
contourdrawing: /usr/local/lib/libopencv_core.so.3.3.0
contourdrawing: CMakeFiles/contourdrawing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ben/SignDetectionSystemCIS4398/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable contourdrawing"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/contourdrawing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/contourdrawing.dir/build: contourdrawing

.PHONY : CMakeFiles/contourdrawing.dir/build

CMakeFiles/contourdrawing.dir/requires: CMakeFiles/contourdrawing.dir/contourdrawing.cpp.o.requires

.PHONY : CMakeFiles/contourdrawing.dir/requires

CMakeFiles/contourdrawing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/contourdrawing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/contourdrawing.dir/clean

CMakeFiles/contourdrawing.dir/depend:
	cd /home/ben/SignDetectionSystemCIS4398/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ben/SignDetectionSystemCIS4398 /home/ben/SignDetectionSystemCIS4398 /home/ben/SignDetectionSystemCIS4398/build /home/ben/SignDetectionSystemCIS4398/build /home/ben/SignDetectionSystemCIS4398/build/CMakeFiles/contourdrawing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/contourdrawing.dir/depend

