cmake_minimum_required(VERSION 3.21)

project(tot LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR True)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
link_libraries(${GTEST_LIBRARIES} gtest_main pthread)

add_executable(qc)
add_executable(utils_test)
add_executable(tensor_test)

add_library(tensors STATIC)
target_sources(tensors PUBLIC
                code/QuanCirc/src/tensors/tensor.cpp 
                code/QuanCirc/src/tensors/bin_utils.cpp 
                code/QuanCirc/src/tensors/eigen_impl.cpp 
                )       

target_link_libraries(qc tensors)
target_link_libraries(tensor_test PUBLIC tensors)

# target_sources(main PRIVATE main.cpp)
target_sources(qc PRIVATE 
                main.cpp 
                code/QuanCirc/src/quantumcircuit.cpp 
                code/QuanCirc/src/random_qc.cpp
                code/QuanCirc/src/random/genfactory.cpp)

target_sources(utils_test PRIVATE
                test/QuanCirc/src/tensors/test_bin_utils.cpp
                code/QuanCirc/src/tensors/bin_utils.cpp 
                )       

target_sources(tensor_test PRIVATE
                test/QuanCirc/src/tensors/test_tensor.cpp
                )       