#ifndef _SIMDATA
#define _SIMDATA

#include "inc/parameter.h"
#include "inc/GateSimulator/tensorspec.h"
#include "inc/QuantumCircuit/metadata.h"
#include <memory>


class SimData: public MetaData{
public:
    SimData()=default;
    SimData(const State& st): state{st} {}
    State state;
    ParameterSet ps;

};

// std::shared_ptr<SimData>
typedef std::shared_ptr<SimData> SimDataPtr;

#endif