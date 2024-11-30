#include "code/QuanCirc/inc/quantumcirc/quantumcircuit.h"
#include "algorithm"
#include <map>
#include <algorithm>

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

void QuantumCircuit::add_instruction(const tensor::HSMatrix un, const IntArr qubits){
    validate_instruction_qubits(n_qubits, qubits);
    qc_data.push_back(Instruction{un, qubits});
}


void QuantumCircuit::add_instruction(const Instruction& instr){
    qc_data.push_back(instr);
}

void QuantumCircuit::add_instruction(const std::vector<std::pair<tensor::HSMatrix, IntArr>> u_qub){
    for(auto& x: u_qub){
        this->add_instruction(x.first, x.second);
    }
}

    
void QuantumCircuit::compose(const QuantumCircuit& circ){
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
// TODO нужно разобраться с перестановкой осей и новыми кубитами
Instruction instruction_prod(const Instruction& l, const Instruction& r){
    IntArr new_qubits;
    IntArr pl;
    IntArr pr;
    IntArr axis_transp;
    std::map<int, int> ndl;
    std::map<int, int> ndr;
    std::map<int, std::pair<int,int>> qubits_map;

    int nl = l.qubits.size();
    int nr = r.qubits.size();

    for (int i=0; i<nl; i++){
        qubits_map[l.qubits[i]] = std::make_pair(i, -1);
        ndl[l.qubits[i]] = i;
    }
    for (int i=0; i<nr; i++){
        if (qubits_map.find(r.qubits[i]) == qubits_map.end()){
            qubits_map[r.qubits[i]] = std::make_pair(-1, i);

        }else{
            qubits_map[r.qubits[i]].second = i;
            pl.push_back(qubits_map[r.qubits[i]].first);
            pr.push_back(i);
        }
        ndr[r.qubits[i]] = i;
    }

    for (auto it: qubits_map){
        new_qubits.push_back(it.first);
        if (it.second.first == -1){
            for(auto it2: qubits_map)
                if ((it.second.second > it2.second.second) & (it2.second.first != -1) & (it2.second.second != -1)) ndr[it.first]--;
        }else if (it.second.second == -1){
            for(auto it2: qubits_map)
                if ((it.second.first > it2.second.first) & (it2.second.first != -1) & (it2.second.second != -1)) ndl[it.first]--;
        }
    }

    for (auto it: qubits_map){
        if (it.second.first != -1) axis_transp.push_back(it.second.first);
        else axis_transp.push_back(ndr[it.first] + 2*nl - pl.size());
    }

    for (auto it: qubits_map){
        if (it.second.second == -1) axis_transp.push_back(ndl[it.first] + nl );
        else axis_transp.push_back(2*nl - 2*pl.size()  + nr + it.second.second);
    }

    for(auto x: l.qubits){
        std::cout<< x << " ";
    }

    tensor::HSMatrix res = tensor::hsmatrixdot(l.un, r.un, pl, pr);

    res.move_axis(std::move(axis_transp));
    return Instruction{res, new_qubits};
}

Instruction QuantumCircuit::to_instruction(){
    if (qc_data.size() == 0)
        return Instruction{tensor::HSMatrix{0}, IntArr{}};
    auto it = qc_data.begin();
    Instruction In = (*it);
    it++;
    for (; it != qc_data.end(); it++){
        In = instruction_prod(In, *it);
    }

    return In;
}