project(grover)
set(GROVER_NAME grover)
add_library(${GROVER_NAME} OBJECT grover.cpp)
add_library(sub::${GROVER_NAME} ALIAS ${GROVER_NAME})
# add_test()
target_include_directories(${GROVER_NAME} PRIVATE ${QC_SOURCE_PATH} ${CM_SOURCE_PATH})

set(RANDOM_QC_NAME random_qc)
add_library(${RANDOM_QC_NAME} OBJECT random_qc.cpp)
add_library(sub::${RANDOM_QC_NAME} ALIAS ${RANDOM_QC_NAME})
# add_test()
target_include_directories(${RANDOM_QC_NAME} PRIVATE ${QC_SOURCE_PATH} ${CM_SOURCE_PATH} ${RD_SOURCE_PATH} ${EIGEN_INCLUDE_PATH})

set(TRANSPILER_NAME transpiler)
add_library(${TRANSPILER_NAME} OBJECT transpilers.cpp)
add_library(sub::${TRANSPILER_NAME} ALIAS ${TRANSPILER_NAME})
# add_test()
target_include_directories(${TRANSPILER_NAME} PRIVATE ${TR_SOURCE_PATH} ${QC_SOURCE_PATH} ${CM_SOURCE_PATH} ${RD_SOURCE_PATH} ${EIGEN_INCLUDE_PATH})

set(QAOA_NAME qaoa)
add_library(${QAOA_NAME} OBJECT qaoa.cpp)
add_library(sub::${QAOA_NAME} ALIAS ${QAOA_NAME})
# add_test()
target_include_directories(${QAOA_NAME} PRIVATE ${QC_SOURCE_PATH} ${CM_SOURCE_PATH} ${RD_SOURCE_PATH} ${EIGEN_INCLUDE_PATH} ${GS_SOURCE_PATH} ${TR_SOURCE_PATH})

