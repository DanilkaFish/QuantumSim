#include "numgenerator/lcg.cpp"
#include "genfactory.h"

BaseGenerator* RandGeneratorFactory::CreateRandGenerator(int seed, GeneratorKind type){
    switch (type)
    {
        case GeneratorKind::LCG:
            return new LCG(seed);
        default:
            return nullptr;
    }
}

