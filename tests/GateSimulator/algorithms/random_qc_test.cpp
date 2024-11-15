// #include "test/QuanCirc/inc/algorithms/grover_test.h"

#include "tests/GateSimulator/algorithms/random_qc_test.h"
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
    PureSim exec(qc);
    std::cout << exec.sdptr->state;
    exec.run();
    DataType res = conv(exec.sdptr->state);
    DataType exp = {0.798328, -0.599588};
    EXPECT_TRUE(compare(exec.sdptr->state.conj()*exec.sdptr->state,Tensor{1})) << ERR_PREFIX 
                    << "Differnt state array values on ";
    ASSERT_NEAR(std::abs(res - exp), 0, 0.000001) << ERR_PREFIX 
                        << "Differnt state array values on " << res;
}