#ifndef _GENFACTORY
#define _GENFACTORY

#include "code/QuanCirc/src/random/numgenerator/basegen.h"
#include <iostream>

enum class GeneratorKind {LCG};

class RandGeneratorFactory{
public:
    static BaseGenerator* CreateRandGenerator(int seed, GeneratorKind type);
};

#endif