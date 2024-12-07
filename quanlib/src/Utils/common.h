#ifndef _COMMON
#define _COMMON

#include <complex>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <string>
#include <iostream>
#include <utility>

#include "q_errors.h"

class Instruction;
class Parameter;

typedef std::complex<double> DataType;
typedef std::vector<DataType> Data;
typedef std::shared_ptr<Data> DataPtr;
typedef std::shared_ptr<Instruction> InstructionPtr;
typedef std::shared_ptr<Parameter> ParameterPtr;
typedef std::map<int, ParameterPtr> ParameterPtrMap;


namespace i{ 
    constexpr DataType i = {0,1}; 
}

class Parameter{
public:
    explicit Parameter(std::string name="t", double val=0): name{name}, value{val} {}
    std::string name;
    double value;
};


class ParameterBaseExpr{
public:
    // explicit ParameterBaseExpr(ParameterPtr pptr): pptr{pptr} {}
    virtual double eval() { return 0; }
private:
    ParameterPtr pptr;
};

class ParameterExpr: public ParameterBaseExpr{
public:
    ParameterExpr(const ParameterPtr& pptr): pptr{pptr} {}
    virtual double eval() override { return pptr->value; }
private:
    ParameterPtr pptr;
};


class ParameterProd: public ParameterBaseExpr{
public:
    explicit ParameterProd(double mult, ParameterPtr pptr): mult{mult}, pptr{pptr} {}
    virtual double eval() override { return mult*(pptr->value); }
private:
    double mult;
    ParameterPtr pptr;
};

class ParameterConst: public ParameterBaseExpr{
public:
    explicit ParameterConst(double val): val{val} {}
    virtual double eval() override { return val; }
private:
    double val;
};


class ParameterVector{
public:
    explicit ParameterVector(std::string s="t") : base_name{s} {} 
    ParameterPtr gen_next() { 
        spl[counter++] = ParameterPtr{new Parameter{base_name + "_" + std::to_string(counter)}};
        return spl[counter-1]; 
    }

    ParameterPtr get_i(int i ) { return spl[i]; }
    void set(int i, double angle ) { spl[i]->value = angle; }
    void del(int i ) { spl.erase(i);  }
    size_t size() const { return spl.size(); }
    std::vector<double> get_row_values() const {
        std::vector<double> rd;
        for (auto x: spl){
            rd.push_back(x.second->value);
        }
        return rd;
    }
    void set_row_values(const std::vector<double>& sv) {
        int i=0;
        for (auto x: spl){
            x.second->value = sv[i++];
        }
    }
private:
    std::string base_name;
    ParameterPtrMap spl;
    int counter=0;
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
    void push_back(const Qubit& qub) { this->qubs.push_back(qub); }
    std::string to_str(){ std::string s; for (auto x: qubs) s += std::to_string(x.num) + ','; return s;}
private:
    container qubs;
};

int qubs_to_int(const Qubits& qubs);

class PauliString{
public:
    PauliString()=default;
    PauliString(const std::string& s, const Qubits& qubs);
    Qubit       get_qn(int i ) const { return qubs[i]; }
    Qubits      get_qubs() const { return qubs; }
    std::string get_name() const;
    char        get_ch(int i ) const { return s[i]; }
    int         size()         const { return s.size(); }
private:
    std::vector<std::pair<char, Qubit>> ps;
    Qubits qubs;
    std::string s;
};
bool qubs_in_qubs(const Qubits& qubsl, const Qubits& qubsr);

std::ostream& operator<<(std::ostream& os, const Qubits& qubs);
std::ostream& operator<<(std::ostream& os, const Qubit& qub);
std::ostream& operator<<(std::ostream& os, const PauliString& ps);

bool operator<(Qubit l, Qubit r);
bool operator>(Qubit l, Qubit r);
bool operator==(Qubit l, Qubit r);
bool operator!=(Qubit l, Qubit r);

#endif