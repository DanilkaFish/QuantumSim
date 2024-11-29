#ifndef _COMMON
#define _COMMON

#include <complex>
#include <vector>
#include <memory>
#include <algorithm>


typedef std::complex<double> DataType;
typedef std::vector<DataType> Data;
typedef std::shared_ptr<std::vector<DataType>> DataPtr;
class Instruction;
typedef std::shared_ptr<Instruction> InstructionPtr;

namespace i{ constexpr DataType i = {0,1}; }


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

std::ostream& operator<<(std::ostream& os, const Qubits& qubs);
std::ostream& operator<<(std::ostream& os, const Qubit& qub);
bool operator<(Qubit l, Qubit r);
bool operator>(Qubit l, Qubit r);
bool operator==(Qubit l, Qubit r);
bool operator!=(Qubit l, Qubit r);

#endif