#include "code/QuanCirc/inc/algorithms/random_qc.h"

QCGenerator::QCGenerator(int _depth, int _n_qubits, GeneratorKind type, int seed){
    ng = RandGeneratorFactory::CreateRandGenerator(seed, type);
    depth = _depth;
    n_qubits = _n_qubits;
};

QCGenerator::~QCGenerator(){
    delete ng;
}

QuantumCircuit QCGenerator::get_qc(double p=0.64){
    QuantumCircuit qc(n_qubits);
    for(int i=0; i< depth; i++){
        double n = ng->get_double(0, 1);
        if (n > p){
            auto n_qubits = get_n_qubits(1);
            qc.add_instruction(get_n_HSMatrix(1), n_qubits);
        }else{
            auto n_qubits = get_n_qubits(2);
            qc.add_instruction(get_n_HSMatrix(2), n_qubits);
        }
    }
    return qc;
}  

tensor::HSMatrix QCGenerator::get_n_HSMatrix(int n){
    int size = (1 << n);
    ComplexArr vec(size*size);
    for(int i=0; i < size; i++){
        for(int j=i; j < size; j++){
            if (i == j){
                vec[i*size + i] = ng->get_double(-L,L);
            }else{
                vec[i*size + j] = ng->get_double(-L,L);
                vec[i*size + j] += tensor::i * ng->get_double(-L,L);
                vec[j*size + i] = vec[i*size + j].real() - tensor::i * vec[i*size + j].imag();
            }
        }
    }
    return tensor::HSMatrix(vec).to_unitary();
}

IntArr QCGenerator::get_n_qubits(int n){
    IntArr qubits(n);
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