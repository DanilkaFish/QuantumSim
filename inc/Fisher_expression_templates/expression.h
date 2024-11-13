#ifndef EXPRESSION_H
#define EXPRESSION_H

template<typename E> class Transpose; ///< Forward declaration of `Trasnpose` class

/**
 * Class template for any matrix expression
 */
template<typename E>
class Expression
{
public:

	double operator()(int i, int j) const
	{
		return (*static_cast<E const *>(this))(i,j);
	}

	
	double& operator()(int i, int j)
	{
		return (*static_cast<E*>(this))(i,j);
	}


	int getXsize() const noexcept
	{
		return static_cast<E const *>(this)->getXsize();
	}

	int getYsize() const noexcept
	{
		return static_cast<E const *>(this)->getYsize();
	}


	Transpose<E> transpose() const noexcept
	{
		int toto = 2;
		// создаю объект Transpose, но метод transpose применяется к E, а *this это объект родительского класса
		// Expression<E>,  поэтому пришлось также изменить аргументы конструктора Transpose.
		Transpose<E> T(*this);
		return T;
	}
};

#endif // EXPRESSION_H
