#ifndef _PURESIM
#define _PURESIM

#include "inc/QuantumCircuit/quantumcircuit.h"
#include "simdata.h"


class PureSim: public Executor{
public:
    PureSim(const QuantumCircuit& qc): Executor{qc}, sdptr{new SimData{qc.get_qubits()}} {
        for(auto x: qc.get_instr()){
            x->attach_meta(static_cast<MetaDataPtr>(sdptr));
        }
    } 
    PureSim(const QuantumCircuit& qc, State& st): Executor{qc}, sdptr{new SimData(st)} {
        for(auto x: qc.get_instr()){
            x->attach_meta(static_cast<MetaDataPtr>(sdptr));
        }
    } 
    
    void SetUp() override {}
    SimDataPtr sdptr;
};

#endif