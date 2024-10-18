#include "test/QuanCirc/inc/tensors/test_tensor.h"
#include <bits/stdc++.h>
#include <string>

using ::testing::Combine;
using ::testing::Values;

TEST_P(VSInitTest, TestVsInitialization) {
    std::vector<State> vs;
    for (int i=0; i< n_qubits; i++){
        vs.push_back(State(1));
    }
    State s(vs);
    State s_exp(n_qubits);

    ASSERT_EQ(s.get_n_qubits(), n_qubits) << ERR_PREFIX
                                << "Different number of qubits!";

    for (int i = 0; i < s.size(); i++){
        ASSERT_EQ(s_exp[i], s[i]) << ERR_PREFIX 
                                << "Differnt state array values on " << i;
    }

    IntArr ia(n_qubits);
    
    for (int i = 0; i < n_qubits; i++){
        ia[i] = i;
    }
    
    ASSERT_EQ(Complex(1,0), statedot(s,s,ia,ia).get_array()[0]) << ERR_PREFIX
                            << "Different number of qubits!";
};

INSTANTIATE_TEST_CASE_P(SelectValues, VSInitTest,
                        Values(0, 1, 2, 3, 4, 5, 10));




