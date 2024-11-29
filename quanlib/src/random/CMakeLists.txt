project(random)
add_library(${PROJECT_NAME} OBJECT genfactory.cpp)
add_library(sub::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${MYPUBLIC_PATH}/quantumcircuit/algorithms)
