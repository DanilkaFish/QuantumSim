#ifndef _RANDOM_QC
#define _RANDOM_QC

#include "genfactory.h"
#include "QuantumCircuit.h"

constexpr double L = 100;

class QCGenerator{
public:
    QCGenerator(int _depth, int _n_qubits, GeneratorKind type, int seed=18);
    ~QCGenerator();
    QuantumCircuit   get_qc(double);
    // QuantumCircuit   get_qc(double=0.64);

private:
    DataPtr          gen_op(Qubits qubs);
    Qubits           gen_qubits(int n);
    int              n_qubits;
    int              depth;
    BaseGenerator*   ng;
};

DataPtr herm_to_un(const DataPtr& op, int n);

#endif
    