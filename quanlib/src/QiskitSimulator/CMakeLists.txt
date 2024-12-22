project(qiskit_evolve)
set(ENV{VIRTUAL_ENV} "/home/yadanilka/python_venvs/quansim/")
set(Python_VIRTUALENV FIRST)
# TODO
set(pybind11_DIR /home/yadanilka/python_venvs/quansim/lib/python3.12/site-packages/pybind11/include)
find_package(pybind11 REQUIRED)
find_package(Python REQUIRED COMPONENTS Interpreter Development )
# find_package(Pybind REQUIRED COMPONENTS Interpreter Development )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
link_libraries(${PYTHON_LIBRARIES})
message(NOTICE ${Python_EXECUTABLE})
message(NOTICE ${pybind11_INCLUDE_DIRS})
# if (Python_FOUND){

# }
add_executable(main main.cpp)
add_library(${PROJECT_NAME} OBJECT pybind.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${TR_SOURCE_PATH} ${QC_SOURCE_PATH} ${GS_SOURCE_PATH} ${CM_SOURCE_PATH} ${Python_INCLUDE_DIRS})
target_link_libraries(main quan)
set_target_properties(${PROJECT_NAME}  PROPERTIES CXX_VISIBILITY_PRESET hidden)
set_target_properties(main PROPERTIES CXX_VISIBILITY_PRESET hidden)



