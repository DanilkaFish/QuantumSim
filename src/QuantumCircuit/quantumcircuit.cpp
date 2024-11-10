#include "inc/QuantumCircuit/__init__.h"

// TODO
void validate_in_range(Qubits all, Qubits in){}

InstructionPtr makeInsPtr(Instruction *in){
    return std::shared_ptr<Instruction>(in);
}

std::ostream& operator<<(std::ostream& os, const Qubits& qubs){
    os << '(';
    for(auto x: qubs.qubs){
            os << x <<  ',' ;
    }
    return os << ") ";
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

QC_representation QuantumCircuit::get_qcr() const {
    QC_representation toto;
    toto.qubits = qubits;
    for(const auto ops: ins){
        toto.s = toto.s + ops->get_name() + ":" +  ops->get_qubits().to_str() + ";";
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