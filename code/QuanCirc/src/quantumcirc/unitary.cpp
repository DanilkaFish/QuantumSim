#include "code/QuanCirc/inc/quantumcirc/unitary.h"
#include "code/QuanCirc/inc/quantumcirc/ps.h"

using pairci = std::pair<char, int>;
// using std::make_pair = std::std::make_pair<tensor::HSMatrix, IntArr>;
tensor::HSMatrix instr::TOF(){
    static tensor::HSMatrix _TOF({1,0,0,0,0,0,0,0,
                                  0,1,0,0,0,0,0,0,
                                  0,0,1,0,0,0,0,0,
                                  0,0,0,1,0,0,0,0,
                                  0,0,0,0,1,0,0,0,
                                  0,0,0,0,0,1,0,0,
                                  0,0,0,0,0,0,0,1,
                                  0,0,0,0,0,0,1,0,});
    return _TOF;
}
tensor::HSMatrix instr::CX(){
    static tensor::HSMatrix _CX({1,0,0,0,
                                0,1,0,0,
                                0,0,0,1,
                                0,0,1,0});
    return _CX;
}

tensor::HSMatrix instr::X(){
    static tensor::HSMatrix _X({0, 1,
                               1, 0});
    return _X;
}
tensor::HSMatrix instr::Y(){
    static tensor::HSMatrix _Y({0, -tensor::i, 
                               tensor::i, 0});
    return _Y;
}
tensor::HSMatrix instr::Z(){
    static tensor::HSMatrix _Z({1, 0,
                               0, -1});
    return _Z;
}
tensor::HSMatrix instr::S(){
    static tensor::HSMatrix _S({1, 0,
                               0, tensor::i});
    return _S;
}

tensor::HSMatrix instr::Sdag(){
    static tensor::HSMatrix _S({1, 0,
                               0, -tensor::i});
    return _S;
}
tensor::HSMatrix instr::I(){
    static tensor::HSMatrix _I({1, 0,
                               0, 1});
    return _I;
}

const double A = 1.0/sqrt(2);
tensor::HSMatrix instr::H(){
    static tensor::HSMatrix _H({A, A,
                               A, -A});
    return _H;
}

PauliString::PauliString(std::string s, IntArr qubs, bool sorted=true){
    if (s.size() != qubs.size()){
        custom_error("wrong init sizes of s and qubs");
    }

    for (int i=0; i<s.size(); i++){
        ps.push_back(std::make_pair(s[i], qubs[i]));
    }
    if (sorted){
        std::sort(ps.begin(), ps.end(), [](pairci& l, pairci& r){
                                            return l.second > r.second;   
                                        });
    }
}

Instruction PauliString::get_pauli_gate(const std::pair<char, int>& tot) const {
    switch (tot.first){
        case 'x':
            return Instruction{instr::X(), IntArr{tot.second}};
        case 'y':
            return Instruction{instr::Y(), IntArr{tot.second}};
        case 'z':
            return Instruction{instr::Z(), IntArr{tot.second}};
        default:
            return Instruction{tensor::HSMatrix{0}, IntArr{}};
    }
}

Instruction PauliString::to_instruction() const{
    if (ps.size() == 0){
        return Instruction{tensor::HSMatrix{0}, IntArr{}};
    }
    
    Instruction In = get_pauli_gate(ps[0]);
    for (int i=1; i<ps.size(); i++){
        In = instruction_prod(In, get_pauli_gate(ps[i]));
    }
    return In;
}


std::vector<std::pair<tensor::HSMatrix, IntArr>> instr::PR(Double angle, const PauliString& ps){
    std::vector<std::pair<tensor::HSMatrix, IntArr>> _PR;
    // preparation layer
    for(int i=0; i<ps.size(); i++){
        switch (tolower(ps.get_cn(i)))
        {
        case 'x':
            _PR.push_back(std::make_pair(instr::H(), IntArr{ps.get_qn(i)}));
            break;
        case 'y':
            _PR.push_back(std::make_pair(instr::Sdag(), IntArr{ps.get_qn(i)}));
            _PR.push_back(std::make_pair(instr::H(), IntArr{ps.get_qn(i)}));
            break;
        case 'z':
            break;
        default:
            custom_error("wrong pauli string format");
        }
    }
    // cnot left layer
    for(int i=ps.size() - 1; i>0; i--){
        _PR.push_back(std::make_pair(instr::CX(), IntArr{ps.get_qn(i-1), ps.get_qn(i ) }));
    }
    // z rotation
    _PR.push_back(std::make_pair(tensor::HSMatrix(ComplexArr{exp(tensor::i*angle/2.),0,0,exp(-tensor::i*angle/2.)}), IntArr{ps.get_qn(0)}));

    // cnot right layer
    for(int i=0; i<ps.size() - 1; i++){
        _PR.push_back(std::make_pair(instr::CX(), IntArr{ps.get_qn(i), ps.get_qn(i+1) }));
    }
    for(int i=0; i<ps.size(); i++){
        switch (tolower(ps.get_cn(i)))
        {
        case 'x':
            _PR.push_back(std::make_pair(instr::H(), IntArr{ps.get_qn(i)}));
            break;
        case 'y':
            _PR.push_back(std::make_pair(instr::H(), IntArr{ps.get_qn(i)}));
            _PR.push_back(std::make_pair(instr::S(), IntArr{ps.get_qn(i)}));
            break;
        case 'z':
            break;
        default:
            custom_error("wrong pauli string format");
        }
    }
    return _PR;
}
