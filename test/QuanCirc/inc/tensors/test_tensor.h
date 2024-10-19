#ifndef _TEST_BIN_UTILS
#define _TEST_BIN_UTILS

#include <gtest/gtest.h>
#include "code/QuanCirc/inc/tensors/tensor.h"

#include <iostream>
#include <tuple>

using ::testing::TestWithParam;  // GTest parametric test fixture
using namespace tensor;
#include "test/common_test.h"


class VSInitTest : public TestWithParam<int>{
protected:
    int n_qubits;

    void SetUp() override {
    // `GetParam()` fetches the parameter, then we unpack the tuple
        n_qubits = GetParam();
    }
};

// class StateDotTest : public Test{
// protected:
//     int n_qubits;

//     void SetUp() override {
//     // `GetParam()` fetches the parameter, then we unpack the tuple
//         n_qubits = GetParam();
//     }
// };


#endif