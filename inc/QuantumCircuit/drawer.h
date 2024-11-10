#ifndef _DRAWER
#define _DRAWER
#include "qubits.h"
struct QC_representation{
    Qubits qubits;
    std::string s;
};

class Drawer{
public:
    virtual void draw(const QC_representation& qcr){};
};

#endif 