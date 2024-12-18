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
include CMakeFiles/quan.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/quan.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/quan.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/quan.dir/flags.make

CMakeFiles/quan.dir/codegen:
.PHONY : CMakeFiles/quan.dir/codegen

# Object files for target quan
quan_OBJECTS =

# External object files for target quan
quan_EXTERNAL_OBJECTS = \
"/home/yadanilka/Projects/quansim/quanlib/bin/src/QuantumCircuit/CMakeFiles/quantum.dir/quantumcircuit.cpp.o" \
"/home/yadanilka/Projects/quansim/quanlib/bin/src/Tensors/CMakeFiles/tensor.dir/tensors.cpp.o" \
"/home/yadanilka/Projects/quansim/quanlib/bin/src/Utils/CMakeFiles/common.dir/common.cpp.o" \
"/home/yadanilka/Projects/quansim/quanlib/bin/src/StateSimulator/CMakeFiles/state_evolve.dir/gatesimulator.cpp.o" \
"/home/yadanilka/Projects/quansim/quanlib/bin/src/algorithms/CMakeFiles/grover.dir/grover.cpp.o" \
"/home/yadanilka/Projects/quansim/quanlib/bin/src/random/CMakeFiles/random.dir/genfactory.cpp.o" \
"/home/yadanilka/Projects/quansim/quanlib/bin/src/algorithms/CMakeFiles/random_qc.dir/random_qc.cpp.o" \
"/home/yadanilka/Projects/quansim/quanlib/bin/src/VQE/CMakeFiles/vqe.dir/vqe.cpp.o" \
"/home/yadanilka/Projects/quansim/quanlib/bin/src/QiskitSimulator/CMakeFiles/qiskit_evolve.dir/pybind.cpp.o" \
"/home/yadanilka/Projects/quansim/quanlib/bin/src/algorithms/CMakeFiles/qaoa.dir/qaoa.cpp.o"

/home/yadanilka/Projects/quansim/quanlib/lib/libquan.a: src/QuantumCircuit/CMakeFiles/quantum.dir/quantumcircuit.cpp.o
/home/yadanilka/Projects/quansim/quanlib/lib/libquan.a: src/Tensors/CMakeFiles/tensor.dir/tensors.cpp.o
/home/yadanilka/Projects/quansim/quanlib/lib/libquan.a: src/Utils/CMakeFiles/common.dir/common.cpp.o
/home/yadanilka/Projects/quansim/quanlib/lib/libquan.a: src/StateSimulator/CMakeFiles/state_evolve.dir/gatesimulator.cpp.o
/home/yadanilka/Projects/quansim/quanlib/lib/libquan.a: src/algorithms/CMakeFiles/grover.dir/grover.cpp.o
/home/yadanilka/Projects/quansim/quanlib/lib/libquan.a: src/random/CMakeFiles/random.dir/genfactory.cpp.o
/home/yadanilka/Projects/quansim/quanlib/lib/libquan.a: src/algorithms/CMakeFiles/random_qc.dir/random_qc.cpp.o
/home/yadanilka/Projects/quansim/quanlib/lib/libquan.a: src/VQE/CMakeFiles/vqe.dir/vqe.cpp.o
/home/yadanilka/Projects/quansim/quanlib/lib/libquan.a: src/QiskitSimulator/CMakeFiles/qiskit_evolve.dir/pybind.cpp.o
/home/yadanilka/Projects/quansim/quanlib/lib/libquan.a: src/algorithms/CMakeFiles/qaoa.dir/qaoa.cpp.o
/home/yadanilka/Projects/quansim/quanlib/lib/libquan.a: CMakeFiles/quan.dir/build.make
/home/yadanilka/Projects/quansim/quanlib/lib/libquan.a: CMakeFiles/quan.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/yadanilka/Projects/quansim/quanlib/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX static library /home/yadanilka/Projects/quansim/quanlib/lib/libquan.a"
	$(CMAKE_COMMAND) -P CMakeFiles/quan.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/quan.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/quan.dir/build: /home/yadanilka/Projects/quansim/quanlib/lib/libquan.a
.PHONY : CMakeFiles/quan.dir/build

CMakeFiles/quan.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/quan.dir/cmake_clean.cmake
.PHONY : CMakeFiles/quan.dir/clean

CMakeFiles/quan.dir/depend:
	cd /home/yadanilka/Projects/quansim/quanlib/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yadanilka/Projects/quansim/quanlib /home/yadanilka/Projects/quansim/quanlib /home/yadanilka/Projects/quansim/quanlib/bin /home/yadanilka/Projects/quansim/quanlib/bin /home/yadanilka/Projects/quansim/quanlib/bin/CMakeFiles/quan.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/quan.dir/depend

