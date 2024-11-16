cmake_minimum_required(VERSION 3.21)

project(tot LANGUAGES CXX)


option(TENSOR_TEST "Tensor" ON)
option(QC_INTER_TEST "QC" ON)
option(GATESIM_TEST "Gate simulator" ON)
option(RANDOMQC_TEST "random_qc" OFF)



set(CMAKE_INCLUDE_CURRENT_DIR True)
set(CODE_QC_DIR "src/QuantumCircuit")
set(TEST_QC_DIR "tests/QuantumCircuit")

set(CODE_TENSOR_DIR "src/Tensors")
set(TEST_TENSOR_DIR "tests/Tensors")

set(CODE_SIM_DIR "src/GateSimulator")
set(TEST_SIM_DIR "tests/GateSimulator")



find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS} ${CODE_TENSOR_DIR})
link_libraries(${GTEST_LIBRARIES} gtest_main pthread)


add_library(qubits STATIC src/qubits.cpp)
add_library(quantumcirc STATIC ${CODE_QC_DIR}/quantumcircuit.cpp )
# add_library(random STATIC src/random/genfactory.cpp)
add_library(gatesim STATIC ${CODE_SIM_DIR}/gatesimulator.cpp)
add_library(tensor STATIC ${CODE_TENSOR_DIR}/tensors.cpp)

if(QC_INTER_TEST)
    add_executable(test_qc_interface)
    target_link_libraries(test_qc_interface PUBLIC quantumcirc qubits)
    target_sources(test_qc_interface PRIVATE ${TEST_QC_DIR}/test_qc_interface.cpp)
else()
endif()

if(TENSOR_TEST)
    add_executable(test_tensor_crtp)
    add_executable(test_tensor_data)
    target_link_libraries(test_tensor_crtp PUBLIC tensor qubits )
    target_link_libraries(test_tensor_data PUBLIC tensor qubits )
    target_sources(test_tensor_crtp PRIVATE ${TEST_TENSOR_DIR}/test_crtp.cpp)      
    target_sources(test_tensor_data PRIVATE ${TEST_TENSOR_DIR}/test_datatensor.cpp)    
else()
endif()

if(GATESIM_TEST)
    add_executable(test_gatesim)
    target_link_libraries(test_gatesim PUBLIC quantumcirc tensor qubits gatesim )
    target_sources(test_gatesim PRIVATE ${TEST_SIM_DIR}/test_gatesim.cpp)    
else()
endif()


if(RANDOMQC_TEST)
    add_executable(test_randomqc)
    target_link_libraries(test_randomqc PUBLIC quantumcirc tensor qubits gatesim random)
    target_sources(test_randomqc PRIVATE 
        ${TEST_SIM_DIR}/algorithms/random_qc_test.cpp 
        src/GateSimulator/algorithms/random_qc.cpp
        )
else()
endif()




