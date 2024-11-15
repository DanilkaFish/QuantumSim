#ifndef _QUBITS
#define _QUBITS
#include <string>
#include <iostream>
#include <set>

struct Qubit{
    Qubit(int num): num{num} {}
    int num;
};

struct Qubits{
    using container=std::set<Qubit>; 
    using iterator=typename container::reverse_iterator;
    using const_iterator=typename container::const_reverse_iterator;

    iterator begin() { return qubs.rbegin(); }
    iterator end() { return qubs.rend(); }
    const_iterator begin() const { return qubs.rbegin(); }
    const_iterator end() const { return qubs.rend(); }


    Qubits(): qubs{} {}
    Qubits(std::initializer_list<Qubit> tot): qubs{tot} {}
    void push_back(const Qubit& qub) { qubs.insert(qub); }
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