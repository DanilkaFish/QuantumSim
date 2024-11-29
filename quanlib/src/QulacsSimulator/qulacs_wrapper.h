#ifndef _IS_QULACS_WRAPPED
#define _IS_QULACS_WRAPPED


#include <memory>

namespace qulacs{
    #include "cppsim/state.hpp"
    #include "cppsim/circuit.hpp"
    #include "cppsim/gate_factory.hpp"

    using QuantumState = QuantumState;
    using QuantumCircuit = QuantumCircuit;
    using QGatePtr = std::shared_ptr<QuantumGateBase>;
    // using QuantumGateBase = QuantumGateBase;
    QGatePtr _create_quantum_gate_from_string(const std::string& s){
        return QGatePtr(create_quantum_gate_from_string(s));
    }
    
}

#endif