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
CMAKE_SOURCE_DIR = /home/ben/SignDetectionSystemCIS4398/cpp/sd_contour

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/main.cpp.o -c /home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/main.cpp

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/main.cpp > CMakeFiles/main.dir/main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/main.cpp -o CMakeFiles/main.dir/main.cpp.s

CMakeFiles/main.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/main.dir/main.cpp.o.requires

CMakeFiles/main.dir/main.cpp.o.provides: CMakeFiles/main.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/main.dir/main.cpp.o.provides

CMakeFiles/main.dir/main.cpp.o.provides.build: CMakeFiles/main.dir/main.cpp.o


CMakeFiles/main.dir/contour.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/contour.cpp.o: ../contour.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/contour.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/contour.cpp.o -c /home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/contour.cpp

CMakeFiles/main.dir/contour.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/contour.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/contour.cpp > CMakeFiles/main.dir/contour.cpp.i

CMakeFiles/main.dir/contour.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/contour.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/contour.cpp -o CMakeFiles/main.dir/contour.cpp.s

CMakeFiles/main.dir/contour.cpp.o.requires:

.PHONY : CMakeFiles/main.dir/contour.cpp.o.requires

CMakeFiles/main.dir/contour.cpp.o.provides: CMakeFiles/main.dir/contour.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/contour.cpp.o.provides.build
.PHONY : CMakeFiles/main.dir/contour.cpp.o.provides

CMakeFiles/main.dir/contour.cpp.o.provides.build: CMakeFiles/main.dir/contour.cpp.o


CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.o: /home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.o -c /home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp

CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp > CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.i

CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp -o CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.s

CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.o.requires:

.PHONY : CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.o.requires

CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.o.provides: CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.o.provides.build
.PHONY : CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.o.provides

CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.o.provides.build: CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.o


CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.o: /home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.o -c /home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp

CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp > CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.i

CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp -o CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.s

CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.o.requires:

.PHONY : CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.o.requires

CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.o.provides: CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.o.provides.build
.PHONY : CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.o.provides

CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.o.provides.build: CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.o


# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o" \
"CMakeFiles/main.dir/contour.cpp.o" \
"CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.o" \
"CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/main.cpp.o
main: CMakeFiles/main.dir/contour.cpp.o
main: CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.o
main: CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.o
main: CMakeFiles/main.dir/build.make
main: /usr/local/lib/libopencv_dnn.so.3.3.0
main: /usr/local/lib/libopencv_ml.so.3.3.0
main: /usr/local/lib/libopencv_objdetect.so.3.3.0
main: /usr/local/lib/libopencv_shape.so.3.3.0
main: /usr/local/lib/libopencv_stitching.so.3.3.0
main: /usr/local/lib/libopencv_superres.so.3.3.0
main: /usr/local/lib/libopencv_videostab.so.3.3.0
main: /usr/local/lib/libopencv_viz.so.3.3.0
main: /usr/local/lib/libopencv_calib3d.so.3.3.0
main: /usr/local/lib/libopencv_features2d.so.3.3.0
main: /usr/local/lib/libopencv_flann.so.3.3.0
main: /usr/local/lib/libopencv_highgui.so.3.3.0
main: /usr/local/lib/libopencv_photo.so.3.3.0
main: /usr/local/lib/libopencv_video.so.3.3.0
main: /usr/local/lib/libopencv_videoio.so.3.3.0
main: /usr/local/lib/libopencv_imgcodecs.so.3.3.0
main: /usr/local/lib/libopencv_imgproc.so.3.3.0
main: /usr/local/lib/libopencv_core.so.3.3.0
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/requires: CMakeFiles/main.dir/main.cpp.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/contour.cpp.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_render/render.cpp.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/home/ben/SignDetectionSystemCIS4398/cpp/sd_shapedetection/shapedetection.cpp.o.requires

.PHONY : CMakeFiles/main.dir/requires

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ben/SignDetectionSystemCIS4398/cpp/sd_contour /home/ben/SignDetectionSystemCIS4398/cpp/sd_contour /home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/build /home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/build /home/ben/SignDetectionSystemCIS4398/cpp/sd_contour/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

