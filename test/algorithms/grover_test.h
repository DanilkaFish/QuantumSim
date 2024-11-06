#ifndef _TEST_GROVER
#define _TEST_GROVER

#include <gtest/gtest.h>
#include "code/QuanCirc/inc/quantumcirc/quantumcircuit.h"
#include "code/algorithms/grover.cpp"
#include <algorithm>
#include <iostream>
#include <tuple>

using ::testing::TestWithParam;  // GTest parametric test fixture
using namespace tensor;

#include "test/common_test.h"


class GroverTest : public TestWithParam<std::tuple<int, IntArr, int>>{
protected:
    int n;
    IntArr true_pos;
    int k;
    State s;

    void SetUp() override {
        n = std::get<0>(GetParam());
        k = std::get<2>(GetParam());
        true_pos = std::get<1>(GetParam());
        QuantumCircuit qc = grover(n,  true_pos, k); 
        s = qc.execute();
        IntArr ia(n - 2);
        IntArr ia2(n - 2);
        for (int i = 0; i < n - 2; i++){
            ia[i] = i;
            ia2[i] = n + i;
        }
        s = tensor::statedot(State(n - 2), s, ia, ia2);
    }
};

#endif
