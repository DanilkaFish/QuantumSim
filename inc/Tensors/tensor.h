#ifndef _TENSOR
#define _TENSOR

#include <generator>
#include "shape.h"
#include "stddata.h"
#include "bin_utils.h"



class Tensor{
public:
    Tensor(const Shape& sh): shape{sh} {}
    const Shape& get_shape() const { return shape; }
    virtual const DataType& operator[](Int i) const;
    void convolution(Tensor& T, const Qubits& qubs) {
        this->shape.to_conv(qubs);
    };

    void convolution(Tensor& T) {
        // T.set_shape(Shape{shape});
        for (int i=0; i < (1<<shape.size()); i++){
            for (int j=0; j < (1 << shape.get_qtype(QType::cdown).size()); j++){
                T[i] += (*this)[Transform::add_to_conv_shape(i,j, T.get_shape(), this->shape)];
            }
        }
    }

protected:
    virtual DataType& operator[](Int i);
    Data data;
    Int pos; 
    Shape shape;
};


class TensorProd: public Tensor{
public:
    TensorProd(Tensor& T1, Tensor& T2): T1{T1}, T2{T2}, Tensor{sum_shape(T1.get_shape(), T2.get_shape())}{ 
        if (this->shape.get_qtype(QType::cdown).size() + this->shape.get_qtype(QType::cup).size() != 0){
            // TODO
            std::cerr << "TensorProd is only for non intersected tensors";
        }
    }

    virtual const DataType& operator[](Int id) const{
        return T1[Transform::to_sub_shape(id, shape, T1.get_shape())] * 
               T2[Transform::to_sub_shape(id, shape, T2.get_shape())];
    }
    
private:
    Tensor T1;
    Tensor T2;
};

class TensorSum: public Tensor{

};

Tensor operator*(Tensor& Tl, Tensor& Tr){

    std::array<QType, 2> qta{{QType::up, QType::down}};
    bool is_intersect=false;
    Shape shl{Tl.get_shape()};
    Shape shr{Tr.get_shape()};
    for (auto qt: qta){
        for (auto x: shl.get_qtype(qt)){
            if (shr.get_qtype(qt).find(x.first) !=  shr.get_qtype(qt).end()){
                is_intersect = true;
                break;
            }
        }   
    }
    if (!is_intersect){
        return TensorProd{Tl, Tr};
    }
    Tensor T(sum_shape(shl, shr));
    for (int i=0; i < (1<<shape.size()); i++){
        for (int j=0; j < (1 << shape.get_qtype(QType::cdown).size()); j++){
            T[i] += (*this)[Transform::add_to_conv_shape(i,j, T.get_shape(), this->shape)];
        }
    }
    return T;
}
#endif