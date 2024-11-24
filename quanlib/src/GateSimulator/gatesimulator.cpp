#include "unitary.h"
#include "tensorprovider.h"

void TensorProvider::I(const Qubits& qubs){
    static DataPtr dptr(new Data{0,1,
                                 1,0});
    inplace_evolve(Operator{qubs, dptr});
}

void TensorProvider::X(const Qubits& qubs){
    static DataPtr dptr{new Data{0,1,
                                 1,0}};
    inplace_evolve(Operator{qubs, dptr});
}

void TensorProvider::Y(const Qubits& qubs){
    static DataPtr dptr{new Data{0,{0,-1},
                                {0,1},0}};
    inplace_evolve(Operator{qubs, dptr});
}

void TensorProvider::Z(const Qubits& qubs){
    static DataPtr dptr{new Data{1,0,
                                 0,-1}};
    inplace_evolve(Operator{qubs, dptr});
}

void TensorProvider::S(const Qubits& qubs){
    static DataPtr dptr{new Data{1,0,
                                 0,{0,1}}};
    inplace_evolve(Operator{qubs, dptr});
}

void TensorProvider::Sdag(const Qubits& qubs){
    static DataPtr dptr{new Data{1,0,
                                 0,{0,-1}}};
    inplace_evolve(Operator{qubs, dptr});
}

void TensorProvider::CX(const Qubits& qubs){
    static DataPtr dptr{new Data{1,0,0,0,
                                 0,1,0,0,
                                 0,0,0,1,
                                 0,0,1,0}};
    static DataPtr dptrinv{new Data{1,0,0,0,
                                 0,0,0,1,
                                 0,0,1,0,
                                 0,1,0,0}};
    if (qubs[0] > qubs[1]){
        inplace_evolve(Operator{qubs, dptr});
    }else{
        inplace_evolve(Operator{qubs, dptrinv});
    }

}

const double A = 1.0/sqrt(2);

void TensorProvider::H(const Qubits& qubs){
    static DataPtr dptr{new Data{A, A,
                                 A,-A}};
    inplace_evolve(Operator{qubs, dptr});
}

void TensorProvider::TOF(const Qubits& qubs){
    static Data data{1,0,0,0,0,0,0,0,
                    0,1,0,0,0,0,0,0,
                    0,0,1,0,0,0,0,0,
                    0,0,0,1,0,0,0,0,
                    0,0,0,0,1,0,0,0,
                    0,0,0,0,0,1,0,0,
                    0,0,0,0,0,0,0,1,
                    0,0,0,0,0,0,1,0};
    inplace_evolve(Operator{qubs, data});
}

void TensorProvider::U1(const Qubits& qubs, DataPtr dptr){
    inplace_evolve(Operator{qubs, dptr});
}
void TensorProvider::U2(const Qubits& qubs, DataPtr dptr){
    inplace_evolve(Operator{qubs, dptr});
}  
void TensorProvider::U(const Qubits& qubs, DataPtr dptr){
    inplace_evolve(Operator{qubs, dptr});
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


