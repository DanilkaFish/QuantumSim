#ifndef _TENSORSPEC
#define _TENSORSPEC

#include "tensor.h"
#include <unordered_map>


class Operator: public Tensor{
public:
    using Tensor::Tensor;
    Operator(const Qubits& qubs): Tensor{Shape{qubs, qubs}}, qubs{qubs} {(*dptr)[0] = 1;}
    Operator(const Qubits& qubs, DataPtr dptr): Tensor{{qubs, qubs}, dptr}, qubs{qubs} { }
    Operator(const Qubits& qubs, const Data& data): Tensor{qubs, qubs, data}, qubs{qubs} { }
    const Qubits& get_qubits() const { return qubs;}
private:
    Qubits qubs;
};


class State: public Tensor{
public:
    using Tensor::Tensor;
    // State(const TensorProd<Operator, State>& tp, DataPtr dumptr);
    State(const Qubits& qubs): Tensor{{qubs, Qubits()}}, qubs{qubs} {(*dptr)[0] = 1;}
    State(const Qubits& qubs, DataPtr dptr): Tensor{{qubs, Qubits()}, dptr}, qubs{qubs} { }
    State(const Qubits& qubs, const Data& data): Tensor{qubs, Qubits(), data}, qubs{qubs} { }
    const Qubits& get_qubits() const { return qubs;}
private:
    Qubits qubs;
};


template<>
class TensorProd<Operator, State>: public Expression<TensorProd<Operator, State>>{
public:
    TensorProd(const Operator& exprl, const State& exprr): exprl{&exprl}, exprr{&exprr}, shape{exprr.get_shape()} { }
    Shape get_shape() const noexcept { return shape; }
    DataType operator[](int i) const{
        return 0;
    }

    Shape shape;
    const Operator *exprl;
    const State *exprr;
};



std::ostream& operator<<(std::ostream& os, const State& s);

template<typename Operator, typename State>
TensorProd<Operator, State> operator*(const Operator &e1, const State &e2)
{
    return TensorProd<Operator, State>(e1, e2);
}

#endif