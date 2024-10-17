#ifndef _RANDOM_QC
#define _RANDOM_QC

#include "random/genfactory.h"
#include "quantumcircuit.h"

constexpr double L = 100;

class QCGenerator{
public:
    QCGenerator(int _depth, int _n_qubits, GeneratorKind type, int seed=18);
    ~QCGenerator();

    QuantumCircuit  get_qc(double);
    tensor::Unitary get_n_unitary(int n);
    IntArr          get_n_qubits(int n);
    
private:
    int             n_qubits;
    int             depth;
    BaseGenerator*  ng;
};
#endif
    