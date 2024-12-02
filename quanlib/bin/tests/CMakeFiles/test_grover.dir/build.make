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
include tests/CMakeFiles/test_grover.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/test_grover.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_grover.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_grover.dir/flags.make

tests/CMakeFiles/test_grover.dir/codegen:
.PHONY : tests/CMakeFiles/test_grover.dir/codegen

tests/CMakeFiles/test_grover.dir/algorithms/grover_test.cpp.o: tests/CMakeFiles/test_grover.dir/flags.make
tests/CMakeFiles/test_grover.dir/algorithms/grover_test.cpp.o: /home/yadanilka/Projects/quansim/quanlib/tests/algorithms/grover_test.cpp
tests/CMakeFiles/test_grover.dir/algorithms/grover_test.cpp.o: tests/CMakeFiles/test_grover.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/yadanilka/Projects/quansim/quanlib/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/test_grover.dir/algorithms/grover_test.cpp.o"
	cd /home/yadanilka/Projects/quansim/quanlib/bin/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/test_grover.dir/algorithms/grover_test.cpp.o -MF CMakeFiles/test_grover.dir/algorithms/grover_test.cpp.o.d -o CMakeFiles/test_grover.dir/algorithms/grover_test.cpp.o -c /home/yadanilka/Projects/quansim/quanlib/tests/algorithms/grover_test.cpp

tests/CMakeFiles/test_grover.dir/algorithms/grover_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_grover.dir/algorithms/grover_test.cpp.i"
	cd /home/yadanilka/Projects/quansim/quanlib/bin/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yadanilka/Projects/quansim/quanlib/tests/algorithms/grover_test.cpp > CMakeFiles/test_grover.dir/algorithms/grover_test.cpp.i

tests/CMakeFiles/test_grover.dir/algorithms/grover_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_grover.dir/algorithms/grover_test.cpp.s"
	cd /home/yadanilka/Projects/quansim/quanlib/bin/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yadanilka/Projects/quansim/quanlib/tests/algorithms/grover_test.cpp -o CMakeFiles/test_grover.dir/algorithms/grover_test.cpp.s

# Object files for target test_grover
test_grover_OBJECTS = \
"CMakeFiles/test_grover.dir/algorithms/grover_test.cpp.o"

# External object files for target test_grover
test_grover_EXTERNAL_OBJECTS =

test_grover: tests/CMakeFiles/test_grover.dir/algorithms/grover_test.cpp.o
test_grover: tests/CMakeFiles/test_grover.dir/build.make
test_grover: tests/CMakeFiles/test_grover.dir/compiler_depend.ts
test_grover: /usr/lib/libgtest.so.1.15.2
test_grover: /home/yadanilka/Projects/quansim/quanlib/lib/libquan.a
test_grover: tests/CMakeFiles/test_grover.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/yadanilka/Projects/quansim/quanlib/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../test_grover"
	cd /home/yadanilka/Projects/quansim/quanlib/bin/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_grover.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_grover.dir/build: test_grover
.PHONY : tests/CMakeFiles/test_grover.dir/build

tests/CMakeFiles/test_grover.dir/clean:
	cd /home/yadanilka/Projects/quansim/quanlib/bin/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_grover.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_grover.dir/clean

tests/CMakeFiles/test_grover.dir/depend:
	cd /home/yadanilka/Projects/quansim/quanlib/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yadanilka/Projects/quansim/quanlib /home/yadanilka/Projects/quansim/quanlib/tests /home/yadanilka/Projects/quansim/quanlib/bin /home/yadanilka/Projects/quansim/quanlib/bin/tests /home/yadanilka/Projects/quansim/quanlib/bin/tests/CMakeFiles/test_grover.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/test_grover.dir/depend

