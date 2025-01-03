find_package(GTest REQUIRED)
link_libraries(${GTEST_LIBRARIES} gtest_main pthread)


set(TEST_QC_DIR "QuantumCircuit")
set(TEST_TENSOR_DIR "Tensors")
set(TEST_SIM_DIR "GateSimulator")

option(TENSOR_TEST "Tensor" ON)
option(QC_INTER_TEST "QC" ON)
option(GATESIM_TEST "Gate simulator" ON)
option(RANDOMQC_TEST "random_qc" ON)
option(GROVER_TEST "grover" ON)
option(VQE_TEST "vqe" ON)
option(QISKIT_TEST "qiskit provider in tests" ON)
if(QISKIT_TEST)
    add_compile_definitions(QISKIT_PROVIDER)
else()
endif()

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

if(GROVER_TEST)
    include(VQE/CMakeLists.txt)
else()
endif()

