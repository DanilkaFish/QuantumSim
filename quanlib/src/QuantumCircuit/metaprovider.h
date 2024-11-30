#ifndef _METADATA
#define _METADATA
#include <memory>

#include "common.h"
#include "instruction.h"

class QuantumCircuit;


// class Meta{
//     Meta(const QuantumCircuit& qc): qc{qc} {}

// private:
//     const QuantumCircuit& qc;
// };


class MetaProvider{
public:
    MetaProvider(const QuantumCircuit& qc): qc{qc} {}
    virtual void X(const Qubits& qubs) {};
    virtual void Y(const Qubits& qubs) {};
    virtual void Z(const Qubits& qubs) {};
    virtual void I(const Qubits& qubs) {};
    virtual void H(const Qubits& qubs) {};
    virtual void S(const Qubits& qubs) {};
    virtual void Sdag(const Qubits& qubs) {};
    virtual void CX(const Qubits& qubs) {};
    virtual void TOF(const Qubits& qubs) {};
    virtual void Rx(const Qubits& qubs, double angle) {};
    virtual void Ry(const Qubits& qubs, double angle) {};
    virtual void Rz(const Qubits& qubs, double angle) {};
    // virtual void PR(const Qubits& qubs, double angle) {};
    // virtual void U1(const Qubits& qubs, DataPtr dptr) {};
    // virtual void U2(const Qubits& qubs, DataPtr dptr) {};
    virtual void U(const Qubits& qubs, DataPtr dptr) {};
    virtual void PR(const PauliString& ps, double dptr) {};
    virtual ~MetaProvider() {};
    virtual void SetUp() {}
    void run();
protected:
    const QuantumCircuit& qc;
};

typedef std::shared_ptr<MetaProvider> MetaProviderPtr;


class _X: public Instruction{
public:
    _X(const Qubits& qubs): Instruction{qubs,"X"} {}
    void apply(MetaProvider& md) override { md.X(qubits);}
};

class _Y: public Instruction{
public:
    _Y(const Qubits& qubs): Instruction{qubs,"Y"} {}
    virtual void apply(MetaProvider& md) override {
         md.Y(qubits);
         }
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

class _Rz: public Instruction{
public:
    // _Rz(const Qubits& qubs, double angle): Instruction{qubs, "Rz"}, angle{new Parameter{"", angle}} {}
    _Rz(const Qubits& qubs, ParameterPtr angle): Instruction{qubs, "Rz"}, angle{angle} {}
    void apply(MetaProvider& md) override { md.Rz(qubits, angle->value);}
private:
    ParameterPtr angle; 
};

class _Ry: public Instruction{
public:
    // _Ry(const Qubits& qubs, double angle): Instruction{qubs, "Rt"}, angle{new Parameter{"", angle}} {}
    _Ry(const Qubits& qubs, ParameterPtr angle): Instruction{qubs, "Ry"}, angle{angle} {}
    void apply(MetaProvider& md) override { md.Ry(qubits, angle->value);}
private:
    ParameterPtr angle; 
};

class _Rx: public Instruction{
public:
    // _Rx(const Qubits& qubs, double angle): Instruction{qubs, "Rx"}, angle{new Parameter{"", angle}} {}
    _Rx(const Qubits& qubs, ParameterPtr angle): Instruction{qubs, "Rx"}, angle{angle} {}
    void apply(MetaProvider& md) override { md.Rx(qubits, angle->value);}
private:
    ParameterPtr angle; 
};

class _PR: public Instruction{
public:
    // _Rx(const Qubits& qubs, double angle): Instruction{qubs, "Rx"}, angle{new Parameter{"", angle}} {}
    _PR(const PauliString& ps, ParameterPtr angle): ps{ps}, Instruction{ps.get_qubs(), ps.get_name()}, angle{angle} {}
    virtual QuantumCircuit decompose(const InstructionPtr& ip) override;
    void apply(MetaProvider& md) override { md.PR(ps, angle->value);}
private:
    ParameterPtr angle; 
    PauliString ps;
};

class _U: public Instruction{
public:
    _U(const Qubits& qubs, DataPtr dptr): Instruction{qubs, "U"}, dptr{dptr} {}
    void apply(MetaProvider& md) override { md.U(qubits, dptr); }
private:
    DataPtr dptr;
};
#endif