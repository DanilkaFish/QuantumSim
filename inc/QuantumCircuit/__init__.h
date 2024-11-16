#include "quantumcircuit.h"
// #include "metaprovider.h"

namespace BaseInstr{

    class _X: public Instruction{
    public:
        _X(const Qubits& qubs): Instruction{qubs,"X"} {}
        void apply(MetaProvider& md) override { md.X(qubits);}
    };

    class _Y: public Instruction{
    public:
        _Y(const Qubits& qubs): Instruction{qubs,"Y"} {}
        void apply(MetaProvider& md) override { md.Y(qubits);}
    };

    class _Z: public Instruction{
    public:
        _Z(const Qubits& qubs): Instruction{qubs,"Z"} {}
        void apply(MetaProvider& md) override { md.Z(qubits);}
    };

    class _I: public Instruction{
    public:
        _I(const Qubits& qubs): Instruction{qubs,"I"} {}
        void apply(MetaProvider& md) override { md.I(qubits);}
    };

    class _CX: public Instruction{
    public:
        _CX(const Qubits& qubs): Instruction{qubs,"CX"} {}
        void apply(MetaProvider& md) override { md.CX(qubits);}
    };

    class _TOF: public Instruction{
    public:
        _TOF(const Qubits& qubs): Instruction{qubs,"TOF"} {}
        void apply(MetaProvider& md) override { md.TOF(qubits);}
    };

    class _S: public Instruction{
    public:
        _S(const Qubits& qubs): Instruction{qubs,"S"} {}
        void apply(MetaProvider& md) override { md.S(qubits);}
    };

    class _Sdag: public Instruction{
    public:
        _Sdag(const Qubits& qubs): Instruction{qubs,"Sdag"} {}
        void apply(MetaProvider& md) override { md.Sdag(qubits);}
    };

    class _H: public Instruction{
    public:
        _H(const Qubits& qubs): Instruction{qubs,"H"} {}
        void apply(MetaProvider& md) override { md.H(qubits);}
    };

    class _Custom: public Instruction{
    public:
        _Custom(const Instruction& in): Instruction{in} {}
        // void apply(MetaProvider& md) override { this->apply(md); }
    };


    InstructionPtr X(Qubit qub) { return InstructionPtr{ new _X{{qub}}}; }
    InstructionPtr Y(Qubit qub) { return InstructionPtr{ new _Y{{qub}}}; }
    InstructionPtr Z(Qubit qub) { return InstructionPtr{ new _Z{{qub}}}; }
    InstructionPtr I(Qubit qub) { return InstructionPtr{ new _I{{qub}}}; }
    InstructionPtr S(Qubit qub) { return InstructionPtr{ new _S{{qub}}}; }
    InstructionPtr H(Qubit qub) { return InstructionPtr{ new _H{{qub}}}; }
    InstructionPtr Sdag(Qubit qub) { return InstructionPtr{ new _Sdag{{qub}}}; }
    InstructionPtr CX(Qubit ctrl, Qubit tar) { return InstructionPtr{ new _CX{{ctrl, tar}}}; }
    InstructionPtr TOF(Qubit ctrl1, Qubit ctrl2, Qubit tar) { return InstructionPtr{ new _TOF{{ctrl1, ctrl2, tar}}}; }
    // InstructionPtr Custom(const Instruction& in) { return InstructionPtr{ new _Custom{in}}; }
}
