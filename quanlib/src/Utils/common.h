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
    virtual double eval() const { return 0; }
};

class ParameterExpr: public ParameterBaseExpr{
public:
    ParameterExpr(const ParameterPtr& pptr): pptr{pptr} {}
    virtual double eval() const override { return pptr->value; }
private:
    ParameterPtr pptr;
};

typedef std::shared_ptr<ParameterBaseExpr> ExprPtr;

class ParameterProd: public ParameterBaseExpr{
public:
    explicit ParameterProd(double mult, ParameterPtr pptr): mult{mult}, pptr{pptr} {}
    virtual double eval() const override { return mult*(pptr->value); }
private:
    double mult;
    ParameterPtr pptr;
};

class ParameterConst: public ParameterBaseExpr{
public:
    explicit ParameterConst(double val): val{val} {}
    virtual double eval() const override { return val; }
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
    void set_row_values(const std::vector<double>& sv);
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
    using iterator=typename container::iterator;
    using const_iterator=typename container::const_iterator;

    iterator begin() { return qubs.begin(); }
    iterator end() { return qubs.end(); }
    const_iterator begin() const { return qubs.begin(); }
    const_iterator end() const { return qubs.end(); }

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
    Qubits      get_sorted_qubs() const { 
        Qubits qubs_copy(qubs);
        std::sort(qubs_copy.begin(), qubs_copy.end());
        return qubs_copy;
    }
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