#ifndef _METADATA
#define _METADATA
#include <memory>
#include "inc/qubits.h"

class QuantumCircuit;

class MetaProvider{
public:
    MetaProvider(const QuantumCircuit& qc): qc{qc} {}
    // virtual void I(Qubit qub) {};
    // virtual void X(Qubit qub) {};
    // virtual void Y(Qubit qub) {};
    // virtual void Z(Qubit qub) {};
    // virtual void CX(Qubit ctrl, Qubit tar) {};
    // virtual void TOF(Qubit ctrl1, Qubit ctrl2, Qubit trg) {};
    // virtual void H(Qubit qub) {};
    // virtual void S(Qubit qub) {};
    // virtual void Sdag(Qubit qub) {};

    virtual void X(const Qubits& qubs) {};
    virtual void Y(const Qubits& qubs) {};
    virtual void Z(const Qubits& qubs) {};
    virtual void I(const Qubits& qubs) {};
    virtual void H(const Qubits& qubs) {};
    virtual void S(const Qubits& qubs) {};
    virtual void Sdag(const Qubits& qubs) {};
    virtual void CX(const Qubits& qubs) {};
    virtual void TOF(const Qubits& qubs) {};
    virtual ~MetaProvider() {};
    virtual void SetUp() {}
    void run();
protected:
    const QuantumCircuit& qc;
};

typedef std::shared_ptr<MetaProvider> MetaProviderPtr;
#endif