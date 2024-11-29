#ifndef _TENSORPROVIDER
#define _TENSORPROVIDER

// #include "inc/parameter.h"
#include "tensorspec.h"
#include "gatesim.h"
#include "QuantumCircuit.h"

constexpr int num_thread=1;
// class Param
void _fill(int init, int finit, int dif, const Data& l, Data& r, const mask& buffer_mask, const std::vector<int>& expand);



#endif