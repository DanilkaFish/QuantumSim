#ifndef _QC
#define _QC

#include <string>
#include <vector>
#include <memory>
#include "drawer.h"
#include "instruction.h"


void validate_in_range(Qubits all, Qubits in);


class InstructionSet{
public:
    using container=std::vector<InstructionPtr>; 
    using iterator=typename container::iterator;
    using const_iterator=typename container::const_iterator;

    iterator begin() { return ins.begin(); }
    iterator end() { return ins.end(); }
    const_iterator begin() const { return ins.begin(); }
    const_iterator end() const { return ins.end(); }

    InstructionSet() {}
    InstructionSet(std::initializer_list<InstructionPtr> in): ins{in} {}
    template<class container>
    InstructionSet(container& vec) {
        for(auto& x: vec){
            ins.push_back(x);
        }
    }
    InstructionPtr compose();
    void push_back( InstructionPtr in) { ins.push_back(in); }
    std::size_t size() const { return ins.size(); }
private:
    container ins;
};


class MagicInstruction: public Instruction{
public:
    MagicInstruction(InstructionSet& tot): ins{tot} { }
    void apply() override {
        for(auto i: ins){
            i->apply();
        }
    }
    InstructionSet decompose() override;
private:
    InstructionSet ins;
};


class QuantumCircuit{
public:
    QuantumCircuit(Qubits qubs): qubits{qubs} {}
    QuantumCircuit(const InstructionSet& ins, Qubits qubs) : ins{ins}, qubits{qubs} {} 
    QuantumCircuit(const InstructionSet& ins) : ins{ins} {
        for (auto x: ins){
            for (auto qub: x->get_qubits())
                qubits.push_back(qub);
        }
    } 
    QuantumCircuit(QuantumCircuit& qc) = default;
    void draw() const;
    const InstructionSet& get_instr() const { return ins;} 
    Qubits get_qubits() const { return qubits; };
    void add_instruction(InstructionPtr in) { validate_in_range(qubits, in->get_qubits()); ins.push_back(in);};
    void compose(QuantumCircuit& qc) {this->add_instruction(qc.ins.compose()); };
    QC_representation get_qcr() const;
    void decompose();

private:
    Drawer* drawer;
    Qubits qubits;
    InstructionSet ins;
};

class Executor{
public:
    Executor(QuantumCircuit& qc): qc{qc} {}
    void run(){ 
        this->SetUp();
        for(auto ops: qc.get_instr()){
            ops->apply();
        }
    };
protected:
    virtual void SetUp() = 0;
    QuantumCircuit& qc;
};
#endif