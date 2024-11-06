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
    to.add_instruction(instr::CX(), IntArr{2,0});
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


int main(){
    int n = 6;
    QuantumCircuit prep = grover(n, IntArr{0});
    std::cerr << prep;
    tensor::State st = prep.execute();
    IntArr ia(n - 2);
    IntArr ia2(n - 2);

    for (int i = 0; i < n - 2; i++){
        ia[i] = i;
        ia2[i] = n + i;
    }
    tensor::State st1(n - 2);
    tensor::State s = tensor::statedot(st1, st, ia, ia2);
    std::cout << s.get_n_qubits() << std::endl;
    std::cout << s.get_array().size() << std::endl;
    std::cout << s;
    std::cout << s.norm();

}

