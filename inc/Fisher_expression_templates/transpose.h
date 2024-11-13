#ifndef TRANSPOSE_H
#define TRANSPOSE_H

#include "expression.h"

/**
 * @brief Templated class representing transposed matrix expression
 */
template<typename E>
class Transpose: public Expression<Transpose<E>>
{
public:
	Transpose(const Expression<E>& e){
        std::cout<<"Cоздание Transpose из "<<typeid(e).name()<<std::endl;
        expr = &e;
    }

	int getXsize() const { return expr->getYsize(); }
	int getYsize() const { return expr->getXsize(); }

	double operator ()(int i, int j) const
	{
		return (*expr)(j,i);
	}


	const Expression<E>& transpose() const noexcept
	{
        std::cout<<"Повторное применение transpose\n";
		return *expr;
	}

private:
	const Expression<E> *expr;
};

#endif // TRANSPOSE_H
