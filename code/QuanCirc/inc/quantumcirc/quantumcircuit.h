#ifndef _QUANTUMCIRCUIT
#define _QUANTUMCIRCUIT


#include "code/QuanCirc/inc/random/genfactory.h"
#include "code/QuanCirc/inc/tensors/tensor.h"

#include <error.h>
#include <set>
#include <utility>
#include <list>

#include "code/QuanCirc/inc/error.h"

void validate_instruction_qubits(int n_qubits, const IntArr& qubits);


struct Instruction{
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

// TODO validate qubits (n_qubits может стать не актуальным по мере добавления интсрукций)
class QuantumCircuit{
public:
    QuantumCircuit(int n_qubits) : n_qubits{n_qubits}, s{n_qubits}{ s[0] = 1; }
    const HSMatrixArr& get_qc_data() const { return qc_data; };
    void               add_instruction(const tensor::HSMatrix un, const IntArr qubits);
    void               add_instruction(const std::vector<std::pair<tensor::HSMatrix, IntArr>> u_qub);
    void               add_instruction(Instruction instr);
    Instruction        to_instruction();
    void               compose(QuantumCircuit& circ);
    void               simplification();
    tensor::State      execute();
    tensor::State      s;
private:
    int         n_qubits;
    HSMatrixArr qc_data;
};

std::ostream& operator<<(std::ostream& os, const QuantumCircuit& qc);




#endif

