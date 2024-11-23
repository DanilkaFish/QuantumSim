project(test_gatesim)
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}//test_gatesim.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${GS_SOURCE_PATH} ${TENSOR_PATH})

target_link_libraries(${PROJECT_NAME} sub::quantum sub::qubits sub::tensor sub::gatesim)
# target_sources(${PROJECT_NAME} PRIVATE )    

