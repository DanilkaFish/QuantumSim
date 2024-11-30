#ifndef _INST
#define _INST

#include <memory>
#include "common.h"
#include "QuantumCircuit.h"
// #include "metaprovider.h"
class MetaProvider;

class Instruction{
public:
    Instruction(const Qubits& qubs, const std::string& name="U"): qubits{qubs}, name{name} { }
    virtual                 ~Instruction(){};

    virtual void            apply(MetaProvider& ) { };
    virtual QuantumCircuit  decompose(const InstructionPtr& that)  ;
    std::string             get_name()   const { return name; }
    Qubits                  get_qubits() const {  return qubits; }
protected:
    Qubits qubits;
    std::string name;
};
typedef std::shared_ptr<Instruction> InstructionPtr;


class MagicInstruction: public Instruction{
public:
    MagicInstruction(QuantumCircuit tot): Instruction{tot.get_qubits(), "composed"} , qc{tot}{ }
    void apply(MetaProvider& md) override {
        for(auto i: qc){
            i->apply(md);
        }
    }
    QuantumCircuit decompose(const InstructionPtr& that) override;
private:
    QuantumCircuit qc{};
};


typedef std::shared_ptr<Instruction> InstructionPtr;



// class _U1: public Instruction{
// public:
//     _U1(const Qubits& qubs, DataPtr dptr): Instruction{qubs, "U1"}, dptr{dptr} {}
//     void apply(MetaProvider& md) override { md.U1(qubits, dptr); }
// private:
//     DataPtr dptr;
// };

// class _U2: public Instruction{
// public:
//     _U2(const Qubits& qubs, DataPtr dptr): Instruction{qubs, "U2"}, dptr{dptr} {}
//     void apply(MetaProvider& md) override { md.U2(qubits, dptr); }
// private:
//     DataPtr dptr;
// };




#endif