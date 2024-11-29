#ifndef _GATESIM
#define _GATESIM
#include <string>
#include <utility>

#include "common.h"
#include "metaprovider.h"
#include "QuantumCircuit.h"
    
class TensorProvider: public MetaProvider{
public:
    TensorProvider(const QuantumCircuit& qc): MetaProvider{qc},
                                            dptr(new Data(1<<qc.get_qubits().size())) { 
        (*dptr)[0] = 1; state = State(qc.get_qubits(), dptr); 
    }
    
    virtual void I(const Qubits& qubs) override;
    virtual void X(const Qubits& qubs) override;
    virtual void Y(const Qubits& qubs) override;
    virtual void Z(const Qubits& qubs) override;
    virtual void CX(const Qubits& qubs) override ;
    virtual void TOF(const Qubits& qubs ) override;
    virtual void H(const Qubits& qubs) override ;
    virtual void S(const Qubits& qubs) override ;
    virtual void Sdag(const Qubits& qubs) override ;
    // virtual void U1(const Qubits& qubs, DataPtr dptr) override ;
    // virtual void U2(const Qubits& qubs, DataPtr dptr) override ;
    virtual void U(const Qubits& qubs, DataPtr dptr) override ;
    State state;
    DataPtr dptr;
private:
    void inplace_evolve(const Operator& op);
};

class Operator;
class State;



namespace bm{
    Operator X(Qubit);
    Operator Y(Qubit);
    Operator Z(Qubit);
    Operator I(Qubit);
    Operator I(const Qubits& qubs);
    Operator H(Qubit);
    Operator S(Qubit);
    Operator Sdag(Qubit);
    Operator CX(Qubit trg, Qubit ctrl);
    Operator TOF(Qubit ctrl1, Qubit ctrl2, Qubit trg);
    Operator PR(const PauliString& pauli, double theta);
};

#endif