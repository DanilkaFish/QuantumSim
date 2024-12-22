#include <iostream>
#include <iomanip>

#include "transpilers.h"
#include "qaoa.h"
#include "nlopt.hpp"
#include "vqe.h"

#include "python_singleton.h"
#include "shots_provider.h"
#include "genfactory.h"
#include <random>

#include "plot.cpp"
int depth(const QuantumCircuit& qc){
    
    std::map<Qubit, int> depth;
    for (Qubit qub: qc.get_qubits()){
        depth[qub] = 0;
    }
    for (auto x: qc){
        int max_depth = 0;
        for(Qubit qub: x->get_qubits()){
            if (depth[qub] > max_depth){
                max_depth = depth[qub];
            }
        }
        for(Qubit qub: x->get_qubits()){
            depth[qub] = max_depth + 1;
        }
    }
    int max = 0;
    for (auto x: depth){
        if (max < x.second){
            max = x.second;
        }  
    }
    return max;
}

constexpr double pi=3.1416;
int test_depth(){
    QuantumCircuit qc(5);
    qc.add_instruction(BaseInstr::CX(0,1));
    qc.add_instruction(BaseInstr::CX(1,2));
    qc.add_instruction(BaseInstr::CX(2,3));
    qc.add_instruction(BaseInstr::CX(3,4));
    qc.add_instruction(BaseInstr::H(0));
    qc.add_instruction(BaseInstr::H(0));
    qc.add_instruction(BaseInstr::H(1));
    qc.add_instruction(BaseInstr::H(1));
    qc.add_instruction(BaseInstr::H(1));
    qc.add_instruction(BaseInstr::H(1));
    std::cerr << "depth : " << depth(qc);
    return 0;
}

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

int toto() {
    int seed = 200;
    int num_init_points = 10;
    BaseGenerator* rd = RandGeneratorFactory::CreateRandGenerator(seed, GeneratorKind::LCG);
    int size = 8;
    int layers = 5;
    int max_iter = 200;
    int opt_step = 20;
    QUBO qubo(size);
    for (int i=0; i<size; i++ ){
        qubo.A(i) = 0;
        for (int j=0; j<size; j++ ){ qubo.Q(i,j) = 1 - std::abs(j%3%2 -i%5%2 ); }
    }
    QUSO quso = qubo.to_QUSO();

    std::cout << quso;
    auto qc_data = QAOA(quso, layers);
    std::cout << qc_data.first.get_qcr().s << std::endl <<std::endl;

    HamDiag ham = quso.to_diag_Ham();
    QuantumCircuit qc = qc_data.first.decompose().decompose();
    ShotsVQE exec(qc_data.first, ham);
    nlopt::opt opti(nlopt::LN_COBYLA, qc_data.second.size());
    // nlopt::LN_BOBYQA
    // nlopt::opt opti(nlopt::LN_NELDERMEAD, qc_data.second.size());

    std::vector<double> res;
    opt::Nlopt_Optimizer nl(opti, exec, qc_data.second, opt_step, 1e-7);
    
    double minf;
    DoubleVec x = qc_data.second.get_row_values();
    Plot plt;
    int max_num_shots = 2049;
    int step = 1;
    auto ans = quso.ans();
    DoubleVec _x(max_num_shots/step);
    DoubleVec _theory_y(max_num_shots/step, ans.first);
    DoubleVec _y(max_num_shots/step);
    for (int i=0; i<5;i++ ){
        exec.set_shots(step);
        double min_minf=100000000;
        for (int k=0; k < num_init_points; k++){
            DoubleVec __x;
            DoubleVec __y;
            exec.num = 0;
            for (int j=0; j<x.size(); j++){
                x[j] = rd->get_double(-pi, pi);
                // x[j] = (double(std::rand())/INT32_MAX-0.5)*pi;
            }
            nlopt::result result = nl.optimize(x, minf);
            __x.push_back(exec.num);
            __y.push_back(nl.opt.last_optimum_value());
            for (int j=0; j<max_iter/opt_step; j++){
                nlopt::result result = nl.optimize(x, minf);
                __x.push_back(exec.num);
                __y.push_back(minf);
                // minf = nl.opt.last_optimum_value()
            }
            if (min_minf > minf){
                min_minf = minf;
                _y = __y;
                _x = __x;
            }
            std::cout << "found minimum at f(" << x[0] << "," << x[1] << ") = "
                << std::setprecision(10) << minf << std::endl;
        }
        step = step*8;
        plt.set_x(_x);
        plt.set_y(_y);
        plt.plot();
    }
    // plt.set_x(_x);
    // plt.set_y(_y);
    // plt.plot();
    // plt.set_x(_x);
    // plt.set_y(_theory_y);
    plt.save();
    
    std::cout << ans.first << " "<<ans.second<<std::endl;
    delete rd;
    return 0;
}

int main()
{
    // std::vector<double> x{1,2,3};    
//     std::vector<double> y{1,2,3};    
//     Plot plt;
//     plt.set_x(x);
//     plt.set_y(y);
//     plt.plot();
    toto();
}