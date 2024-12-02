
project(test_vqe)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/test_vqe.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${QC_SOURCE_PATH} ${VQE_SOURCE_PATH})

target_link_libraries(${PROJECT_NAME} quan)
