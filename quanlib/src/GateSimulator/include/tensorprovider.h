#ifndef _tensorprovider
#define _tensorprovider

// #include "inc/parameter.h"
#include "tensorspec.h"
#include "metaprovider.h"
#include "QuantumCircuit.h"

// class Param

class TensorProvider: public MetaProvider{
public:
    TensorProvider(const QuantumCircuit& qc): MetaProvider{qc}, state(qc.get_qubits()) {  }
    
    virtual void I(const Qubits& qubs) override;
    virtual void X(const Qubits& qubs) override;
    virtual void Y(const Qubits& qubs) override;
    virtual void Z(const Qubits& qubs) override;
    virtual void CX(const Qubits& qubs) override ;
    virtual void TOF(const Qubits& qubs ) override;
    virtual void H(const Qubits& qubs) override ;
    virtual void S(const Qubits& qubs) override ;
    virtual void Sdag(const Qubits& qubs) override ;
    virtual void U1(const Qubits& qubs, DataPtr dptr) override ;
    virtual void U2(const Qubits& qubs, DataPtr dptr) override ;
    virtual void U(const Qubits& qubs, DataPtr dptr) override ;
    //  PR(Double angle, const PauliString& ps);

    State state;
    // ParameterSet ps;
};



#endif