
#include "grover_test.h"
#include "qiskit_provider.h"
// #include "inc/GateSimulator/__init__.h"

#include <bits/stdc++.h>
#include <string>

using ::testing::Combine;
using ::testing::Values;

DataPtr get_grover_state(int n, std::vector<int> ia, int k){
    DataPtr dptr(new Data(1<<n+1));
    (*dptr)[0] = DataType{0,0};
    int N = 1 << (n);
    int M = ia.size();
    double theta = 2*acos(sqrt(double(N-M)/N));
    for (int i = 0; i < dptr->size()/2; i++){
        if (std::find(ia.begin(), ia.end(), i) == ia.end()){
            (*dptr)[(1 << n) + i] = -1/sqrt(2*N-2*M) * cos(theta * (2*k + 1)/2.);
            (*dptr)[i] = 1/sqrt(2*N - 2*M) * cos(theta * (2*k + 1)/2.);
        }else{
            (*dptr)[(1 << n) + i] = -1/sqrt(2*M) * sin(theta * (2*k + 1)/2.);
            (*dptr)[i] = 1/sqrt(2*M) * sin(theta * (2*k + 1)/2.);
        }
    }
    return dptr;
}

//     State s(n + 1);
//     s[0] = Complex{0,0};
//     int N = 1 << (n);
//     int M = ia.size();
//     double theta = 2*acos(sqrt(double(N-M)/N));
//     for (int i = 0; i < s.size()/2; i++){
//         if (std::find(ia.begin(), ia.end(), i) == ia.end()){
//             s[(1 << n) + i] = -1/sqrt(2*N-2*M) * cos(theta * (2*k + 1)/2.);
//             s[i] = 1/sqrt(2*N-2*M) * cos(theta * (2*k + 1)/2.);
//         }else{
//             s[(1 << n) + i] = -1/sqrt(2*M) * sin(theta * (2*k + 1)/2.);
//             s[i] = 1/sqrt(2*M) * sin(theta * (2*k + 1)/2.);
//         }
//     }
//     return s;

TEST_P(GroverTest, TestGrover) {

    auto qcqq = Oracle(n, true_pos ); 
    
    DataPtr dptr = get_grover_state(n , true_pos, k);
    Qubits qubs_st(std::get<2>(qcqq));
    qubs_st.insert(std::get<3>(qcqq));
    State s(qubs_st, dptr);

    QuantumCircuit qc = Grover(std::get<0>(qcqq), std::get<1>(qcqq), std::get<2>(qcqq), std::get<3>(qcqq), k);
    std::cerr << qc.decompose().decompose().get_qcr().s;
    #ifndef QISKIT_PROVIDER
        StateProvider exec(qc);
    #else
        QiskitProvider exec(qc);
    #endif
    
    Qubits qubs = qc.get_qubits();
    Qubits used_qubs = std::get<2>(qcqq);
    used_qubs.insert(std::get<3>(qcqq));
    Qubits anc_qubs{};
    for (auto x: qubs){
        if (std::find(used_qubs.begin(), used_qubs.end(), x) == used_qubs.end()){
            anc_qubs.insert(x);
        }
    }

    exec.state_evolve();

    State res = State(anc_qubs).conj() * exec.get_evolved_state();
    EXPECT_TRUE(compare(exec.get_evolved_state().conj() * exec.get_evolved_state(), Tensor{1})) << ERR_PREFIX 
                                << "Not normed " << Tensor{exec.get_evolved_state().conj() * exec.get_evolved_state()};
    EXPECT_TRUE(compare(res, s)) << ERR_PREFIX 
                                << "not_equal\n " << "theory : \n" << s << "result : \n" << exec.get_evolved_state();
    std::cerr << exec.get_evolved_state();
};


INSTANTIATE_TEST_SUITE_P(ComboValues, GroverTest,
                        Combine(Values(3,4,5),
                                // Values(std::vector<int>{0}),
                                Values(std::vector<int>{0}, std::vector<int>{0,1,2}),
                                Values(1,2,3)));



