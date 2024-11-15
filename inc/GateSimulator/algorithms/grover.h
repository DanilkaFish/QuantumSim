#include "inc/QuantumCircuit/quantumcircuit.h"

QuantumCircuit Oracle(std::vector<int>);

QuantumCircuit Grover(QuantumCircuit& oracle, int n, int _k);