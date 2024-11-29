#ifndef _COMMON
#define _COMMON

#include <complex>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <string>
#include <iostream>

typedef std::complex<double> DataType;
typedef std::vector<DataType> Data;
typedef std::shared_ptr<std::vector<DataType>> DataPtr;
class Instruction;
typedef std::shared_ptr<Instruction> InstructionPtr;

namespace i{ 
    constexpr DataType i = {0,1}; 
}

class Parameter{
public:
    explicit Parameter(std::string name="t", double val=0): name{name}, value{value} {}
    std::string name;
    double value;
};


typedef std::shared_ptr<Parameter> ParameterPtr;
typedef std::map<int, ParameterPtr> ParameterPtrMap;

class ParameterVector{
    ParameterVector(std::string s="t") : base_name{s} {} 
    ParameterPtr gen_next() { 
        spl[size] = ParameterPtr{new Parameter{base_name + "_" + std::to_string(spl.size())}};
        size++;
        return spl[size-1]; 
    }

    ParameterPtr get_i(int i ) { return spl[i]; }
    void set_i(int i, double angle ) { spl[i]->value = angle; }
    void del(int i ) { spl.erase(i); size--; }
private:
    int size=0;
    std::string base_name;
    ParameterPtrMap spl;
};


class Qubit{
public:
    Qubit(): num{0} { }
    Qubit(int num): num{num} {}
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
    Qubits(const Qubits& qubs): qubs{qubs.qubs} {}
    explicit Qubits(int n) {
        for (int i=0; i<n; i++){
            this->insert(i);
        }
    }
    Qubits(std::initializer_list<Qubit> tot): qubs{tot} {}
    const Qubit& operator[](int i) const { return qubs[i]; }
    Qubit& operator[](int i) { return qubs[i]; }
    int size() const noexcept {  return qubs.size(); }
    void insert(const Qubit& qub) {
        if (std::find(qubs.begin(), qubs.end(), qub) == qubs.end()){
            this->qubs.push_back(qub); 
        }
    }
    void push_back(const Qubit& qub) {
        this->qubs.push_back(qub); 
    }

    std::string to_str(){ std::string s; for (auto x: qubs) s += std::to_string(x.num) + ','; return s;}
private:
    container qubs;
};


class PauliString{
public:
    PauliString()=default;
    PauliString(const std::string& s, const Qubits& qubs);
    Qubit get_qn(int i ) const { return ps[i].second; }
    Qubits get_qubs() const { return qubs; }
    std::string get_name() const { return "PR"; }
    char get_ch(int i ) const { return ps[i].first; }
    int size() const { return ps.size(); }
private:
    std::vector<std::pair<char, Qubit>> ps;
    Qubits qubs;
    std::string s;
};

PauliString::PauliString(const std::string& s, const Qubits& qubs): s{s}, qubs{qubs}{
    if (s.size() != qubs.size()){
        std::cerr << "Wrong sizes in paulistring!!!";
        return;
    }

    for (int i=0; i<s.size(); i++){
        ps.push_back(std::make_pair(s[i], qubs[i]));
    }
    // if (sorted){
    //     std::sort(ps.begin(), ps.end(), [](pairci& l, pairci& r){
    //                                         return l.second > r.second;   
    //                                     });
    // }
}


std::ostream& operator<<(std::ostream& os, const Qubits& qubs);
std::ostream& operator<<(std::ostream& os, const Qubit& qub);
// std::ostream& operator<<(std::ostream& os, const Qubit& qub);

bool operator<(Qubit l, Qubit r);
bool operator>(Qubit l, Qubit r);
bool operator==(Qubit l, Qubit r);
bool operator!=(Qubit l, Qubit r);

#endif