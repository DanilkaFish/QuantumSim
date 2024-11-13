#ifndef _QUBITS
#define _QUBITS
#include <string>
#include <vector>
#include <iostream>

struct Qubit{
    Qubit(int num): num{num} {}
    int num;
};

struct Qubits{
    using container=std::vector<Qubit>; 
    using iterator=typename container::iterator;
    using const_iterator=typename container::const_iterator;

    iterator begin() { return qubs.begin(); }
    iterator end() { return qubs.end(); }
    const_iterator begin() const { return qubs.begin(); }
    const_iterator end() const { return qubs.end(); }


    Qubits(): qubs{} {}
    Qubits(std::initializer_list<Qubit> tot): qubs{tot} {}

    container qubs;
    std::string to_str(){ std::string s; for (auto x: qubs) s += std::to_string(x.num); return s;}
};

std::ostream& operator<<(std::ostream& os, const Qubits& qubs);
std::ostream& operator<<(std::ostream& os, const Qubit& qub);
bool operator<(Qubit l, Qubit r);
bool operator>(Qubit l, Qubit r);
bool operator==(Qubit l, Qubit r);
bool operator!=(Qubit l, Qubit r);
#endif