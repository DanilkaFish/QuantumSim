# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_SOURCE_DIR = /home/yadanilka/Projects/quansim/quanlib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yadanilka/Projects/quansim/quanlib/bin

# Include any dependencies generated for this target.
include src/Tensors/CMakeFiles/tensor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/Tensors/CMakeFiles/tensor.dir/compiler_depend.make

# Include the progress variables for this target.
include src/Tensors/CMakeFiles/tensor.dir/progress.make

# Include the compile flags for this target's objects.
include src/Tensors/CMakeFiles/tensor.dir/flags.make

src/Tensors/CMakeFiles/tensor.dir/codegen:
.PHONY : src/Tensors/CMakeFiles/tensor.dir/codegen

src/Tensors/CMakeFiles/tensor.dir/tensors.cpp.o: src/Tensors/CMakeFiles/tensor.dir/flags.make
src/Tensors/CMakeFiles/tensor.dir/tensors.cpp.o: /home/yadanilka/Projects/quansim/quanlib/src/Tensors/tensors.cpp
src/Tensors/CMakeFiles/tensor.dir/tensors.cpp.o: src/Tensors/CMakeFiles/tensor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/yadanilka/Projects/quansim/quanlib/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Tensors/CMakeFiles/tensor.dir/tensors.cpp.o"
	cd /home/yadanilka/Projects/quansim/quanlib/bin/src/Tensors && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Tensors/CMakeFiles/tensor.dir/tensors.cpp.o -MF CMakeFiles/tensor.dir/tensors.cpp.o.d -o CMakeFiles/tensor.dir/tensors.cpp.o -c /home/yadanilka/Projects/quansim/quanlib/src/Tensors/tensors.cpp

src/Tensors/CMakeFiles/tensor.dir/tensors.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tensor.dir/tensors.cpp.i"
	cd /home/yadanilka/Projects/quansim/quanlib/bin/src/Tensors && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yadanilka/Projects/quansim/quanlib/src/Tensors/tensors.cpp > CMakeFiles/tensor.dir/tensors.cpp.i

src/Tensors/CMakeFiles/tensor.dir/tensors.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tensor.dir/tensors.cpp.s"
	cd /home/yadanilka/Projects/quansim/quanlib/bin/src/Tensors && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yadanilka/Projects/quansim/quanlib/src/Tensors/tensors.cpp -o CMakeFiles/tensor.dir/tensors.cpp.s

tensor: src/Tensors/CMakeFiles/tensor.dir/tensors.cpp.o
tensor: src/Tensors/CMakeFiles/tensor.dir/build.make
.PHONY : tensor

# Rule to build all files generated by this target.
src/Tensors/CMakeFiles/tensor.dir/build: tensor
.PHONY : src/Tensors/CMakeFiles/tensor.dir/build

src/Tensors/CMakeFiles/tensor.dir/clean:
	cd /home/yadanilka/Projects/quansim/quanlib/bin/src/Tensors && $(CMAKE_COMMAND) -P CMakeFiles/tensor.dir/cmake_clean.cmake
.PHONY : src/Tensors/CMakeFiles/tensor.dir/clean

src/Tensors/CMakeFiles/tensor.dir/depend:
	cd /home/yadanilka/Projects/quansim/quanlib/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yadanilka/Projects/quansim/quanlib /home/yadanilka/Projects/quansim/quanlib/src/Tensors /home/yadanilka/Projects/quansim/quanlib/bin /home/yadanilka/Projects/quansim/quanlib/bin/src/Tensors /home/yadanilka/Projects/quansim/quanlib/bin/src/Tensors/CMakeFiles/tensor.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/Tensors/CMakeFiles/tensor.dir/depend

