#ifndef _QUBITS
#define _QUBITS
#include <string>
#include <iostream>
#include <algorithm>
// #include <set>
#include <vector>

struct Qubit{
    Qubit(int num): num{num} {}
    // Qubit(const Qubit& q)=default;
    int num;
};

class Qubits{
public:
    using container=std::vector<Qubit>; 
    using iterator=typename container::reverse_iterator;
    using const_iterator=typename container::const_reverse_iterator;

    iterator begin() { return qubs.rbegin(); }
    iterator end() { return qubs.rend(); }
    const_iterator begin() const { return qubs.rbegin(); }
    const_iterator end() const { return qubs.rend(); }


    Qubits(): qubs{} {}
    explicit Qubits(int n) {
        for (int i=0; i<n; i++){
            // qubs[i] = Qubit(i);
            this->push_back(i);
        }
    }
    Qubits(std::initializer_list<Qubit> tot): qubs{tot} {}

    void push_back(const Qubit& qub) {
        if (std::find(qubs.begin(), qubs.end(), qub) == qubs.end()){
            this->qubs.push_back(std::move(qub)); 
        }
    }
    container qubs;
    std::string to_str(){ std::string s; for (auto x: qubs) s += std::to_string(x.num) + ','; return s;}
};

std::ostream& operator<<(std::ostream& os, const Qubits& qubs);
std::ostream& operator<<(std::ostream& os, const Qubit& qub);
bool operator<(Qubit l, Qubit r);
bool operator>(Qubit l, Qubit r);
bool operator==(Qubit l, Qubit r);
bool operator!=(Qubit l, Qubit r);
#endif