#include "QuantumCircuit.h"
#include "qaoa.h"

QuantumCircuit QAOA(std::vector<std::vector<int>>& C, std::vector<int>& X, int layers){
    QuantumCircuit circ(X.size());
    return circ;
}


std::pair<QuantumCircuit, ParameterVector> QAOA(QUSO quso, int layers=1){
    ParameterVector pv;
    QuantumCircuit qc;
    int size = quso.get_size();
    for (int i=0; i< size; i++){
        qc.add_instruction(BaseInstr::H(i));
    }

    for(int k=0; k<layers; k++){
        ParameterPtr alpha = pv.gen_next();
        ParameterPtr beta = pv.gen_next();
        for(int i=0; i<size; i++){
            for(int j=i+1; j<size; j++){
                if (quso.Q(i,j) + quso.Q(j,i) != 0){
                    qc.add_instruction(BaseInstr::PR(PauliString("ZZ", Qubits{i,j}), ParameterProd(quso.Q(i,j) + quso.Q(j,i), alpha)));
                }
            }
            if (quso.A(i) != 0){
                qc.add_instruction(BaseInstr::Rz(i, ParameterProd(quso.A(i), alpha)));
            }
        }
        for(int i=0; i<size; i++){
            qc.add_instruction(BaseInstr::Rx(i, ParameterExpr(beta)));
        }
    }
}