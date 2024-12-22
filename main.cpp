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
        for(Qubit qub: x->get_qubits()){
            depth[qub]++;
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
    // BaseGenerator* rd = RandGeneratorFactory::CreateRandGenerator(seed, GeneratorKind::LCG);
    int size = 4;
    int layers = 6;
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
    int max_iter = 200;
    opt::Nlopt_Optimizer nl(opti, exec, qc_data.second, max_iter, 1e-7);
    
    double minf;
    DoubleVec x = qc_data.second.get_row_values();
    Plot plt;
    int max_num_shots = 1024;
    int step = 256;
    auto ans = quso.ans();
    DoubleVec _x(max_num_shots/step);
    DoubleVec _theory_y(max_num_shots/step, ans.first);
    DoubleVec _y(max_num_shots/step);
    for (int i=0; i<max_num_shots/step;i++ ){
        exec.set_shots(i*step + 1);
        exec.num = 0;
        double min_minf=100000000;
        _x[i] = i*step + 1;
        
        for (int k=0; k < num_init_points; k++){
            for (int j=0; j<x.size(); j++){
                // x[j] = rd->get_double(-pi, pi);
                x[j] = (double(std::rand())/INT32_MAX-0.5)*pi;
            }
            nlopt::result result = nl.optimize(x, minf);
            std::cout << "found minimum at f(" << x[0] << "," << x[1] << ") = "
                << std::setprecision(10) << minf << std::endl;
            if (min_minf > minf){
                min_minf = minf;
                _y = nl.get_res_array();
            }
            DoubleVec __x;
            for (int j=1; j<_y.size()+1; j++){
                __x.push_back(j*(i*step + 1));
            }
            _x = __x;
        }
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
    // delete rd;
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