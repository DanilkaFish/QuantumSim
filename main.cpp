#include <iostream>
#include "pybind.h"

int main() {
    QuantumCircuit qc;
    qc.add_instruction(BaseInstr::I({0}));
    qc.add_instruction(BaseInstr::H({2}));
    qc.add_instruction(BaseInstr::H({1}));
    // qc.add_instruction(BaseInstr::H(3));
    
    QiskitProvider exec(qc);
    // exec.state_evolve();
    // exec.qiskit_state_evolve();
}