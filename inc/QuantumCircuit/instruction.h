#ifndef _INST
#define _INST

#include <memory>
#include "inc/qubits.h"
// #include "metaprovider.h"
// #include "quantumcircuit.h"
class QuantumCircuit;
class MetaProvider;
class Instruction;
typedef std::shared_ptr<Instruction> InstructionPtr;
class Instruction{
public:
    Instruction(const Qubits& qubs, const std::string& name="U"): qubits{qubs}, name{name} { }
    virtual                 ~Instruction(){};

    virtual void            apply(MetaProvider& ) { std::cerr << "HelloBase"; };
    virtual QuantumCircuit  decompose(const InstructionPtr& that)  ;
    std::string             get_name()   const { return name; }
    Qubits                  get_qubits() const {  return qubits; }
protected:
    Qubits qubits;
    std::string name;
};



// std::string instruction_repr(Instruction in);

typedef std::shared_ptr<Instruction> InstructionPtr;

InstructionPtr makeInsPtr(Instruction *in);



#endif