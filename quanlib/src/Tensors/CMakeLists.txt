project(tensor)

add_library(${PROJECT_NAME} tensors.cpp)
add_library(sub::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC include ${MYPUBLIC_PATH}/quantumcircuit)

# export(tensor)