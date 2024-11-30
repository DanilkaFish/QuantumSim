#ifndef _METADATA
#define _METADATA
#include <memory>
#include "inc/qubits.h"
#include "inc/stddata.h"


class QuantumCircuit;

class MetaProvider{
public:
    MetaProvider(const QuantumCircuit& qc): qc{qc} {}
    virtual void X(const Qubits& qubs) {};
    virtual void Y(const Qubits& qubs) {};
    virtual void Z(const Qubits& qubs) {};
    virtual void I(const Qubits& qubs) {};
    virtual void H(const Qubits& qubs) {};
    virtual void S(const Qubits& qubs) {};
    virtual void Sdag(const Qubits& qubs) {};
    virtual void CX(const Qubits& qubs) {};
    virtual void TOF(const Qubits& qubs) {};
    virtual void U1(const Qubits& qubs, DataPtr dptr) {};
    virtual void U2(const Qubits& qubs, DataPtr dptr) {};
    virtual void U(const Qubits& qubs, DataPtr dptr) {};
    virtual ~MetaProvider() {};
    virtual void SetUp() {}
    void run();
protected:
    const QuantumCircuit& qc;
};

typedef std::shared_ptr<MetaProvider> MetaProviderPtr;
#endif