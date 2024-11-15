#ifndef _UNITARY
#define _UNITARY

#include "tensorspec.h"
#include "inc/QuantumCircuit/instruction.h"
#include "inc/parameter.h"
#include "simdata.h"


class BaseUnitary: public Instruction{
public:
    virtual void attach_meta(const MetaDataPtr& md) override { sdptr = SimDataPtr{md, static_cast<SimData *>(md.get())}; }
    virtual void apply() = 0;
protected:
    SimDataPtr sdptr;
};


class FixedUnitary: public BaseUnitary{
public:
    FixedUnitary(const Operator& op): op{op} {}
    virtual void apply() override { sdptr->state = op * sdptr->state; }
private:
    Operator op;
};

// class ParameterUnitary: public BaseUnitary{
// public:
//     ParameterUnitary(Operator (*funcptr)() , std::string parname): {}

// private:
// };

// auto glambda = []() { return Operator{}; };


namespace Gate{
    InstructionPtr I(Qubit qub);
    InstructionPtr X(Qubit qub);
    InstructionPtr Y(Qubit qub);
    InstructionPtr Z(Qubit qub);
    InstructionPtr CX(Qubit ctrl, Qubit tar);
    InstructionPtr TOF(Qubit ctrl1, Qubit ctrl2, Qubit trg);
    InstructionPtr H(Qubit qub);
    InstructionPtr S(Qubit qub);
    InstructionPtr Sdag(Qubit qub);
    //  PR(Double angle, const PauliString& ps);
}

#endif