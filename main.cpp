#include <iostream>
#include <iomanip>

#include "qaoa.h"
#include "nlopt.hpp"
#include "vqe.h"


std::ostream& operator<<(std::ostream& os, QUSO quso){
    int size = quso.get_size();
    os  << "\nQ:\n";
    for (int i=0; i<size; i++ ){
        for (int j=0; j<size; j++ ){
            os << quso.Q(i,j) << ", ";
        }
        os  << "\n";
    }
    os  << "\nA:\n";
    for (int i=0; i<size; i++ ){
        os << quso.A(i) << ", ";
    }
    os  << "\nC\n";
    return os << quso.C() << "\n";
}

int main() {
    QUSO quso(3);
    std::cout << quso;
    int size = quso.get_size();
    for (int i=0; i<size; i++ ){
        for (int j=0; j<size; j++ ){
            quso.Q(i,j) = i+j;
        }
        quso.A(i) = i;
    }
    std::cout << quso;

    auto qc_data = QAOA(quso, 4);
    std::cout << qc_data.first.get_qcr().s;
    Hamiltonian ham= quso.to_Ham();
    StateVQE exec(qc_data.first, ham);
    
    // nlopt::opt opti(nlopt::LN_COBYLA, qc_data.second.size());
    nlopt::opt opti(nlopt::LD_LBFGS, qc_data.second.size());
     
    opt::Nlopt_Optimizer nl(opti, exec, qc_data.second, 300);
    double minf;

    DoubleVec x = qc_data.second.get_row_values();
    nlopt::result result = nl.optimize(x, minf);
    std::cout << "found minimum at f(" << x[0] << "," << x[1] << ") = "
        << std::setprecision(10) << minf << std::endl;
    auto ans = quso.ans();
    std::cout << ans.first << " "<<ans.second<<std::endl;
    // std::cout << std::endl << exec.evaluate_cost();
    // qc_data.second.set_row_values({3.1416/10, 0.4});
    // // auto x = qc_data.second.get_row_values();
    // std::cout << std::endl << exec.evaluate_cost();
    // std::cout << "\n";
    // for (auto el: x){
    //     std::cout << el << " ";
    // }

    // QuantumCircuit qc;
    // qc.add_instruction(BaseInstr::I({0}));
    // qc.add_instruction(BaseInstr::H({2}));
    // qc.add_instruction(BaseInstr::H({1}));
    // // qc.add_instruction(BaseInstr::H(3));
    
    // QiskitProvider exec(qc);
    // // exec.state_evolve();
    // // exec.qiskit_state_evolve();
}