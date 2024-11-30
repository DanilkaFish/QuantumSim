#ifndef _TENSORSPEC
#define _TENSORSPEC

#include "inc/Tensors/__init__.h"


class State: public Tensor{
public:
    using Tensor::Tensor;
    State(const Qubits& qubs): Tensor{{qubs, Qubits()}}, qubs{qubs} {(*dptr)[0] = 1;}
    State(const Qubits& qubs, DataPtr dptr): Tensor{{qubs, Qubits()}, dptr}, qubs{qubs} { }
    State(const Qubits& qubs, const Data& data): Tensor{qubs, Qubits(), data}, qubs{qubs} { }
    const Qubits& get_qubits() const { return qubs;}
private:
    Qubits qubs;
};


class Operator: public Tensor{
public:
    using Tensor::Tensor;
    Operator(const Qubits& qubs): Tensor{{qubs, qubs}}, qubs{qubs} {(*dptr)[0] = 1;}
    Operator(const Qubits& qubs, DataPtr dptr): Tensor{{qubs, qubs}, dptr}, qubs{qubs} { }
    Operator(const Qubits& qubs, const Data& data): Tensor{qubs, qubs, data}, qubs{qubs} { }
    const Qubits& get_qubits() const { return qubs;}
private:
    Qubits qubs;
};


template<>
class TensorProd<Operator, State>: public Expression<TensorProd<Operator, State>>{
public:
    TensorProd(const Operator& exprl, const State& exprr): exprl{&exprl}, exprr{&exprr}, shape{exprr.get_shape()} { init(); }
    Shape get_shape() const noexcept { return shape; }
    DataType operator[](int i) const{
        // int id = i & ( (1 << shape.nd) - 1);
        // int iu = (i - id) >> shape.nd;
        int ir = i&(~op_mask.m);
        int il = op_mask.compress(i) << num_inter;
        DataType val=0;
        for (int j=0; j < (dif); j++){
            val += (*exprl)[il + j] * 
                   (*exprr)[ir + op_mask.expand(j)];
                //    (*exprr)[ir + j];
        }
        return val;
    }
    void init(){
        op_mask = exprl->get_shape().pos_down;
        num_inter = exprl->get_qubits().size();
        dif = 1 << num_inter;
    }

private:
    Shape shape;
    const Operator *exprl;
    const State *exprr;
    mask op_mask;
    int num_inter;
    int dif;
};

std::ostream& operator<<(std::ostream& os, const State& s);

template<typename Operator, typename State>
TensorProd<Operator, State> operator*(const Operator &e1, const State &e2)
{
	return TensorProd<Operator, State>(e1, e2);
}
#endif