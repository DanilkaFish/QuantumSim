#ifndef _QCINIT
#define _QCINIT

#include "quantumcircuit.h"

namespace BaseInstr{

    class _X: public Instruction{
    public:
        _X(const Qubits& qubs): Instruction{qubs,"X"} {}
        void apply(MetaProvider& md) override { md.X(qubits);}
    };

    class _Y: public Instruction{
    public:
        _Y(const Qubits& qubs): Instruction{qubs,"Y"} {}
        virtual void apply(MetaProvider& md) override { md.Y(qubits);}
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
        _TOF(const Qubits& qubs): Instruction{qubs,"TOF"} { }
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

    class _U1: public Instruction{
    public:
        _U1(const Qubits& qubs, DataPtr dptr): Instruction{qubs, "U1"}, dptr{dptr} {}
        void apply(MetaProvider& md) override { md.U1(qubits, dptr); }
    private:
        DataPtr dptr;
    };

    class _U2: public Instruction{
    public:
        _U2(const Qubits& qubs, DataPtr dptr): Instruction{qubs, "U2"}, dptr{dptr} {}
        void apply(MetaProvider& md) override { md.U2(qubits, dptr); }
    private:
        DataPtr dptr;
    };

    class _U: public Instruction{
    public:
        _U(const Qubits& qubs, DataPtr dptr): Instruction{qubs, "U"}, dptr{dptr} {}
        void apply(MetaProvider& md) override { md.U(qubits, dptr); }
    private:
        DataPtr dptr;
    };

    InstructionPtr X(Qubit qub);
    InstructionPtr Y(Qubit qub);
    InstructionPtr Z(Qubit qub);
    InstructionPtr I(Qubit qub);
    InstructionPtr S(Qubit qub);
    InstructionPtr H(Qubit qub);
    InstructionPtr Sdag(Qubit qub);
    InstructionPtr CX(Qubit ctrl, Qubit tar);
    InstructionPtr TOF(Qubit ctrl1, Qubit ctrl2, Qubit tar);
    InstructionPtr U1(Qubit qub, DataPtr dptr);
    InstructionPtr U2(Qubit qub1, Qubit qub2, DataPtr dptr);
    InstructionPtr U(Qubits qubs, DataPtr dptr);
}


#endif