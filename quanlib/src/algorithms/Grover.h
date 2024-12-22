#include "QuantumCircuit.h"

std::tuple<QuantumCircuit,QuantumCircuit, Qubits, Qubit> Oracle(int n, std::vector<int>);

QuantumCircuit Grover(QuantumCircuit& oracle, QuantumCircuit& diff_op, Qubits main_qubits, Qubit trg,  int num_layers);