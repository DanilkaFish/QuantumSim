#include "code/QuanCirc/inc/error.h"


void error_qubits_range(IntArr qubits, int n_qubits){
    std::string s = "qubits [" ;
    for(auto q: qubits) s += std::to_string(q) + ",";
    s += "] is not in range (0, " + std::to_string(n_qubits - 1) + ')';
    throw std::runtime_error(s);
}

void error_qubits_coinc(IntArr qubits){
    std::string s = "qubits [" ;
    for(auto q: qubits) s += std::to_string(q) + ",";
    s += "] have the coincidence;";
    throw std::runtime_error(s);
}

void tensor_error(int l){
    throw std::runtime_error("array " + std::to_string(l) +" size is not power of 2");
}

void custom_error(const std::string& s){
    throw std::runtime_error(s);
}