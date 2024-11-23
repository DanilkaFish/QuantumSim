#include "QuantumCircuit.h"

std::tuple<QuantumCircuit, Qubits, Qubit> Oracle(int n, std::vector<int>);

QuantumCircuit Grover(QuantumCircuit& oracle, Qubits main_qubits, Qubit trg,  int num_layers);