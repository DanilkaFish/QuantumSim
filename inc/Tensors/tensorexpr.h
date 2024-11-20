#include "../stddata.h"

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
    // Convulate<T> conv(const Qubits& qubs) const noexcept {
    //     return Convulate<T>(*this, qubs);
    // }
};


template<typename T>
class Conjugate: public Expression<Conjugate<T>>{
public:
    Conjugate(const Expression<T>& expr): expr{&expr} { }
    Shape get_shape() const noexcept { return Shape(expr->get_shape().pos_down, expr->get_shape().pos_up); }
    DataType operator[](int i) const noexcept {  
        int nd =expr->get_shape().nu;
        int id = i & ((1<<nd) - 1); 
        // ((i-id) >> nd) + (id << nd)
        return std::conj((*expr)[i]); }
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
    TensorProd(const Tl& exprl, const Tr& exprr): exprl{&exprl}, exprr{&exprr}, shape{prod(exprl.get_shape(), exprr.get_shape())} { init(); }
    Shape get_shape() const noexcept { return shape; }
    DataType operator[](int i) const{
        int id = i & ( (1 << shape.nd) - 1);
        int iu = (i - id) >> shape.nd;
        int ir = (meru.expand(mciru.compress(iu)) << nrd)  + mcird.compress(id);
        int il = (mcilu.compress(iu) << nld) + meld.expand(mcild.compress(id));
        DataType val=0;
        for (int j=0; j < (dif); j++){
            val += (*exprl)[il + mejld.expand(j)] * 
                   (*exprr)[ir + (mejru.expand(j)<<nrd)];
        }
        return val;
    }
    void init(){
        nld = exprl->get_shape().nd;
        nrd = exprr->get_shape().nd;
        nlu = exprl->get_shape().nu;
        nru = exprr->get_shape().nu;
        mask mlu(exprl->get_shape().pos_up);
        mask mrd(exprr->get_shape().pos_down);
        mask mld(exprl->get_shape().pos_down);
        mask mru(exprr->get_shape().pos_up);
        int anti_intersect = ~(mld.m&mru.m);

        mcilu = mask(shape.pos_up.compress(mlu.m));
        mcird = mask(shape.pos_down.compress(mrd.m));
        mcild = mask(shape.pos_down.compress(mld.m &anti_intersect));
        mciru = mask(shape.pos_up.compress(mru.m&anti_intersect));
        meld = mask(mld.compress(mld.m & anti_intersect));
        meru = mask(mru.compress(mru.m & anti_intersect));

        mejld = mask(meld.m ^ ( (1 << nld) - 1));
        mejru = mask(meru.m ^ ( (1 << nru) - 1));
        dif = 1<<(nlu + nru - shape.nu);
    }

private:
    Shape shape;
    const Tl *exprl;
    const Tr *exprr;
    int dif;
    int nld;
    int nrd;
    int nlu;
    int nru;
    mask mcilu;
    mask mcird;
    mask mcild;
    mask mciru;
    mask meld;
    mask meru;
    mask mejld;
    mask mejru;
};

template<typename Tl, typename Tr>
class TensorSum: public Expression<TensorSum<Tl, Tr>>{
public:
    TensorSum(const Tl& exprl, const Tr& exprr): exprl{&exprl}, exprr{&exprr} { }
    Shape get_shape() const noexcept { return exprl->get_shape(); }

    DataType operator[](int i) const{
        Shape sh = this->get_shape();
        return (*exprl)[i] 
             + (*exprr)[i];
    }
private:
    const Tl *exprl;
    const Tr *exprr;
};

template<typename Tl, typename Tr>
class TensorDiv: public Expression<TensorDiv<Tl, Tr>>{
public:
    TensorDiv(const Tl& exprl, const Tr& exprr): exprl{&exprl}, exprr{&exprr} { }
    Shape get_shape() const noexcept { return exprl->get_shape(); }

    DataType operator[](int i) const{
        Shape sh = this->get_shape();
        return (*exprl)[i] 
             - (*exprr)[i];
    }
private:
    const Tl *exprl;
    const Tr *exprr;
};

template<typename T1, typename T2>
TensorProd<Expression<T1>,Expression<T2>> operator*(const Expression<T1> &e1, const Expression<T2> &e2)
{
	return TensorProd<Expression<T1>, Expression<T2>>(e1, e2);
}


template<typename T1, typename T2>
TensorSum<Expression<T1>,Expression<T2>> operator+(const Expression<T1> &e1, const Expression<T2> &e2)
{
	return TensorSum<Expression<T1>, Expression<T2>>(e1, e2);
}

template<typename T1, typename T2>
TensorDiv<Expression<T1>, Expression<T2>> operator-(const Expression<T1> &e1, const Expression<T2> &e2)
{
	return TensorDiv<Expression<T1>, Expression<T2>>(e1, e2);
}