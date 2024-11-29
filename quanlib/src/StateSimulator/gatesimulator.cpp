#include "unitary.h"
#include "tensorprovider.h"
#include "gatesim.h"


Operator bm::I(const Qubits& qubs){
    DataPtr dptr(new Data(1<<2*qubs.size()));
    for(int i=0; 1 < 1 << qubs.size(); i++){
        (*dptr)[i*i + i] = 1;
    }
    return Operator(qubs, dptr);
}

Operator bm::I(Qubit qub){
    static DataPtr dptr{new Data{1,0,
                                 0,1}};
    return Operator({qub}, dptr);
}

Operator bm::X(Qubit qub){
    static DataPtr dptr(new Data{0,1,
                                 1,0});
    return Operator({qub}, dptr);
}

Operator bm::Y(Qubit qub){
    static DataPtr dptr{new Data{0,{0,-1},
                                {0,1},0}};
    return Operator({qub}, dptr);
}

Operator bm::Z(Qubit qub){
    static DataPtr dptr{new Data{1,0,
                                 0,-1}};
    return Operator({qub}, dptr);
}

Operator bm::S(Qubit qub){
    static DataPtr dptr{new Data{1,0,
                                 0,{0,1}}};
    return Operator({qub}, dptr);
}

Operator bm::Sdag(Qubit qub){
    static DataPtr dptr{new Data{1,0,
                                 0,{0,-1}}};
    return Operator({qub}, dptr);
}

Operator bm::CX(Qubit trg, Qubit ctrl){
    static DataPtr dptr{new Data{1,0,0,0,
                                 0,1,0,0,
                                 0,0,0,1,
                                 0,0,1,0}};
    static DataPtr dptrinv{new Data{1,0,0,0,
                                 0,0,0,1,
                                 0,0,1,0,
                                 0,1,0,0}};
    if (trg > ctrl){
        return Operator({trg, ctrl}, dptr);
    }else{
        return Operator({trg, ctrl}, dptrinv);
    }
}

const double A = 1.0/sqrt(2);

Operator bm::H(Qubit qub){
    static DataPtr dptr{new Data{A, A,
                                 A,-A}};
    return Operator({qub}, dptr);
}

Operator bm::TOF(Qubit ctrl1, Qubit ctrl2, Qubit trg ){
    static Data data{1,0,0,0,0,0,0,0,
                    0,1,0,0,0,0,0,0,
                    0,0,1,0,0,0,0,0,
                    0,0,0,1,0,0,0,0,
                    0,0,0,0,1,0,0,0,
                    0,0,0,0,0,1,0,0,
                    0,0,0,0,0,0,0,1,
                    0,0,0,0,0,0,1,0};
    return Operator({ctrl1, ctrl2, trg}, data);
}



Operator bm::PR(const PauliString& pauli, double theta){
    Operator T;
    for(int i=0; i<pauli.size(); i++){
        switch (tolower(pauli.get_ch(i)))
        {
        case 'x':
            T = T*bm::X(pauli.get_qn(i));
            break;
        case 'y':
            T = T*bm::Y(pauli.get_qn(i));
            break;
        case 'z':
            T = T*bm::Z(pauli.get_qn(i));
            break;
        case 'i':
            T = T*bm::I(pauli.get_qn(i));
            break;
        default:
            std::cerr << "WTF char in pualistring";
        }
    }
    return Tensor{cos(theta/2)}*bm::I(pauli.get_qubs()) + Tensor{sin(theta/2)}*T;
}

void TensorProvider::I(const Qubits& qubs){
    inplace_evolve(bm::I(qubs[0]));
}
void TensorProvider::X(const Qubits& qubs){
    inplace_evolve(bm::X(qubs[0]));
}
void TensorProvider::Y(const Qubits& qubs){
    inplace_evolve(bm::Y(qubs[0]));
}
void TensorProvider::Z(const Qubits& qubs){
    inplace_evolve(bm::Z(qubs[0]));
}
void TensorProvider::H(const Qubits& qubs){
    inplace_evolve(bm::H(qubs[0]));
}
void TensorProvider::S(const Qubits& qubs){
    inplace_evolve(bm::S(qubs[0]));
}
void TensorProvider::Sdag(const Qubits& qubs){
    inplace_evolve(bm::Sdag(qubs[0]));
}
void TensorProvider::CX(const Qubits& qubs){
    inplace_evolve(bm::CX(qubs[0], qubs[1]));
}
void TensorProvider::TOF(const Qubits& qubs){
    inplace_evolve(bm::TOF(qubs[0], qubs[1], qubs[2]));
}

// void TensorProvider::U1(const Qubits& qubs, DataPtr dptr){
//     inplace_evolve(Operator{qubs, dptr});
// }
// void TensorProvider::U2(const Qubits& qubs, DataPtr dptr){
//     inplace_evolve(Operator{qubs, dptr});
// }
void TensorProvider::U(const Qubits& qubs, DataPtr dptr){
    inplace_evolve(Operator{qubs, dptr});
}

inline void _fill(int init, int finit, int dif, const Data& l, Data& r, const mask& buffer_mask, const std::vector<int>& expand){
    int buffer_i;
    DataType val;
    // int cache_size = 1 << 4; 
    std::vector<DataType> bufferr(dif);
    for (int i=init; i<finit; i++){
        buffer_i = buffer_mask.expand(i);

        for(int up_index=0; up_index<dif; up_index++){
            bufferr[up_index] = r[buffer_i + expand[up_index]];
        }

        for(int up_index=0; up_index<dif; up_index++){
            val = 0;
            for (int down_index=0; down_index<dif; down_index++){
                val += l[up_index*dif + down_index] * bufferr[down_index];
            }
            r[buffer_i + expand[up_index]] = val;
        }
    }
}; 

void TensorProvider::inplace_evolve(const Operator& op){
    mask buffer_mask(state.get_shape().pos_up.compress(state.get_shape().pos_up.m) ^ 
                        state.get_shape().pos_up.compress(op.get_shape().pos_down.m));
    int dif = 1 << op.get_qubits().size();
    std::vector<int> expand;
    mask op_mask(state.get_shape().pos_up.compress(op.get_shape().pos_down.m));
    for (int j=0; j < (dif); j++){
        expand.push_back(op_mask.expand(j));
    }
    // _fill(0, 
    //                                     state.get_dptr()->size() / dif, 
    //                                     dif,
    //                                     std::cref(*(op.get_dptr().get())), 
    //                                     std::ref(*(state.get_dptr().get())),
    //                                     std::cref(buffer_mask), 
    //                                     std::cref(expand));
    std::vector<std::thread> threads(num_thread);
    int size = state.get_dptr()->size() / dif / num_thread;
    for (int j=0; j<num_thread; j++){
        threads[j] = std::thread(_fill, size*j, 
                                        size*(j+1), 
                                        dif,
                                        std::cref(*(op.get_dptr().get())), 
                                        std::ref(*(state.get_dptr().get())),
                                        std::cref(buffer_mask), 
                                        std::cref(expand));
    }
    for (int j=0; j<num_thread; j++){
        threads[j].join();
    }
}

std::ostream& operator<<(std::ostream& os, const State& s){
    for(int i=0; i<s.size(); i++){
        if (s[i].imag() != 0 || s[i].real() != 0){
            os << '+' << s[i] << "|";
            int j = i;
            for(int pos=0; pos<s.get_shape().size(); pos++){
                os << (j & 1);
                j = j >> 1;
            }   
            os << "> ";
        }
    }
    return os << "\n";
}

