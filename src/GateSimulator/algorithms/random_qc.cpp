#include "inc/GateSimulator/algorithms/random_qc.h"
#include "Eigen/Eigen"
#include "inc/GateSimulator/unitary.h"
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
    QuantumCircuit qc(Qubits(this->n_qubits));
    for(int i=0; i< depth; i++){
        double n = ng->get_double(0, 1);
        if (n > p){
            Qubits qubs = gen_qubits(1);
            qc.add_instruction(InstructionPtr(new FixedUnitary(gen_op(qubs))));
        }else{
            Qubits qubs = gen_qubits(2);
            qc.add_instruction(InstructionPtr{new FixedUnitary(gen_op(qubs))});
        }
    }
    return qc;
}  

Operator QCGenerator::gen_op(Qubits qubs){
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
    return herm_to_un(Operator{qubs, dptr});
}

Qubits QCGenerator::gen_qubits(int n){
    Qubits qubits(n);

    int num;
    bool next;
    for(int i=0; i<n;){
        next = true;
        num = ng->get_int(0, n_qubits);
        for(int j=0; j<i; j++)
            if (qubits.qubs[j] == num) {
                next = false;
                break;
            }
        if (next){
            qubits.qubs[i] = num;
            i++;
        }
    }
    return qubits;
}
class Operator;

Operator herm_to_un(const Operator& op){
    int n = 1 << op.get_qubits().qubs.size();
    Eigen::MatrixXcd m(n, n);
    for (int i=0; i<n*n; i++){
        m(i / n, i % n) = op[i];
    }
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXcd> eigensolver(m);
    for (int i=0; i<n*n; i++){
        m(i / n, i % n) =  (i / n != i % n) ? 0 : std::exp(i::i* eigensolver.eigenvalues()[i/n]);
    }
    // HSMatrix u(this->n_qubits);
    DataPtr u{ new Data(n*n) };

    m = eigensolver.eigenvectors() * m * eigensolver.eigenvectors().adjoint();

    for (int i=0; i<n*n; i++){
        (*u)[i] = m(i / n, i % n);
    }
    return Operator(op.get_qubits(), u);
}