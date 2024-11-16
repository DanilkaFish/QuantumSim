#ifndef _SIMDATA
#define _SIMDATA

#include "inc/parameter.h"
#include "inc/GateSimulator/tensorspec.h"
#include "inc/QuantumCircuit/metaprovider.h"
#include "inc/QuantumCircuit/quantumcircuit.h"
#include <memory>


class NumSimProvider: public MetaProvider{
public:
    NumSimProvider(const QuantumCircuit& qc): MetaProvider{qc}, state(qc.get_qubits().size()) {}
    
    virtual void I(const Qubits& qubs) override;
    virtual void X(const Qubits& qubs) override;
    virtual void Y(const Qubits& qubs) override;
    virtual void Z(const Qubits& qubs) override;
    virtual void CX(const Qubits& qubs) override ;
    virtual void TOF(const Qubits& qubs ) override;
    virtual void H(const Qubits& qubs) override ;
    virtual void S(const Qubits& qubs) override ;
    virtual void Sdag(const Qubits& qubs) override ;
    //  PR(Double angle, const PauliString& ps);

    State state;
    ParameterSet ps;
};

// std::shared_ptr<SimData>
// typedef std::shared_ptr<SimData> SimDataPtr;

#endif