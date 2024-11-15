#ifndef _INST
#define _INST

#include <memory>
#include "inc/qubits.h"
#include "metadata.h"

class InstructionSet;

class Instruction{
public:
    Instruction(){}
    Instruction(Qubits qubs): qubits{qubs} {}
    Instruction(const Instruction& in)=default;
    virtual ~Instruction(){};
    std::string get_name() const { return name; }
    Qubits get_qubits() const { return qubits; }
    virtual void apply() {};
    virtual void attach_meta(const MetaDataPtr& ) {};
    virtual InstructionSet decompose();
protected:
    Qubits qubits;
    std::string name = "U";
};

// std::string instruction_repr(Instruction in);

typedef std::shared_ptr<Instruction> InstructionPtr;

InstructionPtr makeInsPtr(Instruction *in);

#endif