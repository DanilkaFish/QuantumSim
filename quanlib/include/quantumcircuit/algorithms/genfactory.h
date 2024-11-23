#ifndef _GENFACTORY
#define _GENFACTORY

// #include "src/random/numgenerator/basegen.h"
#include <iostream>

enum class GeneratorKind {LCG};
class BaseGenerator;

class RandGeneratorFactory{
public:
    static BaseGenerator* CreateRandGenerator(int seed, GeneratorKind type);
};

#endif