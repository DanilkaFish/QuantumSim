cmake_minimum_required(VERSION 3.14)
project(main)
set(ENV{VIRTUAL_ENV} "/home/yadanilka/python_venvs/quansim/")
set(Python_VIRTUALENV FIRST)
set(pybind11_DIR /home/yadanilka/python_venvs/quansim/lib/python3.12/site-packages/pybind11/include)
find_package(pybind11 REQUIRED)
find_package(Python REQUIRED COMPONENTS Interpreter Development )
message(NOTICE ${Python_EXECUTABLE})
message(NOTICE ${pybind11_INCLUDE_DIRS})
message(NOTICE ${Python_LIBRARY})
# find_package(nlopt REQUIRED)
link_libraries(${PYTHON_LIBRARIES})
set(QAUNLIB_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/quanlib/include/QuantumCircuit
                         ${PROJECT_SOURCE_DIR}/quanlib/include/algorithms
                         ${PROJECT_SOURCE_DIR}/quanlib/include/QiskitSimulator
                         ${PROJECT_SOURCE_DIR}/quanlib/include/StateSimulator
                         ${PROJECT_SOURCE_DIR}/quanlib/include/Tensors
                         ${PROJECT_SOURCE_DIR}/quanlib/include/Utils
                         ${PROJECT_SOURCE_DIR}/quanlib/include/VQE
                         )
set(NLOPT_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/ext_sources/nlopt/bin)
message(NOTICE ${NLOPT_INCLUDE_PATH})
# set(QULACS_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/ext_sources/qulacs/include)

# add_subdirectory(ext_sources/qulacs)

add_executable(main)
target_sources(main PRIVATE 
    main.cpp
    )
target_link_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/quanlib/lib)
target_link_libraries(main PRIVATE quan ${NLOPT_INCLUDE_PATH}/libnlopt.so)
target_include_directories(main PUBLIC ${QAUNLIB_INCLUDE_DIRS} ${Python_INCLUDE_DIRS} ${NLOPT_INCLUDE_PATH})
target_compile_options(main PRIVATE -pthread)