#include "QuantumCircuit.h"
#include "qaoa.h"


std::pair<QuantumCircuit, ParameterVector> QAOA(const QUSO& quso, int layers){
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
                    qc.add_instruction(BaseInstr::PR(PauliString("ZZ", Qubits{i,j}), ExprPtr(new ParameterProd((quso.Q(i,j) + quso.Q(j,i)), alpha))));
                    // qc.add_instruction(BaseInstr::PR(PauliString("ZZ", Qubits{i,j}), ExprPtr(new ParameterConst(0))));
                }
            }
            if (quso.A(i) != 0){
                qc.add_instruction(BaseInstr::Rz(i, ExprPtr(new ParameterProd(quso.A(i), alpha))));
            }
        }
        for(int i=0; i<size; i++){
            qc.add_instruction(BaseInstr::Rx(i, ExprPtr(new ParameterExpr(beta))));
        }
    }
    return std::pair<QuantumCircuit, ParameterVector>(qc, pv);
}
HamDiag QUSO::to_diag_Ham(){
    DataPtr dptr(new Data(1 << size));
    for (int k=0; k<dptr->size(); k++){
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                if (((k>>i)&1) ^ ((k>>j)&1)){
                    (*dptr)[k] -= Q(i,j);
                }else{
                    (*dptr)[k] += Q(i,j);
                }
            }
            if (((k>>i)&1)){
                (*dptr)[k] -= A(i);
            }else{
                (*dptr)[k] += A(i);
            }
        }
    }
    return HamDiag{State(Qubits(size), dptr)};
}

HamOpSet QUSO::to_Ham(){
    DataPtr dptr(new Data{1,0,0,0,
                            0,-1,0,0,
                            0,0,-1,0,
                            0,0,0,1});
    HamOpSet Ham;
    DataType val=0;
    for (int i=0; i<size; i++){
        for (int j=i+1; j<size; j++){
            if (Q(i,j) + Q(j,i)!= 0){
                Ham.svec.push_back(Operator(Operator(Q(i,j) + Q(j,i))*Operator({i,j}, dptr)));
            }
        }

        val += Q(i,i);
            
        if (A(i) != 0){
            Ham.svec.push_back(Operator(Operator(A(i))*bm::Z(i)));
        }
    }
    Ham.svec.push_back(Operator(val));
    return Ham;
}
// Operator QUSO::to_Op(){
//     DataPtr dptr(new Data(1 << size*size));
//     for (int k=0; k<dptr->size(); k++){
//         for (int i=0; i<size; i++){
//             for (int j=0; j<size; j++){
//                 if (((k>>i)&1) ^ ((k>>j)&1)){
//                     (*dptr)[k] -= Q(i,j);
//                 }else{
//                     (*dptr)[k] += Q(i,j);
//                 }
//             }
//             if (((k>>i)&1)){
//                 (*dptr)[k] -= A(i);
//             }else{
//                 (*dptr)[k] += A(i);
//             }
//         }
//     }
//     return Operator(Qubits(size), dptr);
// }