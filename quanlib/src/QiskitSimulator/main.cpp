#include "pybind.h"


int main() {
    QuantumCircuit qc;
    qc.add_instruction(BaseInstr::X({0}));
    qc.add_instruction(BaseInstr::X({2}));
    qc.add_instruction(BaseInstr::X({1}));
    // qc.add_instruction(BaseInstr::H(3));
    // qc.add_instruction(BaseInstr::TOF({0},{1},{2}));
    QiskitProvider exec(qc);
    exec.state_evolve();
    std::cerr << exec.get_state_evolve();
}