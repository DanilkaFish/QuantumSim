#ifndef _RANDOM_QC
#define _RANDOM_QC

#include "inc/random/genfactory.h"
#include "inc/QuantumCircuit/quantumcircuit.h"
#include "inc/GateSimulator/tensorspec.h"

constexpr double L = 100;

class QCGenerator{
public:
    QCGenerator(int _depth, int _n_qubits, GeneratorKind type, int seed=18);
    ~QCGenerator();
    QuantumCircuit   get_qc(double);
    // QuantumCircuit   get_qc(double=0.64);

private:
    Operator         gen_op(Qubits qubs);
    Qubits           gen_qubits(int n);
    int              n_qubits;
    int              depth;
    BaseGenerator*   ng;
};

Operator herm_to_un(const Operator& op);

#endif
    