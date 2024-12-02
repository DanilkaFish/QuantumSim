// #include "inc/qubits.h"
#include "common.h"
// #include "inc/qubits.h"
// #include "src/"

PauliString::PauliString(const std::string& s, const Qubits& qubs){
    if (s.size() != qubs.size()){
        throw QException("Wrong sizes in paulistring : s.size = " + std::to_string(s.size()) + ", qubs.size = " + std::to_string(qubs.size()));
    }
    
    for (int i=0; i<s.size(); i++){
        switch (tolower(s[i])){
            case 'x':
            case 'y':
            case 'z':
                ps.push_back(std::make_pair(s[i], qubs[i]));
                this->s.push_back(s[i]);
                this->qubs.insert(qubs[i]);
                break;
            case 'i':
                break;
            default:
                throw QException("wrong pauli string format : " + s[i]);
        }
    }
}

std::string PauliString::get_name() const { 
    std::string name;
    for (auto x: ps){
        name += x.first + "_" + std::to_string(x.second.num) + " ";
    }
    name += '\n';
    return s; 
}


int qubs_to_int(const Qubits& qubs){
    int num =0;
    for(auto x: qubs){
        num += 1 << x.num;
    }
    return num;
}

bool qubs_in_qubs(const Qubits& qubsl, const Qubits& qubsr){
    int l = qubs_to_int(qubsl);
    int r = qubs_to_int(qubsr);
    if ((((l^r) & r) == 0) || (((l^r) & l) == 0))
        return true;
    return false;
}

std::ostream& operator<<(std::ostream& os, const Qubits& qubs){
    os << '(';
    for(auto x: qubs){
            os << x <<  ',' ;
    }
    return os << ") ";
}

std::ostream& operator<<(std::ostream& os, const Qubit& qub){
    return os << qub.num;
}


std::ostream& operator<<(std::ostream& os, const PauliString& ps){
    return os << ps.get_name();
}

bool operator<(Qubit l, Qubit r){
    return l.num < r.num;
}

bool operator>(Qubit l, Qubit r){
    return l.num > r.num;
}
bool operator==(Qubit l, Qubit r){
    return l.num == r.num;
}
bool operator!=(Qubit l, Qubit r){
    return l.num != r.num;
}