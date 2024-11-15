#include "inc/GateSimulator/unitary.h"

InstructionPtr Gate::I(Qubit qub){
    static DataPtr dptr(new Data{0,1,
                                 1,0});
    return makeInsPtr( new FixedUnitary{Operator{{qub}, dptr}});
}

InstructionPtr Gate::X(Qubit qub){
    static DataPtr dptr{new Data{0,1,
                                 1,0}};
    return makeInsPtr( new FixedUnitary{Operator{{qub}, dptr}});
}

InstructionPtr Gate::Y(Qubit qub){
    static DataPtr dptr{new Data{0,{0,-1},
                                {0,1},0}};
    return makeInsPtr( new FixedUnitary{Operator{{qub}, dptr}});
}

InstructionPtr Gate::Z(Qubit qub){
    static DataPtr dptr{new Data{1,0,
                                 0,-1}};
    return makeInsPtr( new FixedUnitary{Operator{{qub}, dptr}});
}

InstructionPtr Gate::S(Qubit qub){
    static DataPtr dptr{new Data{1,0,
                                 0,{0,1}}};
    return makeInsPtr( new FixedUnitary{Operator{{qub}, dptr}});
}

InstructionPtr Gate::Sdag(Qubit qub){
    static DataPtr dptr{new Data{1,0,
                                 0,{0,-1}}};
    return makeInsPtr( new FixedUnitary{Operator{{qub}, dptr}});
}

InstructionPtr Gate::CX(Qubit ctrl, Qubit tar){
    static DataPtr dptr{new Data{1,0,0,0,
                                 0,1,0,0,
                                 0,0,0,1,
                                 0,0,1,0}};
    return makeInsPtr( new FixedUnitary{Operator{{ctrl, tar}, dptr}});
}

const double A = 1.0/sqrt(2);
InstructionPtr Gate::H(Qubit qub){
    static DataPtr dptr{new Data{A, A,
                                 A,-A}};
    return makeInsPtr( new FixedUnitary{Operator{{qub}, dptr}});
}

InstructionPtr Gate::TOF(Qubit ctrl1, Qubit ctrl2, Qubit tar){
    static DataPtr dptr{new Data{1,0,0,0,0,0,0,0,
                                 0,1,0,0,0,0,0,0,
                                 0,0,1,0,0,0,0,0,
                                 0,0,0,1,0,0,0,0,
                                 0,0,0,0,1,0,0,0,
                                 0,0,0,0,0,1,0,0,
                                 0,0,0,0,0,0,0,1,
                                 0,0,0,0,0,0,1,0}};
    return makeInsPtr( new FixedUnitary{Operator{{ctrl1, ctrl2, tar}, dptr}});
}
