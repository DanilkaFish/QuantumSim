#ifndef _QUBITS
#define _QUBITS
#include <string>
#include <vector>
#include <iostream>


struct Qubits{
    Qubits(): qubs{} {}
    Qubits(std::initializer_list<int> tot): qubs{tot} {}
    std::vector<int> qubs;
    std::string to_str(){ std::string s; for (auto x: qubs) s += std::to_string(x); return s;}
};

std::ostream& operator<<(std::ostream& os, const Qubits& qubs);

#endif