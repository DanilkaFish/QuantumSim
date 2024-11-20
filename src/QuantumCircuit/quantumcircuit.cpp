#include "inc/QuantumCircuit/__init__.h"
#include <utility>
// #include "metaprovider.h"
// TODO
void validate_in_range(Qubits all, Qubits in){}

InstructionPtr makeInsPtr(Instruction *in){
    return std::shared_ptr<Instruction>(in);
}

InstructionPtr QuantumCircuit::to_instruction(){
    return makeInsPtr(new MagicInstruction(*this));
}

QuantumCircuit Instruction::decompose() {
    return QuantumCircuit({InstructionPtr(this)});
}

QuantumCircuit MagicInstruction::decompose()  {
    return this->qc;
}

void MetaProvider::run() {
    SetUp();
    for(auto ins: qc){
        ins->apply(*this);
    }
}

std::string instruction_repr(const InstructionPtr& inptr){
    return inptr->get_name() + ":" +  inptr->get_qubits().to_str() + ";";
}

QC_representation QuantumCircuit::get_qcr() const {
    QC_representation toto;
    toto.qubits = qubs;
    for(const auto ops: ins){
        toto.s = toto.s + instruction_repr(ops);
    }
    return toto;
}

void QuantumCircuit::add_instruction(InstructionPtr in) { 
    ins.push_back(in); 
    for (Qubit x: in->get_qubits()){
        qubs.insert(x);
    }
}

void QuantumCircuit::compose(const QuantumCircuit& qc){
    add_instruction(InstructionPtr{new MagicInstruction(qc)});

}
// void QuantumCircuit::compose(QuantumCircuit&& qc){
//     this->add_instruction(InstructionPtr( new MagicInstruction(std::move(qc))));
// }

QuantumCircuit QuantumCircuit::decompose() {
    QuantumCircuit qc;
    for(auto x: (*this)){
        for (auto y: x->decompose()){
            qc.add_instruction(y);
        }
    }
    return qc;
};


InstructionPtr BaseInstr::X(Qubit qub) { return InstructionPtr{ new _X{{qub}}}; }
InstructionPtr BaseInstr::Y(Qubit qub) { return InstructionPtr{ new _Y{{qub}}}; }
InstructionPtr BaseInstr::Z(Qubit qub) { return InstructionPtr{ new _Z{{qub}}}; }
InstructionPtr BaseInstr::I(Qubit qub) { return InstructionPtr{ new _I{{qub}}}; }
InstructionPtr BaseInstr::S(Qubit qub) { return InstructionPtr{ new _S{{qub}}}; }
InstructionPtr BaseInstr::H(Qubit qub) { return InstructionPtr{ new _H{{qub}}}; }
InstructionPtr BaseInstr::Sdag(Qubit qub) { return InstructionPtr{ new _Sdag{{qub}}}; }
InstructionPtr BaseInstr::CX(Qubit ctrl, Qubit tar) { return InstructionPtr{ new _CX{{ctrl, tar}}}; }
InstructionPtr BaseInstr::TOF(Qubit ctrl1, Qubit ctrl2, Qubit tar) { return InstructionPtr{ new _TOF{{ctrl1, ctrl2, tar}}}; }
InstructionPtr BaseInstr::U1(Qubit qub, DataPtr dptr) { return InstructionPtr{ new _U1{{qub}, dptr}}; }
InstructionPtr BaseInstr::U2(Qubit qub1, Qubit qub2, DataPtr dptr) { return InstructionPtr{ new _U2{{qub1, qub2}, dptr}}; }
InstructionPtr BaseInstr::U(Qubits qubs, DataPtr dptr) { return InstructionPtr{ new _U{qubs, dptr}}; }
// void QuantumCircuit::draw() const {
//     drawer->draw(get_qcr());
// }


// void QuantumCircuit::decompose(){
//     QuantumCircuit new_ins;
//     for(auto x: ins){
//         for (auto y: x->decompose()){
//             new_ins.push_back(y);
//         }
//     }
//     this->ins = new_ins;
// }