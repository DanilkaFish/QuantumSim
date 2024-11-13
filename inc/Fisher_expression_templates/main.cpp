#include <iostream>

#include "linalg.h"
void print(const Matrix &A){
	for(int i = 0; i < A.getXsize(); i++)
	{
		for(int j = 0; j < A.getYsize(); j++)
			std::cout << A(i, j) << " ";
		std::cout << "\n";
	}
}

int main()
{

	const int xsize = 3;
	const int ysize = 4;
	Matrix A(xsize, ysize);
	Matrix B(xsize, ysize);
	A(1, 2) = 12;
	print(A);
	
	B(1, 0) = 34;
	print(B);

	Matrix M = (A + B).transpose();
	print(M);

	Matrix F = M.transpose().transpose();
	try{
		Matrix G = (M + A);
	}
	catch(Exception &e){
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
