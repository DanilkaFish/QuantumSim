cmake_minimum_required(VERSION 3.21)

project(tot LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR True)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
link_libraries(${GTEST_LIBRARIES} gtest_main pthread)

add_executable(qc)

# add_library(main STATIC)


# target_sources(main PRIVATE main.cpp)
target_sources(qc PRIVATE 
                main.cpp 
                code/QuanCirc/src/tensors/tensor.cpp 
                code/QuanCirc/src/quantumcircuit.cpp 
                code/QuanCirc/src/random_qc.cpp
                code/QuanCirc/src/random/genfactory.cpp)

