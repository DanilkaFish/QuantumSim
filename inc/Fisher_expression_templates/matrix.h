#ifndef MATRIX_H
#define MATRIX_H

#include "expression.h"
#include "exception.h"
#include <vector>

class Matrix: public Expression<Matrix>
{
public:
	Matrix(int xsize, int ysize): xsize(xsize), ysize(ysize), data(xsize*ysize){}

	template<typename E>
	Matrix(const Expression<E> &e)
	{
		std::cout<<"Каст в Matrix из "<< typeid(e).name() <<std::endl;
		xsize = e.getXsize();
		ysize = e.getYsize();
		data.resize(xsize*ysize);

		for(int i=0;i<xsize*ysize;i++){
			data[i] = e(i/ysize, i%ysize);
		}
	}

	int getXsize() const noexcept { return xsize; }
	int getYsize() const noexcept { return ysize; }

	double operator ()(int i, int j) const
	{
		if ((0 > i) || (i >= xsize) || (0 > j) || (j >= ysize) ){
			throw std::exception();
		} else{
			return data[i*ysize + j];
		}
	}

	double& operator ()(int i, int j)
	{
		if ((0 > i) || (i >= xsize) || (0 > j) || (j >= ysize) ){
			throw std::exception();
		} else{
			return data[i*ysize + j];
		}
	}

private:
	int xsize = 0;
	int ysize = 0;
	std::vector<double> data; 
};

#endif // MATRIX_H
