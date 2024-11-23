project(quantum)

add_library(${PROJECT_NAME} quantumcircuit.cpp)
add_library(sub::${PROJECT_NAME} ALIAS ${PROJECT_NAME})


target_include_directories(${PROJECT_NAME} PUBLIC ${QC_SOURCE_PATH} ${MYPUBLIC_PATH}/quantumcircuit)