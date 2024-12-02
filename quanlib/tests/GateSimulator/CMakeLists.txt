project(test_state_evolve)
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/test_state_evolve.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${GS_SOURCE_PATH} ${TR_SOURCE_PATH})

target_link_libraries(${PROJECT_NAME} quan)
# target_sources(${PROJECT_NAME} PRIVATE )    

