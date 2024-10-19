#include "test/algorithms/grover_test.h"

#include "test/QuanCirc/inc/tensors/test_tensor.h"
#include <bits/stdc++.h>
#include <string>

using ::testing::Combine;
using ::testing::Values;

State get_grover_state(int n, IntArr ia, int k){
    State s(n + 1);
    s[0] = Complex{0,0};
    int N = 1 << (n);
    int M = ia.size();
    double theta = 2*acos(sqrt(double(N-M)/N));
    for (int i = 0; i < s.size()/2; i++){
        if (std::find(ia.begin(), ia.end(), i) == ia.end()){
            s[(1 << n) + i] = -1/sqrt(2*N-2*M) * cos(theta * (2*k + 1)/2.);
            s[i] = 1/sqrt(2*N-2*M) * cos(theta * (2*k + 1)/2.);
        }else{
            s[(1 << n) + i] = -1/sqrt(2*M) * sin(theta * (2*k + 1)/2.);
            s[i] = 1/sqrt(2*M) * sin(theta * (2*k + 1)/2.);
        }
    }
    return s;
}

TEST_P(GroverTest, TestGrover) {
    State s_exp = get_grover_state(n , true_pos, k);
    ASSERT_NEAR(s_exp.norm(), 1, 0.0001) << ERR_PREFIX 
                                << "Differnt state qubits size";
    for (int i = 0; i < s.size(); i++){
        ASSERT_NEAR(s_exp[i].real(), s[i].real(), 0.000001) << ERR_PREFIX 
                                << "Differnt state array values on " << i;
    }
    
};


INSTANTIATE_TEST_CASE_P(ComboValues, GroverTest,
                        Combine(Values(3,4,5,6),
                                Values(IntArr{0,2,5}),
                                Values(1,2,3)));



