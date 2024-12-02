cmake_minimum_required(VERSION 3.14)
project(main)

set(QULACS_LIB_PATH ${PROJECT_SOURCE_DIR}/ext_sources/qulacs/lib)
set(QULACS_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/ext_sources/qulacs/include)

# add_subdirectory(ext_sources/qulacs)
add_subdirectory(quanlib)

add_executable(main)
target_sources(main PRIVATE 
    main.cpp
    )
target_link_libraries(main PRIVATE sub::quantum sub::tensor sub::qubits sub::state_evolve sub::grover sub::random ${QULACS_LIB_PATH}/libqcsim_static.a)
target_include_directories(main PUBLIC ${TR_SOURCE_PATH} ${MYPUBLIC_PATH} )
target_compile_options(main PRIVATE -pthread)