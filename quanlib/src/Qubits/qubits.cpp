// #include "inc/qubits.h"
#include "common.h"
// #include "inc/qubits.h"
// #include "src/"


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