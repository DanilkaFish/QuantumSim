project(gatesim)

add_library(${PROJECT_NAME} gatesimulator.cpp)
add_library(sub::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC include ${TENSOR_PATH} ${QC_SOURCE_PATH} ${MYPUBLIC_PATH}/quantumcircuit)


