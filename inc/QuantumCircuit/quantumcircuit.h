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

    iterator begin() { return ins.begin(); }
    iterator end() { return ins.end(); }
    const_iterator begin() const { return ins.begin(); }
    const_iterator end() const { return ins.end(); }

    QuantumCircuit() {}
    // QuantumCircuit(const QuantumCircuit& )=default;
    // QuantumCircuit(QuantumCircuit&& )=default;
    QuantumCircuit(std::initializer_list<InstructionPtr> in): ins{in} {std::cerr << "here2"; }
    
    Qubits get_qubits() const { return qubs; } 
    std::size_t size() const { return ins.size(); }
    
    template<class cont>
    QuantumCircuit(const cont& vec): ins{vec} { }

    InstructionPtr to_instruction();

    void add_instruction( InstructionPtr in);
    QC_representation get_qcr() const;
    void compose(QuantumCircuit& qc);
    QuantumCircuit decompose();
private:
    container ins;
    Qubits qubs;
};


typedef std::shared_ptr<const QuantumCircuit> QuantumCircuitPtr;

class MagicInstruction: public Instruction{
public:
    MagicInstruction(const QuantumCircuit& tot): Instruction{tot.get_qubits(), "composed"}, qc{tot} { }
    MagicInstruction(QuantumCircuit&& tot): Instruction{tot.get_qubits(), "composed"}, qc{tot} { }
    void apply(MetaProvider& md) override {
        for(auto i: qc){
            i->apply(md);
        }
    }
    QuantumCircuit decompose() override;
private:
    QuantumCircuit qc;
};





// class QuantumCircuit{
// public:
//     // QuantumCircuit(Qubits qubs): qubs{qubs} {}
//     QuantumCircuit(const QuantumCircuit& ins) : ins{ins} {} 
//     // QuantumCircuit(const QuantumCircuit& ins) : ins{ins} {} 
//     QuantumCircuit(QuantumCircuit& qc) = default;
//     void draw() const;
//     const QuantumCircuit& get_instr() const { return ins;} 
//     Qubits get_qubits() const { return ins.get_qubits(); };
//     void add_instruction(InstructionPtr in) { 
//         ins.push_back(in);

//     };
//     void compose(QuantumCircuit& qc) {this->add_instruction(qc.ins.compose()); };
//     QC_representation get_qcr() const;
//     void decompose();

// private:
//     DrawerPtr drawer;
//     QuantumCircuit ins;
// };

// class Executor{
// public:
//     Executor(QuantumCircuit& qc): qc{qc} {}
//     void run(){ 
//         this->SetUp();
//         for(auto ops: qc.get_instr()){
//             ops->apply(md);
//         }
//     };
// protected:
//     virtual void SetUp() = 0;
//     QuantumCircuit& qc;
// };

#endif