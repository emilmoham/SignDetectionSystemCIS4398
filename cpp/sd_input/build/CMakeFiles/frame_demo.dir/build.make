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
CMAKE_SOURCE_DIR = /home/ben/SignDetectionSystemCIS4398/cpp/sd_input

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/build

# Include any dependencies generated for this target.
include CMakeFiles/frame_demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/frame_demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/frame_demo.dir/flags.make

CMakeFiles/frame_demo.dir/main.cpp.o: CMakeFiles/frame_demo.dir/flags.make
CMakeFiles/frame_demo.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ben/SignDetectionSystemCIS4398/cpp/sd_input/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/frame_demo.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/frame_demo.dir/main.cpp.o -c /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/main.cpp

CMakeFiles/frame_demo.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/frame_demo.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/main.cpp > CMakeFiles/frame_demo.dir/main.cpp.i

CMakeFiles/frame_demo.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/frame_demo.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/main.cpp -o CMakeFiles/frame_demo.dir/main.cpp.s

CMakeFiles/frame_demo.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/frame_demo.dir/main.cpp.o.requires

CMakeFiles/frame_demo.dir/main.cpp.o.provides: CMakeFiles/frame_demo.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/frame_demo.dir/build.make CMakeFiles/frame_demo.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/frame_demo.dir/main.cpp.o.provides

CMakeFiles/frame_demo.dir/main.cpp.o.provides.build: CMakeFiles/frame_demo.dir/main.cpp.o


CMakeFiles/frame_demo.dir/read_from_camera.cpp.o: CMakeFiles/frame_demo.dir/flags.make
CMakeFiles/frame_demo.dir/read_from_camera.cpp.o: ../read_from_camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ben/SignDetectionSystemCIS4398/cpp/sd_input/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/frame_demo.dir/read_from_camera.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/frame_demo.dir/read_from_camera.cpp.o -c /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/read_from_camera.cpp

CMakeFiles/frame_demo.dir/read_from_camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/frame_demo.dir/read_from_camera.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/read_from_camera.cpp > CMakeFiles/frame_demo.dir/read_from_camera.cpp.i

CMakeFiles/frame_demo.dir/read_from_camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/frame_demo.dir/read_from_camera.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/read_from_camera.cpp -o CMakeFiles/frame_demo.dir/read_from_camera.cpp.s

CMakeFiles/frame_demo.dir/read_from_camera.cpp.o.requires:

.PHONY : CMakeFiles/frame_demo.dir/read_from_camera.cpp.o.requires

CMakeFiles/frame_demo.dir/read_from_camera.cpp.o.provides: CMakeFiles/frame_demo.dir/read_from_camera.cpp.o.requires
	$(MAKE) -f CMakeFiles/frame_demo.dir/build.make CMakeFiles/frame_demo.dir/read_from_camera.cpp.o.provides.build
.PHONY : CMakeFiles/frame_demo.dir/read_from_camera.cpp.o.provides

CMakeFiles/frame_demo.dir/read_from_camera.cpp.o.provides.build: CMakeFiles/frame_demo.dir/read_from_camera.cpp.o


CMakeFiles/frame_demo.dir/open_image.cpp.o: CMakeFiles/frame_demo.dir/flags.make
CMakeFiles/frame_demo.dir/open_image.cpp.o: ../open_image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ben/SignDetectionSystemCIS4398/cpp/sd_input/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/frame_demo.dir/open_image.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/frame_demo.dir/open_image.cpp.o -c /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/open_image.cpp

CMakeFiles/frame_demo.dir/open_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/frame_demo.dir/open_image.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/open_image.cpp > CMakeFiles/frame_demo.dir/open_image.cpp.i

CMakeFiles/frame_demo.dir/open_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/frame_demo.dir/open_image.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/open_image.cpp -o CMakeFiles/frame_demo.dir/open_image.cpp.s

CMakeFiles/frame_demo.dir/open_image.cpp.o.requires:

.PHONY : CMakeFiles/frame_demo.dir/open_image.cpp.o.requires

CMakeFiles/frame_demo.dir/open_image.cpp.o.provides: CMakeFiles/frame_demo.dir/open_image.cpp.o.requires
	$(MAKE) -f CMakeFiles/frame_demo.dir/build.make CMakeFiles/frame_demo.dir/open_image.cpp.o.provides.build
.PHONY : CMakeFiles/frame_demo.dir/open_image.cpp.o.provides

CMakeFiles/frame_demo.dir/open_image.cpp.o.provides.build: CMakeFiles/frame_demo.dir/open_image.cpp.o


CMakeFiles/frame_demo.dir/read_from_video.cpp.o: CMakeFiles/frame_demo.dir/flags.make
CMakeFiles/frame_demo.dir/read_from_video.cpp.o: ../read_from_video.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ben/SignDetectionSystemCIS4398/cpp/sd_input/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/frame_demo.dir/read_from_video.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/frame_demo.dir/read_from_video.cpp.o -c /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/read_from_video.cpp

