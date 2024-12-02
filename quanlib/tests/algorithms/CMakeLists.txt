set(CMAKE_INCLUDE_CURRENT_DIR True)

add_executable(test_grover)
target_link_libraries(test_grover quan)
target_sources(test_grover PRIVATE ${CMAKE_CURRENT_LIST_DIR}/grover_test.cpp)    
target_include_directories(test_grover PUBLIC ${QC_SOURCE_PATH} ${GS_SOURCE_PATH})
