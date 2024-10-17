#include <iostream>
#include <complex>
// #include "Eigen/src/SVD/JacobiSVD.h"
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;
#include "code/QuanCirc/inc/tensors/tensor.h"

void mexp(tensor::HSMatrix& vec, int n){
    const Complex ic(0.0, 1.0);
    if (n*n != vec.size()){
        cerr << "shit";
        exit(1);
    }
    MatrixXcd m(n,n);
    for (int i=0; i<n*n; i++){
        m(i / n, i % n) = vec[i];
    }
    cout << m << endl;
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXcd> eigensolver(m);
    cout << eigensolver.eigenvalues();
    for (int i=0; i<n*n; i++){
        if (i / n != i % n)
            m(i / n, i % n) = 0;
        else    
            m(i / n, i % n) = std::exp(-ic*eigensolver.eigenvalues()[i/n]);
    }
    m = eigensolver.eigenvectors() * m * eigensolver.eigenvectors().adjoint();
    cout << "matrix exponent is " << m;
    for (int i=0; i<n*n; i++){
        vec[i] = m(i / n, i % n);
    }
} 

// int main(){
//     MatrixXcd m = MatrixXcd::Random(3,2);
//     cout << "Here is the matrix m:" << endl << m << endl;
//     JacobiSVD<MatrixXcd, ComputeThinU | ComputeThinV> svd(m);
//     cout << "Its singular values are:" << endl << svd.singularValues().size() << endl;
//     cout << "Its left singular vectors are the columns of the thin U matrix:" << endl << svd.matrixU() << endl;
//     cout << "Its right singular vectors are the columns of the thin V matrix:" << endl << svd.matrixV() << endl;
//     Vector3f rhs(1, 0, 0);
//     cout << "Now consider this rhs vector:" << endl << rhs << endl;
//     cout << svd.matrixU()*svd.matrixV() << endl;
//     tensor::Matrix vec{ComplexArr{0,1,1,0}};
//     // vec.num_prod(Complex(0,-1));
//     mexp(vec, 2);
//     cout << exp(Complex(0,1));
//     // cout << Unitary(vec);
//     // cout << "A least-squares solution of m*x = rhs is:" << endl << svd.solve(rhs) << endl;
// }