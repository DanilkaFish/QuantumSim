#include "test/QuanCirc/inc/tensors/test_tensor.h"
#include <bits/stdc++.h>
#include <string>

using ::testing::Combine;
using ::testing::Values;

TEST_F(Test, TestTensordot) {
    IntArr it{};
    HSMatrix II(tensordot(instr::I(), instr::I(), IntArr{}, it).get_array());
    HSMatrix II_exp(ComplexArr{1,0,0,0,
                               0,1,0,0,
                               0,0,1,0,
                               0,0,0,1});
    ASSERT_EQ(II_exp.get_n_qubits(), II.get_n_qubits() ) << ERR_PREFIX
                                << "Different number of qubits!";
    for (int i = 0; i<II.size(); i++){
        ASSERT_EQ(II_exp[i], II[i]) << ERR_PREFIX 
                                << "Differnt array values";
    }

}




