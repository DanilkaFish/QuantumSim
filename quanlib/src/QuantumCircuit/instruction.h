#ifndef _INST
#define _INST

#include <memory>
#include "common.h"
#include "QuantumCircuit.h"
#include "metaprovider.h"

class Instruction{
public:
    Instruction(const Qubits& qubs, const std::string& name="U"): qubits{qubs}, name{name} { }
    virtual                 ~Instruction(){};

    virtual void            apply(MetaProvider& ) { };
    virtual QuantumCircuit  decompose(const InstructionPtr& that)  ;
    std::string             get_name()   const { return name; }
    Qubits                  get_qubits() const {  return qubits; }
protected:
    Qubits qubits;
    std::string name;
};
typedef std::shared_ptr<Instruction> InstructionPtr;


class MagicInstruction: public Instruction{
public:
    MagicInstruction(QuantumCircuit tot): Instruction{tot.get_qubits(), "composed"} , qc{tot}{ }
    void apply(MetaProvider& md) override {
        for(auto i: qc){
            i->apply(md);
        }
    }
    QuantumCircuit decompose(const InstructionPtr& that) override;
private:
    QuantumCircuit qc{};
};


typedef std::shared_ptr<Instruction> InstructionPtr;


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


#endif