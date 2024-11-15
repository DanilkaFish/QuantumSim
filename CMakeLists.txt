cmake_minimum_required(VERSION 3.21)

project(tot LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR True)


find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS} ${CODE_TENSOR_DIR})
link_libraries(${GTEST_LIBRARIES} gtest_main pthread)

set(CODE_QC_DIR "src/QuantumCircuit")
set(TEST_QC_DIR "tests/QuantumCircuit")
set(TEST_TENSOR_DIR "tests/Tensors")
set(CODE_TENSOR_DIR "src/Tensors")

set(TEST_SIM_DIR "tests/GateSimulator")
set(CODE_SIM_DIR "src/GateSimulator")

add_library(quantumcirc STATIC)
# add_library( STATIC)
add_library(qubits STATIC)

target_sources(quantumcirc PRIVATE
                ${CODE_QC_DIR}/quantumcircuit.cpp 
                )
target_sources(qubits PRIVATE
                src/qubits.cpp 
                )

add_executable(test_qc_interface)
add_executable(test_tensor_crtp)
add_executable(test_tensor_data)
add_executable(test_gatesim)

target_link_libraries(test_gatesim PUBLIC quantumcirc qubits )
target_link_libraries(test_qc_interface PUBLIC quantumcirc qubits)
target_link_libraries(test_tensor_crtp PUBLIC qubits)
target_link_libraries(test_tensor_data PUBLIC qubits)



target_sources(test_qc_interface PRIVATE
                ${TEST_QC_DIR}/test_qc_interface.cpp
                )       

target_sources(test_tensor_crtp PRIVATE
                ${TEST_TENSOR_DIR}/test_crtp.cpp
                ${CODE_TENSOR_DIR}/tensors.cpp
                )      

target_sources(test_tensor_data PRIVATE
                ${TEST_TENSOR_DIR}/test_datatensor.cpp
                ${CODE_TENSOR_DIR}/tensors.cpp
                )    

target_sources(test_gatesim PRIVATE
                ${TEST_SIM_DIR}/test_gatesim.cpp
                ${CODE_SIM_DIR}/gatesimulator.cpp
                ${CODE_TENSOR_DIR}/tensors.cpp
                )    

