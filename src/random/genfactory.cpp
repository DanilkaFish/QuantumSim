#include "numgenerator/lcg.cpp"
#include "inc/random/genfactory.h"

BaseGenerator* RandGeneratorFactory::CreateRandGenerator(int seed, GeneratorKind type){
    switch (type)
    {
        case GeneratorKind::LCG:
            return new LCG(seed);
        default:
            return nullptr;
    }
}

