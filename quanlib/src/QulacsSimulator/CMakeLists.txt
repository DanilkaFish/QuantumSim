project(qulacs)

add_library(${PROJECT_NAME} OBJECT qulacssim.cpp)
add_library(sub::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${QULACS_INCLUDE_PATH} ${CM_SOURCE_PATH})


