#include "qulacssim.h"

void QulacsProvider::I(const Qubits& qubs){
    inplace_evolve(qulacs::create_quantum_gate_from_string("I " + std::string(qubs[0].num)));
}
void QulacsProvider::X(const Qubits& qubs){
    inplace_evolve(qulacs::create_quantum_gate_from_string("X " + std::string(qubs[0].num)));
}
void QulacsProvider::Y(const Qubits& qubs){
    inplace_evolve(qulacs::create_quantum_gate_from_string("Y " + std::string(qubs[0].num)));
}
void QulacsProvider::Z(const Qubits& qubs){
    inplace_evolve(qulacs::create_quantum_gate_from_string("Z " + std::string(qubs[0].num)));
}
void QulacsProvider::H(const Qubits& qubs){
    inplace_evolve(qulacs::create_quantum_gate_from_string("H " + std::string(qubs[0].num)));
}
void QulacsProvider::S(const Qubits& qubs){
    inplace_evolve(qulacs::create_quantum_gate_from_string("S " + std::string(qubs[0].num)));
}
void QulacsProvider::Sdag(const Qubits& qubs){
    inplace_evolve(qulacs::create_quantum_gate_from_string("Sdag " + std::string(qubs[0].num)));
}
void QulacsProvider::CX(const Qubits& qubs){
    inplace_evolve(qulacs::create_quantum_gate_from_string("CX " + std::string(qubs[0].num) + " " + std::string(qubs[1].num) ));
}
void QulacsProvider::TOF(const Qubits& qubs){
    inplace_evolve(std::string(qubs[0].num) );
}

// void QulacsProvider::U1(const Qubits& qubs, DataPtr dptr){
//     inplace_evolve(Operator{qubs, dptr});
// }
// void QulacsProvider::U2(const Qubits& qubs, DataPtr dptr){
//     inplace_evolve(Operator{qubs, dptr});
// }
// void QulacsProvider::U(const Qubits& qubs, DataPtr dptr){
//     inplace_evolve(Operator{qubs, dptr});
// }