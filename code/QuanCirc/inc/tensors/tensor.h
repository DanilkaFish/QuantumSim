#ifndef _TENSOR
#define _TENSOR

#include "bin_utils.h"


inline void error(int l);
inline void custom_error(std::string s);

namespace tensor{
class HSMatrix;
// TODO
// void is_unitary(const HSMatrix& hs){};
// TODO
// void is_hermite(const HSMatrix& hs){};

const Complex i{0,1};

class State{
public:
    State(int n_qubits)          : v{ComplexArr(1 << n_qubits)}, n_qubits{n_qubits} {}
    State(const ComplexArr& vec) : v{vec}, n_qubits{ find_power_2(vec.size()) } {}
    State(ComplexArr&& vec)      : v{vec}, n_qubits{ find_power_2(vec.size()) } {}
    State(const State& s)        : v{s.v}, n_qubits{s.n_qubits} {}
    State(State&& s)             : v{s.v}, n_qubits{s.n_qubits} {}
    State&            operator=(const State& s);
    State&            operator=(State&& s);
    const Complex&    operator[]( int i ) const { return v[i];}
    Complex&          operator[]( int i ){ return v[i];}

    int               get_n_qubits() const { return n_qubits;}
    int               size() const { return v.size(); }
    const ComplexArr& get_array() const { return v;}
    Double            norm() const;
    void              make_normed();
private:
    ComplexArr v;
    int n_qubits;
};
class Condition;

class HSMatrix{
public:
    HSMatrix()                   : v{}, n_qubits{0} {  }
    HSMatrix(int n_qubits)       : v{ComplexArr(1 << n_qubits*2)}, n_qubits{n_qubits}{  }
    HSMatrix(const HSMatrix& uo) : v{uo.v}, n_qubits{uo.n_qubits} {  }
    HSMatrix(HSMatrix&& uo)      : v{uo.v}, n_qubits{uo.n_qubits}{  }
    HSMatrix(const ComplexArr& vec);
    HSMatrix(ComplexArr&& vec);

    HSMatrix&         operator=( const HSMatrix& s );
    HSMatrix&         operator=( HSMatrix&& s );
    Complex&          operator[]( int i ){ return v[i]; }
    const Complex&    operator[]( int i ) const { return v[i];}
    
    int               size()         const { return v.size(); }
    int               get_n_qubits() const { return n_qubits; }
    const ComplexArr& get_array() const { return v;}
    std::string       get_name()     const { return name; }
    void              set_name( const std::string& new_name ){ name = new_name; }
    HSMatrix          to_unitary() const;
    const HSMatrix&   move_axis( IntArr&& fin );
    void              evolve(State&, const IntArr& qubits);
protected:
    ComplexArr  v;
    int         n_qubits;
    std::string name="HSMatrix"; 
};
tensor::HSMatrix tensordot( const tensor::HSMatrix l, 
                            const tensor::HSMatrix r, 
                            const IntArr& axisl,
                            const IntArr& axisr );
}
tensor::HSMatrix operator* (const tensor::HSMatrix& l, const tensor::HSMatrix& r);
std::ostream&    operator<<( std::ostream& os, const tensor::HSMatrix& bt );
std::ostream&    operator<<( std::ostream& os, const tensor::State&    s  );


namespace instr{
    tensor::HSMatrix CX();
    tensor::HSMatrix TOF();
    tensor::HSMatrix X();
    tensor::HSMatrix Y();
    tensor::HSMatrix Z();
    tensor::HSMatrix I();
    tensor::HSMatrix H();
}

#endif