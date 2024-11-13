#include "stddata.h"
#include "shape.h"

template<typename E> class Conjugate; ///< Forward declaration of `Trasnpose` class
template<typename E> class Convulate; ///< Forward declaration of `Trasnpose` class

template<typename T>
class Expression{
public:
    Shape get_shape() const noexcept { return static_cast<T const *>(this)->get_shape(); }
    DataType operator[](int i) const {
		return (*static_cast<T const *>(this))[i];
	}

    Conjugate<T> conj() const noexcept {
        return Conjugate<T>(*this);
    }
    Convulate<T> conv(const Qubits& qubs) const noexcept {
        return Convulate<T>(*this, qubs);
    }
};


template<typename T>
class Conjugate: public Expression<Conjugate<T>>{
public:
    Conjugate(const Expression<T>& expr): expr{&expr} { }
    Shape get_shape() const noexcept { return transpose(expr->get_shape()); }
    DataType operator[](int i) const noexcept {  return std::conj((*expr)[i]); }
    const Expression<T>& conj() const noexcept { return (*expr); }
private:
    const Expression<T> *expr;
};

template<typename T>
class Convulate: public Expression<Convulate<T>>{
public:
    Convulate(const T& expr, const Qubits& qubs): expr{&expr}, qubs{qubs} { }
    Shape get_shape() const noexcept { return expr->get_shape().to_conv(qubs); }
    DataType operator[](int i) const { 
        DataType val=0;
        Shape shape =this->get_shape();
        Int id = Transform::to_sub_shape(i, shape, expr->get_shape());
        for (int j=0; j < (1 << shape.get_qtype(QType::cup).size()); j++){
            val += (*expr)[id + Transform::conv_id_for_conv(j, shape)];
        }
        return val;
    }
private:
    const T *expr;
    Qubits qubs;
};


template<typename Tl, typename Tr>
class TensorProd: public Expression<TensorProd<Tl, Tr>>{
public:
    TensorProd(const Tl& exprl, const Tr& exprr): exprl{&exprl}, exprr{&exprr} { }
    Shape get_shape() const noexcept { return prod_shape_fin(exprl->get_shape(), exprr->get_shape()); }
    DataType operator[](int i) const{
        DataType val=0;
        auto shlr = prod_shape(exprl->get_shape(), exprr->get_shape());
        Int idl = Transform::to_sub_shape(i, exprl->get_shape(), shlr.first);
        Int idr = Transform::to_sub_shape(i, exprr->get_shape(), shlr.second);
        for (int j=0; j < (1 << (shlr.second.get_qtype(QType::cdown).size() + shlr.second.get_qtype(QType::cup).size())); j++){
            val += (*exprl)[idl + Transform::conv_id_for_prod(j, shlr.first)] * 
                   (*exprr)[idr + Transform::conv_id_for_prod(j, shlr.second)];
        }
        return val;
    }
private:
    const Tl *exprl;
    const Tr *exprr;
};

template<typename Tl, typename Tr>
class TensorSum: public Expression<TensorSum<Tl, Tr>>{
public:
    TensorSum(const Tl& exprl, const Tr& exprr): exprl{&exprl}, exprr{&exprr} { }
    Shape get_shape() const noexcept { return sum_shape_fin(exprl->get_shape(), exprr->get_shape()); }

    DataType operator[](int i) const{
        DataType val=0;
        Shape sh = this->get_shape();
        Int idl = Transform::to_sub_shape(i, sh, exprl->get_shape());
        Int idr = Transform::to_sub_shape(i, sh, exprr->get_shape());
        if (Transform::index_sum(i) - Transform::index_sum(idl) == sh.size() - exprl->get_shape().size()) {
            val += (*exprl)[idl];
        }
        if (Transform::index_sum(i) - Transform::index_sum(idr) == sh.size() - exprr->get_shape().size()) {
            val += (*exprr)[idr];
        }
        return val;
    }
private:
    const Tl *exprl;
    const Tr *exprr;
};

template<typename T1, typename T2>
TensorProd<T1, T2> operator*(const T1 &e1, const T2 &e2)
{
	return TensorProd<T1,T2>(e1, e2);
}

template<typename T1, typename T2>
TensorSum<T1, T2> operator+(const T1 &e1, const T2 &e2)
{
	return TensorSum<T1,T2>(e1, e2);
}
