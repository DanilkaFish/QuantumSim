cmake_minimum_required(VERSION 3.5)

project(tot VERSION 0.1.0 )


option(TESTS "enable tests" ON)
option(MAIN "grover" OFF)

set(TENSOR_PATH ${PROJECT_SOURCE_DIR}/src/Tensors/include)
set(QC_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/QuantumCircuit/include)
set(GS_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/GateSimulator/include)
set(MYPUBLIC_PATH ${PROJECT_SOURCE_DIR}/include)
# set(CMAKE_INCLUDE_CURRENT_DIR True)


# include_directories(include/QuantumCircuit)
# include_directories(include/QuantumCircuit/algorithms)
# include_directories(include/QuantumCircuit/algorithms)

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
# include_directories(${PROJECT_SOURCE_DIR}/include/quantumcircuit)
# include_directories(${PROJECT_SOURCE_DIR}/include/Tensors)
# include_directories(${PROJECT_SOURCE_DIR}/include)



add_subdirectory(src/random)
add_subdirectory(src/Qubits)
add_subdirectory(src/QuantumCircuit)
add_subdirectory(src/GateSimulator)
add_subdirectory(src/Tensors)
add_subdirectory(src/algorithms)

# add_library(everything)
# target_link_libraries(everything PUBLIC sub::quantum sub::tensor sub::qubits sub::gatesim sub::grover sub::random)


if(TESTS)
    add_subdirectory(tests)
else()
endif()


if(MAIN)
    add_executable(main)
    target_sources(main PRIVATE 
        main.cpp
        )
    target_link_libraries(main PRIVATE everything )

else()
endif()

