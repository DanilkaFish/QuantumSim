#include "grover_test.h"

// #include "test/QuanCirc/inc/tensors/test_tensor.h"
// #include "inc/GateSimulator/__init__.h"
#include <bits/stdc++.h>
#include <string>

using ::testing::Combine;
using ::testing::Values;

DataPtr get_grover_state(int n, std::vector<int> ia, int k){
    DataPtr dptr(new Data(1<<n));
    (*dptr)[0] = DataType{0,0};
    int N = 1 << (n);
    int M = ia.size();
    double theta = 2*acos(sqrt(double(N-M)/N));
    for (int i = 0; i < dptr->size()/2; i++){
        if (std::find(ia.begin(), ia.end(), i) == ia.end()){
            (*dptr)[(1 << n)/2 + i] = -1/sqrt(2*N-2*M) * cos(theta * (2*k + 1)/2.);
            (*dptr)[i] = 1/sqrt(2*N - 2*M) * cos(theta * (2*k + 1)/2.);
        }else{
            (*dptr)[(1 << n)/2 + i] = -1/sqrt(2*M) * sin(theta * (2*k + 1)/2.);
            (*dptr)[i] = 1/sqrt(2*M) * sin(theta * (2*k + 1)/2.);
        }
    }
    return dptr;
}


TEST_P(GroverTest, TestGrover) {
    DataPtr dptr = get_grover_state(n , true_pos, k);
    auto qcqq = Oracle(5, std::vector<int>{2,3,4} ); 
    // 
    // State s(Qubits(n), dptr);
    // 
    QuantumCircuit qc = Grover(std::get<0>(qcqq), std::get<1>(qcqq), std::get<2>(qcqq), k);
    // TensorProvider exec(qc);
    // exec.run();
    // EXPECT_TRUE(compare(exec.state.conj() * exec.state, Tensor{1})) << ERR_PREFIX 
    //                             << "Not normed";
    // for (int i = 0; i < s.size(); i++){
    //     ASSERT_NEAR(s_exp[i].real(), s[i].real(), 0.000001) << ERR_PREFIX 
    //                             << "Differnt state array values on " << i;
    // }
    
};


INSTANTIATE_TEST_SUITE_P(ComboValues, GroverTest,
                        Combine(Values(3,4,6,4,5),
                                Values(std::vector<int>{0,2,5}),
                                Values(1,2,3)));



