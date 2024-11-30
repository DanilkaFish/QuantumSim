#ifndef _TENSOR
#define _TENSOR

#include "bin_utils.h"
#include "code/QuanCirc/inc/error.h"

namespace tensor{
class HSMatrix;
class State;
// TODO
// void is_unitary(const HSMatrix& hs){};
// TODO
// void is_hermite(const HSMatrix& hs){};
State statedot( const tensor::State& l, 
                const tensor::State& r, 
                const IntArr& axisl,
                const IntArr& axisr );

HSMatrix hsmatrixdot( const tensor::HSMatrix& l, 
                      const tensor::HSMatrix& r, 
                      IntArr axisl,
                      IntArr axisr );    
const Complex i{0,1};

class State{
public:
    State() : v{ComplexArr{1}}, n_qubits{0}{}
    State(int n_qubits)          : v{ComplexArr(1 << n_qubits, 0)}, n_qubits{n_qubits} {v[0] = 1;}
    State(std::vector<State> vs){
        if (!vs.size()==0){
            (*this) = (vs[0]);
            for (int i = 1; i< vs.size(); i++){
                (*this) = statedot((*this), vs[i], IntArr{}, IntArr{}); 
            }
        }else{
            v = ComplexArr{1};
            n_qubits = 0;
        }
    }
    State(const ComplexArr& vec) : v{vec} { n_qubits = find_power_2(vec.size()); }
    State(ComplexArr&& vec)      : v{vec} { n_qubits = find_power_2(vec.size()); }
    State(const State& s)        : v{s.v}, n_qubits{s.n_qubits} {}
    State(State&& s)             : v{s.v}, n_qubits{s.n_qubits} {}
    State&            operator=(const State& s);
    State&            operator=(State&& s);
    const Complex&    operator[]( int i ) const { return v[i];}
    Complex&          operator[]( int i ){ return v[i];}

    int               get_n_qubits() const { return n_qubits;}
    int               size() const { return v.size(); }
    Double            get_norm() const;
    const ComplexArr& get_array() const { return v;}
    void              make_normed();
private:
    ComplexArr v;
    int n_qubits;
};


class HSMatrix{
public:
    HSMatrix(const ComplexArr& vec);
    HSMatrix(ComplexArr&& vec);
    HSMatrix()                   : v{ComplexArr{1}}, n_qubits{0} {  }
    HSMatrix(int n_qubits)       : v{ComplexArr(1 << n_qubits*2, 0)}, n_qubits{n_qubits}{  }
    HSMatrix(const HSMatrix& uo) : v{uo.v}, n_qubits{uo.n_qubits} {  }
    HSMatrix(HSMatrix&& uo)      : v{uo.v}, n_qubits{uo.n_qubits}{  }


    HSMatrix&         operator=( const HSMatrix& s );
    HSMatrix&         operator=( HSMatrix&& s );
    Complex&          operator[]( int i ){ return v[i]; }
    const Complex&    operator[]( int i ) const { return v[i];}
    
    int               size()         const { return v.size(); }
    int               get_n_qubits() const { return n_qubits; }
    const ComplexArr& get_array()    const { return v; }
    std::string       get_name()     const { return name; }
    HSMatrix          to_unitary()   const;

    void              set_name( const std::string& new_name ){ name = new_name; }
    const HSMatrix&   move_axis( const IntArr& full_perm );
    const HSMatrix&   move_axis( const IntArr& in, const IntArr& fin );
    void              evolve( State&, const IntArr& qubits );
protected:
    std::string       name="HSMatrix"; 
    ComplexArr        v;
    int               n_qubits;
};

}
tensor::HSMatrix operator* (const tensor::HSMatrix& l, const tensor::HSMatrix& r);
tensor::HSMatrix operator+(const  tensor::HSMatrix& l, const tensor::HSMatrix& r );
tensor::HSMatrix operator*(Complex d, const tensor::HSMatrix& r );

std::ostream&    operator<<( std::ostream& os, const tensor::HSMatrix& bt );
std::ostream&    operator<<( std::ostream& os, const tensor::State&    s  );


#endif