#ifndef _RANDOM_QC
#define _RANDOM_QC

#include "code/QuanCirc/inc/random/genfactory.h"
#include "quantumcircuit.h"

constexpr double L = 100;

class QCGenerator{
public:
    QCGenerator(int _depth, int _n_qubits, GeneratorKind type, int seed=18);
    ~QCGenerator();

    QuantumCircuit   get_qc(double);
    tensor::HSMatrix get_n_HSMatrix(int n);
    IntArr           get_n_qubits(int n);
    
private:
    int              n_qubits;
    int              depth;
    BaseGenerator*   ng;
};
#endif
    