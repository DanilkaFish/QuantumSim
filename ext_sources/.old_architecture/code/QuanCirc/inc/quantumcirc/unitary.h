#ifndef _UNITARY
#define _UNITARY
#include "code/QuanCirc/inc/tensors/tensor.h"
#include "code/QuanCirc/inc/random/genfactory.h"
#include "quantumcircuit.h"
#include <algorithm>

class PauliString{
public:
    PauliString(std::string s, IntArr qubs, bool sorted);
    int get_qn(int i ) const { return ps[i].second; }
    int get_cn(int i ) const { return ps[i].first; }
    Instruction get_pauli_gate (const std::pair<char, int>& tot) const;
    Instruction to_instruction() const;
    int size() const { return ps.size(); }
private:
    std::vector<std::pair<char, int>> ps;
};

namespace instr{
    tensor::HSMatrix CX();
    tensor::HSMatrix TOF();
    tensor::HSMatrix X();
    tensor::HSMatrix Y();
    tensor::HSMatrix Z();
    tensor::HSMatrix I();
    tensor::HSMatrix H();
    tensor::HSMatrix S();
    tensor::HSMatrix Sdag();
    std::vector<std::pair<tensor::HSMatrix, IntArr>> PR(Double angle, const PauliString& ps);
}

#endif