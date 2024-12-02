project(common)

add_library(${PROJECT_NAME} OBJECT common.cpp)
add_library(sub::${PROJECT_NAME} ALIAS ${PROJECT_NAME})


# target_include_directories(${PROJECT_NAME} PUBLIC )
# export(TARGETS qubits)