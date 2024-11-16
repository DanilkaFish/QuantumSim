#include "inc/GateSimulator/unitary.h"
#include "inc/GateSimulator/simdata.h"

void NumSimProvider::I(const Qubits& qubs){
    static DataPtr dptr(new Data{0,1,
                                 1,0});
    state = Operator{qubs, dptr}*state;
}

void NumSimProvider::X(const Qubits& qubs){
    static DataPtr dptr{new Data{0,1,
                                 1,0}};
    state = Operator{qubs, dptr}*state;
}

void NumSimProvider::Y(const Qubits& qubs){
    static DataPtr dptr{new Data{0,{0,-1},
                                {0,1},0}};
    state = Operator{qubs, dptr}*state;
}

void NumSimProvider::Z(const Qubits& qubs){
    static DataPtr dptr{new Data{1,0,
                                 0,-1}};
    state = Operator{qubs, dptr}*state;
}

void NumSimProvider::S(const Qubits& qubs){
    static DataPtr dptr{new Data{1,0,
                                 0,{0,1}}};
    state = Operator{qubs, dptr}*state;
}

void NumSimProvider::Sdag(const Qubits& qubs){
    static DataPtr dptr{new Data{1,0,
                                 0,{0,-1}}};
    state = Operator{qubs, dptr}*state;
}

void NumSimProvider::CX(const Qubits& qubs){
    static DataPtr dptr{new Data{1,0,0,0,
                                 0,1,0,0,
                                 0,0,0,1,
                                 0,0,1,0}};
    state = Operator{qubs, dptr}*state;
}

const double A = 1.0/sqrt(2);

void NumSimProvider::H(const Qubits& qubs){
    static DataPtr dptr{new Data{A, A,
                                 A,-A}};
    state = Operator{qubs, dptr}*state;
}

void NumSimProvider::TOF(const Qubits& qubs){
    static DataPtr dptr{new Data{1,0,0,0,0,0,0,0,
                                 0,1,0,0,0,0,0,0,
                                 0,0,1,0,0,0,0,0,
                                 0,0,0,1,0,0,0,0,
                                 0,0,0,0,1,0,0,0,
                                 0,0,0,0,0,1,0,0,
                                 0,0,0,0,0,0,0,1,
                                 0,0,0,0,0,0,1,0}};
    state = Operator{qubs, dptr}*state;
}
