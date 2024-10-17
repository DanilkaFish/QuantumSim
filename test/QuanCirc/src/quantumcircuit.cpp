#include "code/QuanCirc/inc/quantumcircuit.h"


inline void error_qubits_range(IntArr qubits, int n_qubits){
    std::string s = "qubits [" ;
    for(auto q: qubits) s += std::to_string(q) + ",";
    s += "] is not in range (0, " + std::to_string(n_qubits - 1) + ')';
    throw std::runtime_error(s);
}

inline void error_qubits_coinc(IntArr qubits){
    std::string s = "qubits [" ;
    for(auto q: qubits) s += std::to_string(q) + ",";
    s += "] have the coincidence;";
    throw std::runtime_error(s);
}

void validate_instruction_qubits(int n_qubits, const IntArr& qubits){
    for (int qubit: qubits){
        if ((qubit >= n_qubits) || (qubit < 0))
            error_qubits_range(qubits, n_qubits);
    }
    std::set<int> sq{qubits.begin(), qubits.end()};
    if (sq.size() != qubits.size())
        error_qubits_coinc(qubits);
}

void Instruction::reverse_qubits(const IntArr& qubits){
    IntArr axis_to_move;
    IntArr new_qubits = qubits;
    for (int i=0; i<qubits.size(); i++){
        axis_to_move.push_back(qubits[i] * 2);
        axis_to_move.push_back(qubits[i] * 2 + 1);
        new_qubits[qubits[i]] = this->qubits[i];

    }
    un.move_axis(std::move(axis_to_move));
}

void QuantumCircuit::add_instruction(const tensor::Unitary un, const IntArr qubits){
    validate_instruction_qubits(n_qubits, qubits);
    qc_data.push_back(Instruction{un, qubits});
}


void QuantumCircuit::add_instruction(Instruction instr){
    qc_data.push_back(instr);
}
    
void QuantumCircuit::compose(QuantumCircuit& circ){
    if (n_qubits == circ.n_qubits){
        for (auto inst : circ.qc_data)
            add_instruction(inst);
    }else{
        std::cerr << "WARNING : different circuit sizes " << n_qubits << " and " << circ.n_qubits << std::endl; 
    }
}

tensor::State QuantumCircuit::execute(){
    tensor::State s_test = s;
    for(auto x: qc_data){
        x.evolve(s_test);
    }
    return s_test;
}
void QuantumCircuit::simplification(){
    std::vector<Instruction*> pred(n_qubits);
    int size=0;
    Instruction* InstPtr;
    bool equal_qubits = true;

    for(auto x = qc_data.begin(); x != qc_data.end(); x++){
        auto qubits = x->qubits;
        equal_qubits = bool(pred[qubits[0]]) && (pred[qubits[0]]->qubits.size() == qubits.size());
        if (equal_qubits){
            for (int i=0; i < qubits.size(); i++){
                if (qubits[i] != (pred[qubits[0]] -> qubits)[i]){
                    equal_qubits = false;
                    break;
                }
            }
            if (qubits.size() == 2 && (pred[qubits[0]] -> qubits).size() == 2){
                if (qubits[0] == (pred[qubits[0]] -> qubits)[1] && qubits[1] == (pred[qubits[0]] -> qubits)[0]){
                    std::cout << x->un << std::endl;
                    std::cout << x->qubits[0] << std::endl;
                    x->reverse_qubits(IntArr{1,0});
                    std::cout << x->un << std::endl;
                    std::cout << x->qubits[0] << std::endl;
                    qubits = x->qubits;
                    equal_qubits == true;
                }
            }
            if (equal_qubits){
                pred[qubits[0]]->un = (x->un) * (pred[qubits[0]]->un) ;
                auto old = x;
                x--;
                qc_data.erase(old);
            } 
        }
        if (!equal_qubits){
            for (auto q: qubits){
                if (pred[q]){
                    for (auto qpred: pred[q]->qubits){
                        pred[qpred] = nullptr;
                    }
                }
            }
            for (auto q: qubits){
                pred[q] = &(*x);
            }
        }

    }
};

std::ostream& operator<<(std::ostream& os, const QuantumCircuit& qc){
    for (auto x: qc.get_qc_data()){
        os << x.un.get_name() << " [";
        for (auto it = x.qubits.begin(); it != x.qubits.end(); it++){
            os << *it << ",";
        }
        os << "]\n";
    }
    return os << "\n";
}

const tensor::Unitary instr::TOF(){
    static tensor::Unitary _TOF({1,0,0,0,0,0,0,0,
                                 0,1,0,0,0,0,0,0,
                                 0,0,1,0,0,0,0,0,
                                 0,0,0,1,0,0,0,0,
                                 0,0,0,0,1,0,0,0,
                                 0,0,0,0,0,1,0,0,
                                 0,0,0,0,0,0,0,1,
                                 0,0,0,0,0,0,1,0,});
    return _TOF;
}
const tensor::Unitary instr::CX(){
    static tensor::Unitary _CX({1,0,0,0,
                                0,1,0,0,
                                0,0,0,1,
                                0,0,1,0});
    return _CX;
}

const tensor::Unitary instr::X(){
    static tensor::Unitary _X({0, 1,
                               1, 0});
    return _X;
}
const tensor::Unitary instr::Y(){
    static tensor::Unitary _Y({0, -tensor::i, 
                               tensor::i, 0});
    return _Y;
}
const tensor::Unitary instr::Z(){
    static tensor::Unitary _Z({1, 0,
                               0, 1});
    return _Z;
}
const tensor::Unitary instr::I(){
    static tensor::Unitary _I({1, 0,
                               0, 1});
    return _I;
}

const double A = 1.0/sqrt(2);
const tensor::Unitary instr::H(){
    static tensor::Unitary _H({A, A,
                               A, -A});
    return _H;
}
