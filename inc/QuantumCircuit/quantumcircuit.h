#ifndef _QC
#define _QC

#include <string>
#include <vector>
#include <memory>
#include "instruction.h"
#include "metaprovider.h"
#include "drawer.h"

void validate_in_range(Qubits all, Qubits in);


class QuantumCircuit{
public:
    using container=std::vector<InstructionPtr>; 
    using iterator=typename container::iterator;
    using const_iterator=typename container::const_iterator;
    using reverse_iterator=typename container::reverse_iterator;
    using const_reverse_iterator=typename container::const_reverse_iterator;
    
    iterator begin() { return ins.begin(); }
    iterator end() { return ins.end(); }
    const_iterator begin() const { return ins.begin(); }
    const_iterator end() const { return ins.end(); }

    reverse_iterator rbegin() { return ins.rbegin(); }
    reverse_iterator rend() { return ins.rend(); }
    const_reverse_iterator rbegin() const { return ins.rbegin(); }
    const_reverse_iterator rend() const { return ins.rend(); }
    
    QuantumCircuit(): ins{}, qubs{} {}
    QuantumCircuit(std::initializer_list<InstructionPtr> in) : ins{in} { }
    QuantumCircuit(const QuantumCircuit& qc): ins{qc.ins} {} 
    Qubits get_qubits() const { return qubs; } 
    std::size_t size() const { return ins.size(); }
    
    template<class cont>
    QuantumCircuit(const cont& vec): ins{vec} { }

    InstructionPtr to_instruction();

    void add_instruction(InstructionPtr in);
    QC_representation get_qcr() const;
    void compose(const QuantumCircuit& qc);
    QuantumCircuit decompose();
private:
    container ins;
    Qubits qubs;
};


typedef std::shared_ptr<const QuantumCircuit> QuantumCircuitPtr;

class MagicInstruction: public Instruction{
public:
    MagicInstruction(QuantumCircuit tot): Instruction{tot.get_qubits(), "composed"} , qc{tot}{ }
    void apply(MetaProvider& md) override {
        for(auto i: qc){
            i->apply(md);
        }
    }
    QuantumCircuit decompose() override;
private:
    QuantumCircuit qc{};
};

#endif