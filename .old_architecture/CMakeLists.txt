cmake_minimum_required(VERSION 3.21)

project(tot LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR True)

set(CODE_TENSOR_DIR "code/QuanCirc/src/tensors")
set(CODE_QUANTUMCIRC_DIR "code/QuanCirc/src/quantumcirc")
set(CODE_ALGORITHMS_DIR "code/QuanCirc/src/algorithms")

set(TEST_TENSOR_DIR "test/QuanCirc/src/tensors")
set(TEST_QUANTUMCIRC_DIR "test/QuanCirc/src/quantumcirc")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${CODE_TENSOR_DIR})
link_libraries(${GTEST_LIBRARIES} gtest_main pthread)

add_library(tensors STATIC)
add_library(quantumcirc STATIC)
add_library(random STATIC)
add_library(algorithms STATIC)
add_library(error STATIC 
            code/QuanCirc/src/error.cpp
    )
    
add_executable(utils_test)
add_executable(tensor_test)
add_executable(grover_test)
add_executable(qc_test)
add_executable(rotation_test)
add_executable(qc)



target_sources(tensors PRIVATE
                ${CODE_TENSOR_DIR}/tensor.cpp 
                ${CODE_TENSOR_DIR}/bin_utils.cpp 
                ${CODE_TENSOR_DIR}/eigen_impl.cpp 
                )       

target_sources(quantumcirc PRIVATE
                ${CODE_QUANTUMCIRC_DIR}/quantumcircuit.cpp 
                ${CODE_QUANTUMCIRC_DIR}/ps.cpp
                ${CODE_QUANTUMCIRC_DIR}/unitary.cpp
               )


target_sources(random PRIVATE
              code/QuanCirc/src/random/genfactory.cpp
              ${CODE_ALGORITHMS_DIR}/random_qc.cpp
              )

target_sources(algorithms PRIVATE 
                ${CODE_ALGORITHMS_DIR}/grover.cpp
                ${CODE_ALGORITHMS_DIR}/qaoa.cpp
              )
# target_sources(quantumcirc PUBLIC tensors )
target_sources(error PRIVATE code/QuanCirc/src/error.cpp )

target_link_libraries(utils_test    PUBLIC tensors error)
target_link_libraries(tensor_test   PUBLIC tensors error)
target_link_libraries(qc_test       PUBLIC quantumcirc tensors error)
target_link_libraries(grover_test   PUBLIC algorithms quantumcirc tensors error)
target_link_libraries(rotation_test PUBLIC quantumcirc tensors algorithms error)
target_link_libraries(qc            PUBLIC algorithms quantumcirc tensors  random error)

target_sources(qc PUBLIC
                main.cpp 
                )

target_sources(utils_test PRIVATE
                test/QuanCirc/src/tensors/test_bin_utils.cpp
                )       

target_sources(tensor_test PRIVATE
                test/QuanCirc/src/tensors/test_tensor.cpp
                )   

target_sources(grover_test PUBLIC
                test/QuanCirc/src/algorithms/grover_test.cpp
                )       

target_sources(qc_test PRIVATE
                test/QuanCirc/src/quantumcirc/test_qc.cpp
                )       

target_sources(rotation_test PRIVATE
                test/QuanCirc/src/quantumcirc/test_pauli_rotation.cpp
                )     