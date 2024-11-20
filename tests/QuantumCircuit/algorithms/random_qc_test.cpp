// #include "test/QuanCirc/inc/algorithms/grover_test.h"

#include "tests/QuantumCircuit/algorithms/random_qc_test.h"
#include "inc/GateSimulator/__init__.h"
#include <bits/stdc++.h>
#include <string>

DataType conv(const State& st){
    DataType d;
    for (int i = 0; i < st.size(); i++){
        d += st[i] * double(i)/double(i+2);
    }
    return d;
}


TEST(SimpleTest, TestRandomQC){
    QCGenerator qg(62, 5, GeneratorKind::LCG);
    QuantumCircuit qc = qg.get_qc(0.64);
    std::cout << qc.get_qcr().s;
    TensorProvider exec(qc);
    std::cout << exec.state;
    exec.run();
    Tensor tot = exec.state.conj()*exec.state;
    DataType res = conv(exec.state);
    DataType exp = {0.798328, -0.599588};
    EXPECT_TRUE(compare(tot,Tensor{1})) << ERR_PREFIX 
                    << "Differnt state array values on " << exec.state.get_shape();
    ASSERT_NEAR(std::abs(res - exp), 0, 0.000001) << ERR_PREFIX 
                        << "Differnt state array values on " << res;
}