#ifndef _QUANTUMCIRCUIT
#define _QUANTUMCIRCUIT


#include "code/QuanCirc/inc/random/genfactory.h"
#include "code/QuanCirc/inc/tensors/tensor.h"
#include "qubits.h"

#include <error.h>
#include <set>
#include <utility>
#include <list>

#include "code/QuanCirc/inc/error.h"

void validate_instruction_qubits(int n_qubits, const IntArr& qubits);


class Instruction{
public:
    Instruction(const tensor::HSMatrix& hs, IntArr qubits):un{hs}, qubits{qubits}{
        if (hs.get_n_qubits() != qubits.size()){
            custom_error("wrong sizes of qubits and unitary matrix");
        }
    }
    void             evolve(tensor::State& s){ un.evolve(s, qubits); }
    void             reverse_qubits(const IntArr& qubits);
    tensor::HSMatrix un;
    IntArr           qubits;
};
Instruction instruction_prod(const Instruction& l, const Instruction& r);
using HSMatrixArr = std::list<Instruction>;


class QuantumCircuit{
public:
    QuantumCircuit(int n_qubits) : qubs{n_qubits}, s{n_qubits}{ s[0] = 1; }
    virtual ~QuantumCircuit(){};
    const HSMatrixArr& get_qc_data() const { return qc_data; };
    void               add_instruction(const tensor::HSMatrix un, const Qubits qubits);
    void               add_instruction(const std::vector<std::pair<tensor::HSMatrix, Qubits>> u_qub);
    void               add_instruction(Instruction instr);
    Instruction        to_instruction();
    void               compose(QuantumCircuit& circ);
    void               simplification();
    tensor::State      execute();
    tensor::State      s;
private:
    Qubits      qubs;
    HSMatrixArr qc_data;
};

std::ostream& operator<<(std::ostream& os, const QuantumCircuit& qc);

#endif

