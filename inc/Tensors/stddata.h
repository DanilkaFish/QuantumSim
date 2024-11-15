#ifndef _STDDATA
#define _STDDATA

#include <complex>
#include <vector>
#include <map>
#include <memory>
#include "inc/qubits.h"

typedef std::complex<double> DataType;
// typedef std::vector<DataType> Container;
typedef int Int;
typedef std::vector<DataType> Data;
typedef std::shared_ptr<std::vector<DataType>> DataPtr;
typedef std::map<Qubit, Int, std::greater<Qubit>> PosMap;
// typedef std::vector<Int> Positions;
namespace i{
    constexpr DataType i = {0,1};
}

#endif