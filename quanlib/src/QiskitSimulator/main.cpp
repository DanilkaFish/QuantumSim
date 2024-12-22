#include "qiskit_provider.h"


int main() {
    QuantumCircuit qc;
    qc.add_instruction(BaseInstr::X({0}));
    qc.add_instruction(BaseInstr::X({2}));
    qc.add_instruction(BaseInstr::X({1}));
    // qc.add_instruction(BaseInstr::H(3));
    qc.add_instruction(BaseInstr::U({0,1}, DataPtr(new Data{1,0,0,0,
                                                            0,1,0,0,
                                                            0,0,0,1,
                                                            0,0,1,0})));
    QiskitProvider exec(qc);
    exec.state_evolve();
    std::cerr << exec.get_evolved_state();
}