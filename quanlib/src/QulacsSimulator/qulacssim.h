#ifndef _GATESIM
#define _GATESIM

#include <string>
#include <utility>

#include "common.h"
#include "metaprovider.h"
	

class QulacsProvider : public MetaProvider{
    virtual void I(const Qubits& qubs) override;
    virtual void X(const Qubits& qubs) override;
    virtual void Y(const Qubits& qubs) override;
    virtual void Z(const Qubits& qubs) override;
    virtual void CX(const Qubits& qubs) override ;
    virtual void TOF(const Qubits& qubs ) override;
    virtual void H(const Qubits& qubs) override ;
    virtual void S(const Qubits& qubs) override ;
    virtual void Sdag(const Qubits& qubs) override ;
    virtual void U1(const Qubits& qubs, DataPtr dptr) override ;
    virtual void U2(const Qubits& qubs, DataPtr dptr) override ;
    virtual void U(const Qubits& qubs, DataPtr dptr) override ;
};



#endif