find_package(GTest REQUIRED)
link_libraries(${GTEST_LIBRARIES} gtest_main pthread)


set(TEST_QC_DIR "QuantumCircuit")
set(TEST_TENSOR_DIR "Tensors")
set(TEST_SIM_DIR "GateSimulator")

option(TENSOR_TEST "Tensor" OFF)
option(QC_INTER_TEST "QC" OFF)
option(GATESIM_TEST "Gate simulator" OFF)
option(RANDOMQC_TEST "random_qc" OFF)
option(GROVER_TEST "grover" ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests/bin)
if(QC_INTER_TEST)
    include(QuantumCircuit/CMakeLists.txt)
else()
endif()

if(TENSOR_TEST)
    include(Tensors/CMakeLists.txt)
    else()
endif()

if(GATESIM_TEST)
    include(GateSimulator/CMakeLists.txt)
else()
endif()



if(GROVER_TEST)
    include(algorithms/CMakeLists.txt)
else()
endif()

