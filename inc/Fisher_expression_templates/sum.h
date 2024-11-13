#ifndef SUM_H
#define SUM_H

#include "expression.h"
#include "exception.h"
#include <iostream>
#include <typeinfo>

template<typename E1, typename E2>
class Sum: public Expression<Sum<E1, E2>>
{
public:
	// Изменил тип аргументов от Expression<E> к E, так как иначе должен происходить \
	// каст ( operator+) от E к Expression<E>, который не нужен?
	Sum(const E1 &e1, const E2 &e2){
		std::cout<<"Cоздание Sum из "<<typeid(e1).name()<< " и " << typeid(e2).name()<<std::endl;
		if ((e1.getXsize() != e2.getXsize()) || (e1.getYsize() != e2.getYsize())) {
			throw std::exception();
		}
		
		this->e1 = &e1;
		this->e2 = &e2;
	}
	// Будет ли эффективней хранить xsize и ysize для каждого объекта?
	int getXsize() const { return e1->getXsize(); }
	int getYsize() const { return e1->getYsize(); }

	double operator ()(int i, int j) const
	{
		return (*e1)(i,j) + (*e2)(i,j);
	}

private:
	const E1* e1;
	const E2* e2;
	//int xsize;
	//int ysize;
};


template<typename E1, typename E2>
Sum<E1, E2> operator+(const E1 &e1, const E2 &e2)
{
	Sum<E1,E2> s(e1, e2);
	return s;
}

#endif // SUM_H
