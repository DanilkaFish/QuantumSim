#include "inc/QuantumCircuit/__init__.h"
#include "inc/GateSimulator/__init__.h"

int main(){
    QuantumCircuit qc;
    qc.add_instruction(BaseInstr::H(Qubit{1}));
    qc.add_instruction(BaseInstr::H(Qubit{0}));
    qc.add_instruction(BaseInstr::H(Qubit{3}));
    TensorProvider exec(qc);
    exec.run();
}