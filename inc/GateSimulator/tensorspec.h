#ifndef _TENSORSPEC
#define _TENSORSPEC

#include "inc/Tensors/__init__.h"


class State: public Tensor{
public:
    using Tensor::Tensor;
    State(const Qubits& qubs): Tensor{{qubs,{}}}, qubs{qubs} {(*dptr)[0] = 1;}
    State(const Qubits& qubs, DataPtr dptr): Tensor{{qubs, {}}, dptr}, qubs{qubs} { }
    State(const Qubits& qubs, const Data& data): Tensor{{qubs, {}}, data}, qubs{qubs} { }
    Qubits get_qubits() const { return qubs;}
private:
    Qubits qubs;
};


class Operator: public Tensor{
public:
    using Tensor::Tensor;
    Operator(const Qubits& qubs): Tensor{{qubs, qubs}}, qubs{qubs} {(*dptr)[0] = 1;}
    Operator(const Qubits& qubs, DataPtr dptr): Tensor{{qubs, qubs}, dptr}, qubs{qubs} { }
    const Qubits& get_qubits() const { return qubs;}
private:
    Qubits qubs;
};

#endif