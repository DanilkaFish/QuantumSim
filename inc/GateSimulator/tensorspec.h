#ifndef _TENSORSPEC
#define _TENSORSPEC

#include "inc/Tensors/__init__.h"


class State: public Tensor{
public:
    using Tensor::Tensor;
    State(const Qubits& qubs): Tensor{{qubs,{}}} {(*dptr)[0] = 1;}
    State(const Qubits& qubs, DataPtr dptr): Tensor{{qubs, {}}, dptr} { }
    State(const Qubits& qubs, const Data& data): Tensor{{qubs, {}}, data} { }
};


class Operator: public Tensor{
public:
    using Tensor::Tensor;
    Operator(const Qubits& qubs): Tensor{{qubs, qubs}} {(*dptr)[0] = 1;}
    Operator(const Qubits& qubs, DataPtr dptr): Tensor{{qubs, qubs}, dptr} { }
};

#endif