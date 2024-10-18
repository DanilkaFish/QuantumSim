#ifndef _QUANTUMCIRCUIT
#define _QUANTUMCIRCUIT

#include "random/genfactory.h"
#include "tensors/tensor.h"

#include <error.h>
#include <set>
#include <list>

inline void error_qubits_range(IntArr qubits, int n_qubits);
inline void error_qubits_coinc(IntArr qubits);

void validate_instruction_qubits(int n_qubits, const IntArr& qubits);

struct Instruction{

    void            evolve(tensor::State& s){ un.evolve(s, qubits); }
    void            reverse_qubits(const IntArr& qubits);
    tensor::HSMatrix un;
    IntArr          qubits;
};

using HSMatrixArr = std::list<Instruction>;


class QuantumCircuit{
public:
    QuantumCircuit(int n_qubits) : n_qubits{n_qubits}, s{n_qubits}{ s[0] = 1; }
    const HSMatrixArr& get_qc_data() const { return qc_data; };
    void              add_instruction(const tensor::HSMatrix un, const IntArr qubits);
    void              add_instruction(Instruction instr);
    void              compose(QuantumCircuit& circ);
    void              simplifiation();
    tensor::State     execute();
    tensor::State     s;
private:
    int        n_qubits;
    HSMatrixArr qc_data;
};

std::ostream& operator<<(std::ostream& os, const QuantumCircuit& qc);

namespace instr{
    const tensor::HSMatrix CX();
    const tensor::HSMatrix TOF();
    const tensor::HSMatrix X();
    const tensor::HSMatrix Y();
    const tensor::HSMatrix Z();
    const tensor::HSMatrix I();
    const tensor::HSMatrix H();
}
#endif

