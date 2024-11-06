#include "code/QuanCirc/inc/tensors/tensor.h"


using namespace tensor;

Double State::norm() const {
    Double s = 0;
    for (auto x: v){
        s += std::norm(x);
    }
    return s;
}
void   State::make_normed(){
    Double norm = this->norm();
    if (norm != 0){
        norm = 1 / std::sqrt(norm);
        for (auto& x: v)
            x *= norm;
    }
}

State& State::operator=(const State& s){ 
    this->v = s.v;
    n_qubits=s.n_qubits;
    return *this;
}

State& State::operator=(State&& s){ 
    this->v = std::move(s.get_array()); 
    n_qubits=s.n_qubits;
    return *this;
}

HSMatrix::HSMatrix(const ComplexArr& vec) : v{vec}{
    int n = find_power_2(this->v.size());
    if (n%2 != 0)
        tensor_error(n/2);
    n_qubits = n/2;
}

HSMatrix::HSMatrix(ComplexArr&& vec) : v{vec}{
    int n = find_power_2(this->v.size());
    if (n%2 != 0)
        tensor_error(n/2);
    n_qubits = n/2;
}

HSMatrix& HSMatrix::operator=(const HSMatrix& s){ 
    this->v  = s.v;
    n_qubits = s.n_qubits;
    return *this;
}

HSMatrix& HSMatrix::operator=(HSMatrix&& s){ 
    this->v  = std::move(s.v); 
    n_qubits = s.n_qubits;
    return *this;
}

const HSMatrix& HSMatrix::move_axis(const IntArr& full_perm){
    ComplexArr new_v(1 << (2*this->n_qubits));
    for(int i=0; i<new_v.size(); i++){
        new_v[i] = v[change_on_pos(i, full_perm, i)];
    }
    this->v = new_v;
    return *this;
}

const HSMatrix& HSMatrix::move_axis(const IntArr& in, const IntArr& fin){
    ComplexArr new_v(1<<2*this->n_qubits);
    int sub_int1; 
    int sub_int2; 
    for(int i=0; i<new_v.size(); i++){
        sub_int1 = bit_on_pos(i, in);
        sub_int2 = bit_on_pos(i, fin);
        new_v[i] = v[change_on_pos(change_on_pos(i, fin, sub_int1), in, sub_int2)];
    }
    this->v = new_v;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const State& s){
    for(int i=0; i<s.size(); i++){
        if (s[i].imag() != 0 || s[i].real() != 0){
            os << '+' << s[i] << "|";
            for(int pos=0; pos<s.get_n_qubits(); pos++){
                (bit_on_pos(i,pos) == 1) ? os << '1': os << '0';
            }   
            os << "> ";
        }
    }
    return os << "\n";
}
// ----------------------------------HSMatrix------------------------------


std::ostream& operator<<(std::ostream& os, const HSMatrix& bt){
    os << "[";
    int size = 1 << bt.get_n_qubits();
    for(int row=0; row < size; row++){
        for(int col=0; col < size; col++){
            os << bt[row * size + col] <<  ',' ;
        }
        os << '\n';
    }
    return os << "]\n";
}

HSMatrix operator*(const HSMatrix& l, const HSMatrix& r){
    if (l.get_n_qubits() != r.get_n_qubits())
        tensor_error(l.get_n_qubits());
    int n = 1 << l.get_n_qubits();

    HSMatrix prod(l.get_n_qubits());
    Complex val = 0;
    for(int i=0; i < prod.size(); i++){
        val = 0;
        for(int j=0; j < n; j++){
            val += l[(i / n) * n + j]*r[i % n + j * n];
        }
        prod[i] = val;
    }
    return prod;
}
tensor::HSMatrix operator+(const  tensor::HSMatrix& l, const tensor::HSMatrix& r ){
    HSMatrix res(l.get_n_qubits());
    for(int i=0; i < res.size(); i++){
        res[i] = l[i] + r[i];
    }
    return res;
}
tensor::HSMatrix operator*(Complex d, const tensor::HSMatrix& r ){
    HSMatrix res(r.get_n_qubits());
    for(int i=0; i < res.size(); i++){
        res[i] = d*r[i];
    }
    return res;
}

void HSMatrix::evolve(State& s, const IntArr& qubits){
    if (qubits.size() != n_qubits){
        tensor_error(qubits.size());
    }

    IntArr rqubits(qubits.size());
    for(int i=0; i < qubits.size(); i++){
        rqubits[i] = qubits[qubits.size() - i - 1];
    }
    // rqubits = qubits;
    if (rqubits.size() == 2)
        std::swap(rqubits[0], rqubits[1]);
    State ns(s.get_n_qubits());
    for(int is=0; is < s.size(); is++){
        Complex val = 0;
        for(int iu=0; iu<(1 << n_qubits); iu++){
            val += (*this)[(bit_on_pos(is, rqubits) << this->n_qubits) + iu]*s[change_on_pos(is, rqubits, iu)];
        }
        ns[is] = val;
    }
    s = std::move(ns);
}

tensor::State tensor::statedot(const tensor::State& l, 
                        const tensor::State& r, 
                        const IntArr& axisl,
                        const IntArr& axisr ){
    if (axisl.size() != axisr.size())
        custom_error("Diff sizes of axis");
    int n = l.get_n_qubits() + r.get_n_qubits() - 2*axisl.size();
    int nl = l.get_n_qubits() - axisl.size(); 
    int nr = r.get_n_qubits() - axisr.size(); 

    ComplexArr new_v(1 << n, 0);
    for(int i=0; i < l.size(); i++){
        for (int j=0; j < r.size(); j++)
            if (bit_on_pos(i, axisl) == bit_on_pos(j, axisr))
                new_v[(del_on_pos(i, axisl) << nr) + del_on_pos(j, axisr)] 
                    += l[i] * r[j];
    }
    return State(new_v);
}

// TODO
tensor::HSMatrix tensor::hsmatrixdot(const tensor::HSMatrix& l, 
                        const tensor::HSMatrix& r, 
                        IntArr axisl,
                        IntArr axisr ){
    if (axisl.size() != axisr.size())
        custom_error("Diff sizes of axis");
    int n  = 2*l.get_n_qubits() + 2*r.get_n_qubits() - 2*axisl.size();
    int nl = 2*l.get_n_qubits() - axisl.size(); 
    int nr = 2*r.get_n_qubits() - axisr.size(); 
    for (auto& x: axisl){
        x += l.get_n_qubits();
    }
    ComplexArr new_v(1 << n, 0);
    for(int i=0; i < l.size(); i++){
        for (int j=0; j < r.size(); j++){
            if (bit_on_pos(i, axisl) == bit_on_pos(j, axisr)){
                new_v[(del_on_pos(i, axisl) ) + (del_on_pos(j, axisr) << nl)] 
                    += l[i] * r[j];
            }
        }
    }
    return tensor::HSMatrix(new_v);
}