# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/robert/Computergrafik/asteroids_3d

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/robert/Computergrafik/asteroids_3d

# Include any dependencies generated for this target.
include CMakeFiles/math_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/math_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/math_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/math_test.dir/flags.make

CMakeFiles/math_test.dir/math_test.cc.o: CMakeFiles/math_test.dir/flags.make
CMakeFiles/math_test.dir/math_test.cc.o: math_test.cc
CMakeFiles/math_test.dir/math_test.cc.o: CMakeFiles/math_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/robert/Computergrafik/asteroids_3d/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/math_test.dir/math_test.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/math_test.dir/math_test.cc.o -MF CMakeFiles/math_test.dir/math_test.cc.o.d -o CMakeFiles/math_test.dir/math_test.cc.o -c /home/robert/Computergrafik/asteroids_3d/math_test.cc

CMakeFiles/math_test.dir/math_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/math_test.dir/math_test.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/Computergrafik/asteroids_3d/math_test.cc > CMakeFiles/math_test.dir/math_test.cc.i

CMakeFiles/math_test.dir/math_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/math_test.dir/math_test.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/Computergrafik/asteroids_3d/math_test.cc -o CMakeFiles/math_test.dir/math_test.cc.s

CMakeFiles/math_test.dir/math.cc.o: CMakeFiles/math_test.dir/flags.make
CMakeFiles/math_test.dir/math.cc.o: math.cc
CMakeFiles/math_test.dir/math.cc.o: CMakeFiles/math_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/robert/Computergrafik/asteroids_3d/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/math_test.dir/math.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/math_test.dir/math.cc.o -MF CMakeFiles/math_test.dir/math.cc.o.d -o CMakeFiles/math_test.dir/math.cc.o -c /home/robert/Computergrafik/asteroids_3d/math.cc

CMakeFiles/math_test.dir/math.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/math_test.dir/math.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/Computergrafik/asteroids_3d/math.cc > CMakeFiles/math_test.dir/math.cc.i

CMakeFiles/math_test.dir/math.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/math_test.dir/math.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/Computergrafik/asteroids_3d/math.cc -o CMakeFiles/math_test.dir/math.cc.s

# Object files for target math_test
math_test_OBJECTS = \
"CMakeFiles/math_test.dir/math_test.cc.o" \
"CMakeFiles/math_test.dir/math.cc.o"

# External object files for target math_test
math_test_EXTERNAL_OBJECTS =

math_test: CMakeFiles/math_test.dir/math_test.cc.o
math_test: CMakeFiles/math_test.dir/math.cc.o
math_test: CMakeFiles/math_test.dir/build.make
math_test: CMakeFiles/math_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/robert/Computergrafik/asteroids_3d/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable math_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/math_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/math_test.dir/build: math_test
.PHONY : CMakeFiles/math_test.dir/build

CMakeFiles/math_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/math_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/math_test.dir/clean

CMakeFiles/math_test.dir/depend:
	cd /home/robert/Computergrafik/asteroids_3d && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robert/Computergrafik/asteroids_3d /home/robert/Computergrafik/asteroids_3d /home/robert/Computergrafik/asteroids_3d /home/robert/Computergrafik/asteroids_3d /home/robert/Computergrafik/asteroids_3d/CMakeFiles/math_test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/math_test.dir/depend

