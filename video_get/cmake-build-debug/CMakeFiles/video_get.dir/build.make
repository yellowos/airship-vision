# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/yellowos/CLionProjects/video_get

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/yellowos/CLionProjects/video_get/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/video_get.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/video_get.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/video_get.dir/flags.make

CMakeFiles/video_get.dir/main.cpp.o: CMakeFiles/video_get.dir/flags.make
CMakeFiles/video_get.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yellowos/CLionProjects/video_get/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/video_get.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/video_get.dir/main.cpp.o -c /Users/yellowos/CLionProjects/video_get/main.cpp

CMakeFiles/video_get.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/video_get.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/yellowos/CLionProjects/video_get/main.cpp > CMakeFiles/video_get.dir/main.cpp.i

CMakeFiles/video_get.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/video_get.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/yellowos/CLionProjects/video_get/main.cpp -o CMakeFiles/video_get.dir/main.cpp.s

CMakeFiles/video_get.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/video_get.dir/main.cpp.o.requires

CMakeFiles/video_get.dir/main.cpp.o.provides: CMakeFiles/video_get.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/video_get.dir/build.make CMakeFiles/video_get.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/video_get.dir/main.cpp.o.provides

CMakeFiles/video_get.dir/main.cpp.o.provides.build: CMakeFiles/video_get.dir/main.cpp.o


# Object files for target video_get
video_get_OBJECTS = \
"CMakeFiles/video_get.dir/main.cpp.o"

# External object files for target video_get
video_get_EXTERNAL_OBJECTS =

video_get: CMakeFiles/video_get.dir/main.cpp.o
video_get: CMakeFiles/video_get.dir/build.make
video_get: /usr/local/lib/libopencv_videostab.3.3.0.dylib
video_get: /usr/local/lib/libopencv_ml.3.3.0.dylib
video_get: /usr/local/lib/libopencv_objdetect.3.3.0.dylib
video_get: /usr/local/lib/libopencv_video.3.3.0.dylib
video_get: /usr/local/lib/libopencv_photo.3.3.0.dylib
video_get: /usr/local/lib/libopencv_calib3d.3.3.0.dylib
video_get: /usr/local/lib/libopencv_features2d.3.3.0.dylib
video_get: /usr/local/lib/libopencv_highgui.3.3.0.dylib
video_get: /usr/local/lib/libopencv_videoio.3.3.0.dylib
video_get: /usr/local/lib/libopencv_imgcodecs.3.3.0.dylib
video_get: /usr/local/lib/libopencv_flann.3.3.0.dylib
video_get: /usr/local/lib/libopencv_imgproc.3.3.0.dylib
video_get: /usr/local/lib/libopencv_core.3.3.0.dylib
video_get: CMakeFiles/video_get.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/yellowos/CLionProjects/video_get/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable video_get"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/video_get.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/video_get.dir/build: video_get

.PHONY : CMakeFiles/video_get.dir/build

CMakeFiles/video_get.dir/requires: CMakeFiles/video_get.dir/main.cpp.o.requires

.PHONY : CMakeFiles/video_get.dir/requires

CMakeFiles/video_get.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/video_get.dir/cmake_clean.cmake
.PHONY : CMakeFiles/video_get.dir/clean

CMakeFiles/video_get.dir/depend:
	cd /Users/yellowos/CLionProjects/video_get/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/yellowos/CLionProjects/video_get /Users/yellowos/CLionProjects/video_get /Users/yellowos/CLionProjects/video_get/cmake-build-debug /Users/yellowos/CLionProjects/video_get/cmake-build-debug /Users/yellowos/CLionProjects/video_get/cmake-build-debug/CMakeFiles/video_get.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/video_get.dir/depend

