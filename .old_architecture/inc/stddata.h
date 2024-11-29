#ifndef _STDDATAQC
#define _STDDATAQC

#include <complex>
#include <vector>
#include <memory>


typedef std::complex<double> DataType;
typedef std::vector<DataType> Data;
typedef std::shared_ptr<std::vector<DataType>> DataPtr;
namespace i{
    constexpr DataType i = {0,1};
}

#endif