CMakeFiles/frame_demo.dir/read_from_video.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/frame_demo.dir/read_from_video.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/read_from_video.cpp > CMakeFiles/frame_demo.dir/read_from_video.cpp.i

CMakeFiles/frame_demo.dir/read_from_video.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/frame_demo.dir/read_from_video.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/read_from_video.cpp -o CMakeFiles/frame_demo.dir/read_from_video.cpp.s

CMakeFiles/frame_demo.dir/read_from_video.cpp.o.requires:

.PHONY : CMakeFiles/frame_demo.dir/read_from_video.cpp.o.requires

CMakeFiles/frame_demo.dir/read_from_video.cpp.o.provides: CMakeFiles/frame_demo.dir/read_from_video.cpp.o.requires
	$(MAKE) -f CMakeFiles/frame_demo.dir/build.make CMakeFiles/frame_demo.dir/read_from_video.cpp.o.provides.build
.PHONY : CMakeFiles/frame_demo.dir/read_from_video.cpp.o.provides

CMakeFiles/frame_demo.dir/read_from_video.cpp.o.provides.build: CMakeFiles/frame_demo.dir/read_from_video.cpp.o


# Object files for target frame_demo
frame_demo_OBJECTS = \
"CMakeFiles/frame_demo.dir/main.cpp.o" \
"CMakeFiles/frame_demo.dir/read_from_camera.cpp.o" \
"CMakeFiles/frame_demo.dir/open_image.cpp.o" \
"CMakeFiles/frame_demo.dir/read_from_video.cpp.o"

# External object files for target frame_demo
frame_demo_EXTERNAL_OBJECTS =

frame_demo: CMakeFiles/frame_demo.dir/main.cpp.o
frame_demo: CMakeFiles/frame_demo.dir/read_from_camera.cpp.o
frame_demo: CMakeFiles/frame_demo.dir/open_image.cpp.o
frame_demo: CMakeFiles/frame_demo.dir/read_from_video.cpp.o
frame_demo: CMakeFiles/frame_demo.dir/build.make
frame_demo: /usr/local/lib/libopencv_dnn.so.3.3.0
frame_demo: /usr/local/lib/libopencv_ml.so.3.3.0
frame_demo: /usr/local/lib/libopencv_objdetect.so.3.3.0
frame_demo: /usr/local/lib/libopencv_shape.so.3.3.0
frame_demo: /usr/local/lib/libopencv_stitching.so.3.3.0
frame_demo: /usr/local/lib/libopencv_superres.so.3.3.0
frame_demo: /usr/local/lib/libopencv_videostab.so.3.3.0
frame_demo: /usr/local/lib/libopencv_viz.so.3.3.0
frame_demo: /usr/local/lib/libopencv_calib3d.so.3.3.0
frame_demo: /usr/local/lib/libopencv_features2d.so.3.3.0
frame_demo: /usr/local/lib/libopencv_flann.so.3.3.0
frame_demo: /usr/local/lib/libopencv_highgui.so.3.3.0
frame_demo: /usr/local/lib/libopencv_photo.so.3.3.0
frame_demo: /usr/local/lib/libopencv_video.so.3.3.0
frame_demo: /usr/local/lib/libopencv_videoio.so.3.3.0
frame_demo: /usr/local/lib/libopencv_imgcodecs.so.3.3.0
frame_demo: /usr/local/lib/libopencv_imgproc.so.3.3.0
frame_demo: /usr/local/lib/libopencv_core.so.3.3.0
frame_demo: CMakeFiles/frame_demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ben/SignDetectionSystemCIS4398/cpp/sd_input/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable frame_demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/frame_demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/frame_demo.dir/build: frame_demo

.PHONY : CMakeFiles/frame_demo.dir/build

CMakeFiles/frame_demo.dir/requires: CMakeFiles/frame_demo.dir/main.cpp.o.requires
CMakeFiles/frame_demo.dir/requires: CMakeFiles/frame_demo.dir/read_from_camera.cpp.o.requires
CMakeFiles/frame_demo.dir/requires: CMakeFiles/frame_demo.dir/open_image.cpp.o.requires
CMakeFiles/frame_demo.dir/requires: CMakeFiles/frame_demo.dir/read_from_video.cpp.o.requires

.PHONY : CMakeFiles/frame_demo.dir/requires

CMakeFiles/frame_demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/frame_demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/frame_demo.dir/clean

CMakeFiles/frame_demo.dir/depend:
	cd /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ben/SignDetectionSystemCIS4398/cpp/sd_input /home/ben/SignDetectionSystemCIS4398/cpp/sd_input /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/build /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/build /home/ben/SignDetectionSystemCIS4398/cpp/sd_input/build/CMakeFiles/frame_demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/frame_demo.dir/depend

