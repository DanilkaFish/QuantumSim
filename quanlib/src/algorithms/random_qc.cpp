#include "random_qc.h"
#include "Eigen"
// #include <numeric>
// #include <complex>


QCGenerator::QCGenerator(int _depth, int _n_qubits, GeneratorKind type, int seed){
    ng = RandGeneratorFactory::CreateRandGenerator(seed, type);
    depth = _depth;
    n_qubits = _n_qubits;
};

QCGenerator::~QCGenerator(){
    delete ng;
}

QuantumCircuit QCGenerator::get_qc(double p=0.64){
    QuantumCircuit qc;
    for(int i=0; i< depth; i++){
        double n = ng->get_double(0, 1);
        if (n > p){
            Qubits qubs = gen_qubits(1);
            qc.add_instruction(BaseInstr::U(qubs, gen_op(qubs)));
        }else{
            Qubits qubs = gen_qubits(2);
            qc.add_instruction(BaseInstr::U(qubs, gen_op(qubs)));
        }
    }
    return qc;
}  

DataPtr QCGenerator::gen_op(Qubits qubs){
    int size = (1 << qubs.size());
    DataPtr dptr{ new Data(size*size)};
    for(int i=0; i < size; i++){
        for(int j=i; j < size; j++){
            if (i == j){
                (*dptr)[i*size + i] = ng->get_double(-L,L);
            }else{
                (*dptr)[i*size + j] = ng->get_double(-L,L);
                (*dptr)[i*size + j] += i::i * ng->get_double(-L,L);
                (*dptr)[j*size + i] = (*dptr)[i*size + j].real() - i::i * (*dptr)[i*size + j].imag();
            }
        }
    }
    return herm_to_un(dptr, size);
}

Qubits QCGenerator::gen_qubits(int n){
    Qubits qubits(n);

    int num;
    bool next;
    for(int i=0; i<n;){
        next = true;
        num = ng->get_int(0, n_qubits);
        for(int j=0; j<i; j++)
            if (qubits[j] == num) {
                next = false;
                break;
            }
        if (next){
            qubits[i] = num;
            i++;
        }
    }
    return qubits;
}

class Operator;

DataPtr herm_to_un(const DataPtr& op, int n){
    Eigen::MatrixXcd m(n, n);
    for (int i=0; i<n*n; i++){
        m(i / n, i % n) = (*op)[i];
    }
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXcd> eigensolver(m);
    for (int i=0; i<n*n; i++){
        m(i / n, i % n) =  (i / n != i % n) ? 0 : std::exp(i::i* eigensolver.eigenvalues()[i/n]);
    }
    // HSMatrix u(this->n_qubits);
    DataPtr u{ new Data(n*n) };

    m = eigensolver.eigenvectors() * m * eigensolver.eigenvectors().adjoint();
    std::cerr << m;
    for (int i=0; i<n*n; i++){
        (*u)[i] = m(i / n, i % n);
    }
    return u;
}