// #include "inc/Tensors/new_shape.h"
// #include "inc/Tensors/new_tensorexpr.h"
#include "inc/Tensors/new_tensor.h"


int main(){
    DataPtr dptr( new Data{1,1,1,1,1,1,1,1});
    Shape shr(Qubits({0}), Qubits({}));
    Shape shl(Qubits({}), Qubits({0,1,2}));
    // Shape res = prod(shl, shr);
    Tensor X(shl, DataPtr(new Data(1,1)));
    Tensor X2(shr, dptr);
    std::cerr << X;
    std::cerr << X2;
    Tensor I = X*X2;
    std::cerr << I;
    // std::cout << DataType(0,0) +DataType(1,0)* DataType(0,0);
    // mask t(8);
    // int x = t.compress(8);
    // QuantumCircuit qc{};
    // qc.add_instruction(BaseInstr::X(1));
    // qc.add_instruction(BaseInstr::X(1));
    // qc.add_instruction(BaseInstr::X(1));
    // qc.add_instruction(BaseInstr::X(1));
    // auto qc = Oracle(5, std::vector<int>{2,3,4});
}
