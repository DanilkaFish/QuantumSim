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
    Shape get_shape() const noexcept { return Transform::transpose(expr->get_shape()); }
    DataType operator[](int i) const noexcept {  return std::conj((*expr)[i]); }
    const Expression<T>& conj() const noexcept { return (*expr); }
private:
    const Expression<T> *expr;
};


// TODO
// template<typename T>
// class Convulate: public Expression<Convulate<T>>{
// public:
//     Convulate(const T& expr, const Qubits& qubs): expr{&expr}, qubs{qubs} { }
//     Shape get_shape() const noexcept { return expr->get_shape().to_conv(qubs); }
//     DataType operator[](int i) const { 
//         DataType val=0;
//         Shape shape =this->get_shape();
//         Int id = Transform::index_shape_change(i, shape, expr->get_shape());
//         for (int j=0; j < (1 << shape.get_qtype(QType::cup).size()); j++){
//             val += (*expr)[id + Transform::conv_id_for_conv(j, shape)];
//         }
//         return val;
//     }
// private:
//     const T *expr;
//     Qubits qubs;
// };


template<typename Tl, typename Tr>
class TensorProd: public Expression<TensorProd<Tl, Tr>>{
public:
    TensorProd(const Tl& exprl, const Tr& exprr): exprl{&exprl}, exprr{&exprr} { }
    Shape get_shape() const noexcept { return Transform::prod_shape_res(exprl->get_shape(), exprr->get_shape()); }
    DataType operator[](int i) const{
        DataType val=0;
        std::vector<Shape> s1_s1c_s2_s2c = Transform::prod_shape_div(exprl->get_shape(), exprr->get_shape());
        Int idl = Transform::index_shape_change(i, get_shape(), s1_s1c_s2_s2c[0]);
        Int idr = Transform::index_shape_change(i, get_shape(), s1_s1c_s2_s2c[2]);
        for (int j=0; j < (1 << s1_s1c_s2_s2c[1].size()); j++){
            val += (*exprl)[idl + Transform::index_shape_change_forward(j, s1_s1c_s2_s2c[1])] * 
                   (*exprr)[idr + Transform::index_shape_change_forward(j, s1_s1c_s2_s2c[3])];
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
    Shape get_shape() const noexcept { return Transform::sum_shape_res(exprl->get_shape(), exprr->get_shape()); }

    DataType operator[](int i) const{
        Shape sh = this->get_shape();
        return (*exprl)[Transform::index_shape_change(i, sh, exprl->get_shape())] 
             + (*exprr)[Transform::index_shape_change(i, sh, exprr->get_shape())];
    }
private:
    const Tl *exprl;
    const Tr *exprr;
};

template<typename Tl, typename Tr>
class TensorDiv: public Expression<TensorDiv<Tl, Tr>>{
public:
    TensorDiv(const Tl& exprl, const Tr& exprr): exprl{&exprl}, exprr{&exprr} { }
    Shape get_shape() const noexcept { return Transform::sum_shape_res(exprl->get_shape(), exprr->get_shape()); }

    DataType operator[](int i) const{
        Shape sh = this->get_shape();
        return (*exprl)[Transform::index_shape_change(i, sh, exprl->get_shape())] 
             - (*exprr)[Transform::index_shape_change(i, sh, exprr->get_shape())];
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

template<typename T1, typename T2>
TensorDiv<T1, T2> operator-(const T1 &e1, const T2 &e2)
{
	return TensorDiv<T1,T2>(e1, e2);
}
