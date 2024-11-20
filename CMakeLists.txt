cmake_minimum_required(VERSION 3.21)

# set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
project(tot LANGUAGES CXX)


option(TENSOR_TEST "Tensor" ON)
option(QC_INTER_TEST "QC" ON)
option(GATESIM_TEST "Gate simulator" ON)
option(RANDOMQC_TEST "random_qc" ON)
option(GROVER_TEST "grover" ON)


set(CMAKE_INCLUDE_CURRENT_DIR True)
set(CODE_QC_DIR "src/QuantumCircuit")
set(TEST_QC_DIR "tests/QuantumCircuit")

set(CODE_TENSOR_DIR "src/Tensors")
set(TEST_TENSOR_DIR "tests/Tensors")

set(CODE_SIM_DIR "src/GateSimulator")
set(TEST_SIM_DIR "tests/GateSimulator")


# set(CMAKE_PREFIX_PATH "~/python_venvs/model/bin/python3")
# list(APPEND CMAKE_PREFIX_PATH "/usr/lib/python3.12")
# # /home/yadanilka/python_venvs/model/lib
# set(Python3_FIND_VIRTUALENV FIRST)
# find_package(Python REQUIRED COMPONENTS Interpreter Development)
# # find_package(PythonLibs REQUIRED)
# message(NOTICE ${Python_STDLIB})
# set(PYTHON_INCLUDE_DIRS "/usr/lib/python3.12")
# message(NOTICE ${PYTHON_INCLUDE_DIRS})
# message(NOTICE ${PYTHON_LIBRARIES})
# # set(Python_LIBRARY "/usr/lib/python3.12")
# # message(NOTICE ${CMAKE_PREFIX_PATH})
# # message(NOTICE "this message is on stderr pipe")
# # cmake_print_variables(PYTHON_INCLUDE_DIRS)
# link_libraries(${PYTHON_LIBRARIES})
# -------------------------------------------------
# find_package (Python3 REQUIRED COMPONENTS Interpreter Development )
# set(Python3_INCLUDE_DIRS /usr/include/python3.12)
# include_directories(${Python3_INCLUDE_DIRS})

# message(STATUS "Found Python: ${Python3_FOUND} ${Python3_INTERPRETER_ID} ${Python3_EXECUTABLE}")
# message(STATUS "Found Python3_LIBRARIES: ${Python3_LIBRARIES}")
# message(STATUS "Found INCLUDE: ${Python3_INCLUDE_DIRS}")
# message(STATUS "Found Python3_Development_FOUND: ${Python3_Development_FOUND}")
# message(STATUS "Found Python3_NumPy_FOUND: ${Python3_NumPy_FOUND} ${Python3_NumPy_INCLUDE_DIRS}")


find_package(GTest REQUIRED)
link_libraries(${GTEST_LIBRARIES} gtest_main pthread)


add_library(qubits STATIC src/qubits.cpp)
add_library(quantumcirc STATIC ${CODE_QC_DIR}/quantumcircuit.cpp )
add_library(random STATIC src/random/genfactory.cpp)
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
    target_link_libraries(test_randomqc PRIVATE quantumcirc tensor qubits gatesim random)
    target_sources(test_randomqc PRIVATE 
        ${TEST_QC_DIR}/algorithms/random_qc_test.cpp 
        src/QuantumCircuit/algorithms/random_qc.cpp
        )
else()
endif()

if(GROVER_TEST)
    add_executable(test_grover)
    target_sources(test_grover PRIVATE 
        src/QuantumCircuit/algorithms/grover.cpp
        ${TEST_QC_DIR}/algorithms/grover_test.cpp 
        )
    target_link_libraries(test_grover PUBLIC quantumcirc qubits tensor gatesim )
    # add_executable(a)
    # target_sources(a PRIVATE 
    #     test.cpp
    #     # src/QuantumCircuit/algorithms/grover.cpp
    #     # ${TEST_QC_DIR}/algorithms/grover_test.cpp 
    #     )
    # target_link_libraries(a PUBLIC qubits  )
else()
endif()




