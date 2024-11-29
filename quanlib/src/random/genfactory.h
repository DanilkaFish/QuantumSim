#ifndef _GENFACTORY
#define _GENFACTORY

#include "numgenerator/basegen.h"
#include <iostream>

enum class GeneratorKind {LCG};

class RandGeneratorFactory{
public:
    static BaseGenerator* CreateRandGenerator(int seed, GeneratorKind type);
};

#endif