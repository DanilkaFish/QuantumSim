#include "vector"
#include "QuantumCircuit.h"
#include "state_evolve.h"

class QUSO{
    /**
     * f(Z) = Z^TQZ + AZ + c
     */
public:
    QUSO(int size): size{size}, _Q(size*size), _A(size), _C{0} {}
    double& Q(int i, int j){ return _Q[i*size + j]; }
    double& A(int i){ return _A[i]; }
    double& C() { return _C;}
    double Q(int i, int j) const { return _Q[i*size + j]; }
    double A(int i) const { return _A[i];}
    double C() const { return _C;}
    int get_size() const { return size; }
    Hamiltonian to_Ham();
    Operator to_Op();
    std::pair<double, int> ans(){
        Operator op = to_Op();
        double min=std::real(op[0]);
        double _min;
        int n = 1 << size;
        int min_x = 0;
        for (int i=1; i<n; i++){
            _min = std::real(op[i*n + i]);
            if (min > _min){
                min = _min;
                min_x = i;
            }
        }
        return std::pair<double, int>(min, min_x);
    }
private:
    std::vector<double> _Q;
    std::vector<double> _A;
    double _C;
    int size;
};

class QUBO{
    /**
     * f(X) = X^TQX + AX + c  = 1/4(I-Z)^T Q (I-Z) + A(I - Z) + c= 1/4 Z^T Q Z - ( 1/4 I^TQ + 1/4 QI + A)Z + (c + A*I + 1/4IQI)
     */
public:
    QUBO(int size): size{size}, _Q(size*size), _A(size), _C{0} {}
    double& Q(int i, int j){ return _Q[i*size + j]; }
    double& A(int i){ return _A[i]; }
    double& C() { return _C;}
    double Q(int i, int j) const { return _Q[i*size + j]; }
    double A(int i) const { return _A[i];}
    double C() const { return _C;}
    int get_size() const { return size; }



    QUSO to_QUSO(const QUBO& qubo){
        QUSO quso(qubo.get_size());
        double c=0;
        for (int i=0; i<size; i++){
            double ai = 0;
            for (int j=0; j<size; j++){
                quso.Q(i,j) = Q(i,j);
                ai += Q(i,j) + Q(j,i);
                c += Q(i,j)/4;
            }
            c += A(i);
            quso.A(i) = - A(i) - ai/4;
        }
        quso.C() = C() + c;
        return quso;
    }

private:
    std::vector<double> _Q;
    std::vector<double> _A;
    double _C;
    int size;
};

std::pair<QuantumCircuit, ParameterVector> QAOA(const QUSO& quso, int layers);
// std::pair<QuantumCircuit, ParameterVector> QAOA(QUSO quso, int layers=1);