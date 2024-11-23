
project(test_qci)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}//test_qc_interface.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${QC_PATH}/include)

target_link_libraries(${PROJECT_NAME} sub::quantum sub::qubits)
# target_sources(${PROJECT_NAME}  )
