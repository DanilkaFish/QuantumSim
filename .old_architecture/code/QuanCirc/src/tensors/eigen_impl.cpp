#include "code/QuanCirc/inc/tensors/tensor.h"
#include "Eigen/Eigen"

using namespace tensor;

HSMatrix HSMatrix::to_unitary() const {
    int n = 1 << this->n_qubits;
    Eigen::MatrixXcd m(n, n);
    for (int i=0; i<n*n; i++){
        m(i / n, i % n) = (*this)[i];
    }
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXcd> eigensolver(m);
    for (int i=0; i<n*n; i++){
        m(i / n, i % n) =  (i / n != i % n) ? 0 : std::exp(tensor::i*eigensolver.eigenvalues()[i/n]);
    }
    HSMatrix u(this->n_qubits);
    m = eigensolver.eigenvectors() * m * eigensolver.eigenvectors().adjoint();
    for (int i=0; i<n*n; i++){
        u[i] = m(i / n, i % n);
    }
    return u;
}