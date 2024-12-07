// #include "test/QuanCirc/inc/algorithms/grover_test.h"

#include "random_qc_test.h"
#include "state_evolve.h"
#include <bits/stdc++.h>
#include <string>

DataType conv(const State& st){
    DataType d=0;
    Qubits qubs;
    int nu = st.get_shape().nu;
    int nd = st.get_shape().nd;
    std::map<Qubit, int> posup;
    std::map<Qubit, int> posdown;
    for(int i=0; i < nu; i++){
        posup[Qubit(i)] = nu - 1 - i;
    }
    for(int i=0; i < nd; i++){
        posup[Qubit(i)] = nd - 1 - i;
    }
    for (int i = 0; i < st.size(); i++){
        // d += st[index_shape_change(i, posup, posdown)] * double(i + 1)/double(i + 2);
        d += st[i] * double(i + 1)/double(i + 2);
    }
    return d;
}


TEST(SimpleTest, TestRandomQC){
    QCGenerator qg(40, 5, GeneratorKind::LCG);
    QuantumCircuit qc = qg.get_qc(0.6);
    // std::cout << qc.get_qcr().s;
    StateProvider exec(qc);
    exec.state_evolve();
    // std::cout << exec.get_evolved_state();
    Tensor tot = exec.get_evolved_state().conj()*exec.get_evolved_state();
    DataType res = conv(exec.get_evolved_state());
    DataType exp = {0.798328, -0.599588};
    std::cerr << exec.get_evolved_state();
    std::cerr << qc.get_qcr().s;
    EXPECT_TRUE(compare(tot,Tensor{1})) << ERR_PREFIX 
                    << "Differnt state array values on " << exec.get_evolved_state().get_shape();
    ASSERT_NEAR(std::abs(res - exp), 0, 0.000001) << ERR_PREFIX 
                        << "Differnt state array values on " << res;
}