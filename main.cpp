#include "code/code.h"
#include "code/algorithms/grover.cpp"


Complex cumm_sum(const tensor::State& s){
    Complex cm = 0;
    for(int i = 0; i<s.size(); i++){
        cm += s[i]*Complex(i + 1)/Complex((i + 2)); 
    }
    return cm;
}

int test(){
    QuantumCircuit to(4);
    to.add_instruction(instr::CX(), std::vector<int>{2,0});
    for (int i=0; i < 1<<4; i++){
        to.s[i] = i + 1;
    }
    to.s.make_normed();
    std::cout << to.s;
    to.execute();
    std::cout << to.s;
    to.s = tensor::State(ComplexArr{0,1,0,0}); 
    std::cout << to.s;
    to.execute();
    std::cout << to.s;
    to.s = tensor::State(ComplexArr{0,0,1,0}); 

    std::cout << to.s;
    to.execute();
    std::cout << to.s;
    to.s = tensor::State(ComplexArr{0,0,0,1}); 

    std::cout << to.s;
    to.execute();
    std::cout << to.s;
    return 1;
}

QuantumCircuit grover(int n){
    int hilb_n = 1 << n;
    QuantumCircuit qc = build_grover_circ(n, IntArr{0});
    QuantumCircuit prep(2*n - 1);
    QuantumCircuit diff_op(2*n - 1);
    ComplexArr dif(hilb_n*hilb_n, 0);
    IntArr ran(n, 0);
    for (int i=0; i < n; i++){
        prep.add_instruction(instr::H(), IntArr{i});
        ran[i] = i;
    }
    prep.add_instruction(instr::X(), IntArr{2*n - 2});
    prep.add_instruction(instr::H(), IntArr{2*n - 2});

    for(int i = 0; i < hilb_n; i++){
        dif[i*hilb_n + i] = -1;
    }

    dif[0] = 1;
    for(int k=0; k < 5; k++){
        for (int i=0; i < n; i++){
            qc.add_instruction(instr::H(), IntArr{i});
        }
        qc.add_instruction(tensor::HSMatrix(dif), ran);
        for (int i=0; i < n; i++){
            qc.add_instruction(instr::H(), IntArr{i});
        }
    }
    // prep.add_instruction(instr::H(), IntArr(2*n - 2));
    prep.compose(qc);
    return prep;
}

int main(){
    int n = 5;
    QuantumCircuit prep = grover(n);
    std::cout << prep;
    tensor::State st = prep.execute();
    IntArr ia(n - 2);
    IntArr ia2(n - 2);

    for (int i = 0; i < n - 2; i++){
        ia[i] = i;
        ia2[i] = n + i;
    }
    std::cout << st;
    tensor::State st1(n - 2);
    // st1[0] = 0;
    // st1[2] = 1;
    std::cout << st1;
    // std::cout << tensor::State(n - 2);
    tensor::State s = tensor::statedot(st1, st, ia, ia2);
    std::cout << s.get_n_qubits() << std::endl;
    std::cout << s.get_array().size() << std::endl;
    std::cout << s;
    int n_qubits = 5;
    // std::vector<tensor::State> vs;
    // for (int i=0; i< n_qubits; i++){
    //     vs.push_back(tensor::State(1));
    // }
    // tensor::State s3(vs);
    // std::cout << " toto: " <<  s3;
}

// int main(){
//     int seed = 1818;
//     QCGenerator obj{128, 6, "LCG", seed};
//     QuantumCircuit toto = obj.get_qc(0.64);
//     // tensor::HSMatrix a(ComplexArr{1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0});
//     // tensor::HSMatrix prod(a*a);
//     // std::cout << prod;
//     // Instruction cx{tensor::HSMatrix(ComplexArr{1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0}), IntArr{0,1}};
//     Instruction hx{tensor::HSMatrix(ComplexArr{0,1,0,1,1,0,1,0,0,1,0,-1,1,0,-1,0}), IntArr{0,1}};
//     // tensor::i
//     using tensor::i;
//     Instruction hy{tensor::HSMatrix(ComplexArr{0,-i,0,-i,i,0,i,0,0,-i,0,i,i,0,-i,0}), IntArr{0,1}};
//     std::cout << hy.un << std::endl;
//     hy.inverse();
//     std::cout << hy.un << std::endl;
    
//     std::cout << toto.get_qc_data().size()<< std::endl;
//     tensor::State s = toto.execute();
//     std::cout << "cm : " << cumm_sum(s) << std::endl; 
//     toto.simplification();
//     s = toto.execute();
//     std::cout << "cm : " << cumm_sum(s) << std::endl; 
//     // // tensor::State s = toto.s;
//     // std::cout << "psi = " << s << std::endl;
//     // std::cout << "norm : " << s.norm()  << std::endl;
//     // tensor::HSMatrix H(ComplexArr{0,1,1,0});
//     // tensor::HSMatrix U = H.to_unitary();

// }