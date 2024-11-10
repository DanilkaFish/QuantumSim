cmake_minimum_required(VERSION 3.21)

project(tot LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR True)


find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS} ${CODE_TENSOR_DIR})
link_libraries(${GTEST_LIBRARIES} gtest_main pthread)

set(CODE_QC_DIR "src/QuantumCircuit")
set(TEST_QC_DIR "tests/QuantumCircuit")

add_library(quantumcirc STATIC)

target_sources(quantumcirc PRIVATE
                ${CODE_QC_DIR}/quantumcircuit.cpp 
                )

add_executable(test_qc_interface)

target_link_libraries(test_qc_interface PUBLIC quantumcirc)




target_sources(test_qc_interface PRIVATE
                ${TEST_QC_DIR}/test_qc_interface.cpp
                )       

