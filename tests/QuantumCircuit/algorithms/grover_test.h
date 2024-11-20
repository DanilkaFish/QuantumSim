#ifndef _TEST_GROVER
#define _TEST_GROVER

#include <gtest/gtest.h>
#include "inc/QuantumCircuit/algorithms/grover.h"


#include <algorithm>
#include <iostream>
#include <tuple>

using ::testing::TestWithParam;  // GTest parametric test fixture
// using namespace tensor;

#include "tests/common_test.h"

class GroverTest : public TestWithParam<std::tuple<int, std::vector<int>, int>>{

    
protected:
    int n;
    int k;
    std::vector<int> true_pos;

    void SetUp() override {
        n = std::get<0>(GetParam());
        true_pos = std::get<1>(GetParam());
        k = std::get<2>(GetParam());

    }
};

#endif
