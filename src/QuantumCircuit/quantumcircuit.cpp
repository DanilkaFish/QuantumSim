#include "inc/QuantumCircuit/__init__.h"

// TODO
void validate_in_range(Qubits all, Qubits in){}

InstructionPtr makeInsPtr(Instruction *in){
    return std::shared_ptr<Instruction>(in);
}

InstructionPtr InstructionSet::compose(){
    return makeInsPtr(new MagicInstruction(*this));
}

InstructionSet Instruction::decompose(){
    return InstructionSet({makeInsPtr(this)});
}

InstructionSet MagicInstruction::decompose(){
    return this->ins;
}

std::string instruction_repr(const InstructionPtr& inptr){
    return inptr->get_name() + ":" +  inptr->get_qubits().to_str() + ";";
}

QC_representation QuantumCircuit::get_qcr() const {
    QC_representation toto;
    toto.qubits = qubits;
    for(const auto ops: ins){
        toto.s = toto.s + instruction_repr(ops);
    }
    return toto;
}

void QuantumCircuit::draw() const {
    drawer->draw(get_qcr());
}


void QuantumCircuit::decompose(){
    InstructionSet new_ins;
    for(auto x: ins){
        for (auto y: x->decompose()){
            new_ins.push_back(y);
        }
    }
    this->ins = new_ins;
}