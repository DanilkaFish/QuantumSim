#ifndef _GATESIM
#define _GATESIM

#include <string>
#include <utility>


#include "common.h"
#include "quantumcircuit.h"
#include "metaprovider.h"
#include "qulacs_wrapper.h"

class QulacsCirctuit : public qulacs::QuantumCircuit{
    QulacsCirctit(const QuantumCircuit& qc)
}

class QulacsProvider : public MetaProvider{
    // QulacsProvider
    QulacsProvider(const QuantumCircuiut& qc) {
        for (auto x : qc) {

        }
    };
    virtual void I(const Qubits& qubs) override;
    virtual void X(const Qubits& qubs) override;
    virtual void Y(const Qubits& qubs) override;
    virtual void Z(const Qubits& qubs) override;
    virtual void CX(const Qubits& qubs) override ;
    virtual void TOF(const Qubits& qubs ) override {}
    virtual void H(const Qubits& qubs) override ;
    virtual void S(const Qubits& qubs) override ;
    virtual void Sdag(const Qubits& qubs) override ;
    virtual void U1(const Qubits& qubs, DataPtr dptr) override {}
    virtual void U2(const Qubits& qubs, DataPtr dptr) override {}
    virtual void U(const Qubits& qubs, DataPtr dptr) override {}
    qulacs::QuantumState state;
    void inplace_evolve(qulacs::QGatePtr qb){
        qb->update_quantum_state(&state);
    }
    DataPtr get_data_from_state(){ return *state.data_cpp(); }
    bool is_qulacs_circuit=false;
    qulacs::QuantumCircuit qulacs_qc;

};

// namespace qg
#endif