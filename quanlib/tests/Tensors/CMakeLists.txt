project(test_tensor)
add_executable(${PROJECT_NAME}_crtp ${CMAKE_CURRENT_LIST_DIR}/test_crtp.cpp)

target_include_directories(${PROJECT_NAME}_crtp PUBLIC ${MYPUBLIC_PATH}/quantumcircuit ${TR_SOURCE_PATH})
target_link_libraries(${PROJECT_NAME}_crtp quan)

add_executable(${PROJECT_NAME}_data ${CMAKE_CURRENT_LIST_DIR}/test_datatensor.cpp)

target_include_directories(${PROJECT_NAME}_data PUBLIC ${MYPUBLIC_PATH}/quantumcircuit ${TR_SOURCE_PATH})
target_link_libraries(${PROJECT_NAME}_data quan)
