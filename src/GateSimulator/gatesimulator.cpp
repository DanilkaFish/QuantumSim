#include "inc/GateSimulator/unitary.h"
#include "inc/GateSimulator/tensorprovider.h"

void TensorProvider::I(const Qubits& qubs){
    static DataPtr dptr(new Data{0,1,
                                 1,0});
    state = Operator{qubs, dptr}*state;
}

void TensorProvider::X(const Qubits& qubs){
    static DataPtr dptr{new Data{0,1,
                                 1,0}};
    state = Operator{qubs, dptr}*state;
}

void TensorProvider::Y(const Qubits& qubs){
    static DataPtr dptr{new Data{0,{0,-1},
                                {0,1},0}};
    state = Operator{qubs, dptr}*state;
}

void TensorProvider::Z(const Qubits& qubs){
    static DataPtr dptr{new Data{1,0,
                                 0,-1}};
    state = Operator{qubs, dptr}*state;
}

void TensorProvider::S(const Qubits& qubs){
    static DataPtr dptr{new Data{1,0,
                                 0,{0,1}}};
    state = Operator{qubs, dptr}*state;
}

void TensorProvider::Sdag(const Qubits& qubs){
    static DataPtr dptr{new Data{1,0,
                                 0,{0,-1}}};
    state = Operator{qubs, dptr}*state;
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
        state = Operator{qubs, dptr}*state;
    }else{
        state = Operator{qubs, dptrinv}*state;
    }

}

const double A = 1.0/sqrt(2);

void TensorProvider::H(const Qubits& qubs){
    static DataPtr dptr{new Data{A, A,
                                 A,-A}};
    state = Operator{qubs, dptr}*state;
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
    state = Operator{qubs, data}*state;
}

void TensorProvider::U1(const Qubits& qubs, DataPtr dptr){
    state = Operator{qubs, dptr}*state;
}
void TensorProvider::U2(const Qubits& qubs, DataPtr dptr){
    state = Operator{qubs, dptr}*state;
}  
void TensorProvider::U(const Qubits& qubs, DataPtr dptr){
    state = Operator{qubs, dptr}*state;
} 