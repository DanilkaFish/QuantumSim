#include "inc/QuantumCircuit/quantumcircuit.h"
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
    std::cerr << "here" << std::endl;
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

void QuantumCircuit::add_instruction( InstructionPtr in) { 
    ins.push_back(in); 
    for (Qubit x: in->get_qubits()){
        qubs.insert(x);
    }
}
// std::size_t QuantumCircuit::size() const { return ins.size(); }

void QuantumCircuit::compose(QuantumCircuit& qc){
    this->add_instruction(InstructionPtr( new MagicInstruction(qc)));
}
// void QuantumCircuit::compose(QuantumCircuit&& qc){
    // this->add_instruction(InstructionPtr( new MagicInstruction(std::move(qc))));
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