project(qubits)

add_library(${PROJECT_NAME} qubits.cpp)
add_library(sub::${PROJECT_NAME} ALIAS ${PROJECT_NAME})


target_include_directories(${PROJECT_NAME} PUBLIC ${MYPUBLIC_PATH}/quantumcircuit)
# export(TARGETS qubits)