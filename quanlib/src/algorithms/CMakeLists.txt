project(grover)
add_library(${PROJECT_NAME} grover.cpp)
add_library(sub::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE ${MYPUBLIC_PATH}/quantumcircuit)
