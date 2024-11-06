cmake_minimum_required(VERSION 3.21)

project(tot LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR True)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
link_libraries(${GTEST_LIBRARIES} gtest_main pthread)

add_executable(qc)
add_executable(utils_test)
add_executable(tensor_test)
add_executable(grover_test)
add_executable(qc_test)
add_executable(rotation_test)


add_library(tensors STATIC)
add_library(quantumcirc STATIC)

target_sources(tensors PUBLIC
                code/QuanCirc/src/tensors/tensor.cpp 
                code/QuanCirc/src/tensors/bin_utils.cpp 
                code/QuanCirc/src/tensors/eigen_impl.cpp 
                )       

# target_link_libraries(quantumcirc PUBLIC tensors)
target_sources(quantumcirc PUBLIC
                code/QuanCirc/src/quantumcirc/quantumcircuit.cpp 
                code/QuanCirc/src/quantumcirc/ps.cpp
                code/QuanCirc/src/quantumcirc/unitary.cpp
                )       

target_link_libraries(qc tensors quantumcirc)
target_link_libraries(tensor_test PUBLIC tensors)
target_link_libraries(grover_test PUBLIC tensors quantumcirc)
target_link_libraries(qc_test PUBLIC tensors quantumcirc)
target_link_libraries(rotation_test PUBLIC tensors quantumcirc)

target_sources(qc PRIVATE
                main.cpp 
                code/QuanCirc/src/random/genfactory.cpp
                code/QuanCirc/src/quantumcirc/random_qc.cpp
                code/QuanCirc/src/error.cpp
                )

target_sources(utils_test PRIVATE
                code/QuanCirc/src/error.cpp
                test/QuanCirc/src/tensors/test_bin_utils.cpp
                code/QuanCirc/src/tensors/bin_utils.cpp 
                )       

target_sources(tensor_test PRIVATE
                code/QuanCirc/src/error.cpp
                test/QuanCirc/src/tensors/test_tensor.cpp
                )   

target_sources(grover_test PRIVATE
                code/QuanCirc/src/error.cpp
                test/algorithms/grover_test.cpp
                )       

target_sources(qc_test PRIVATE
                code/QuanCirc/src/error.cpp
                test/QuanCirc/src/quantumcirc/test_qc.cpp
                )       

target_sources(rotation_test PRIVATE
                code/QuanCirc/src/error.cpp
                test/QuanCirc/src/quantumcirc/test_pauli_rotation.cpp

                )     