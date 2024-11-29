#ifndef _STDDATA
#define _STDDATA

#include <map>
#include "inc/qubits.h"

// typedef std::vector<DataType> Container;
typedef int Int;

typedef std::map<Qubit, Int, std::greater<Qubit>> PosMap;
// typedef std::vector<Int> Positions;

#endif