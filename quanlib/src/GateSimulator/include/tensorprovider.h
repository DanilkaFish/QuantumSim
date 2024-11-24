#ifndef _tensorprovider
#define _tensorprovider

// #include "inc/parameter.h"
#include "tensorspec.h"
#include "metaprovider.h"
#include "QuantumCircuit.h"

constexpr int num_thread=16;
// class Param
inline void _fill(int init, int finit, Data l, Data& r, const mask& buffer_mask, int dif, std::vector<int>& expand){
    int buffer_i;
    int buffer_s;
    std::vector<DataType> buffer(dif);
    std::vector<DataType> bufferr(dif);
    for (int i=init; i<finit; i++){
        buffer_i = buffer_mask.expand(i);
        // buffer_i = init;

        for(int up_index=0; up_index<dif; up_index++){
            bufferr[up_index] = r[buffer_i + expand[up_index]] ;
        }

        for(int up_index=0; up_index<dif; up_index++){
            buffer[up_index] = 0;
            for (int down_index=0; down_index<dif; down_index++){
                buffer[up_index] += l[up_index*dif + down_index] * bufferr[down_index];
            }
        }
        for(int up_index=0; up_index<dif; up_index++){
            r[buffer_i + expand[up_index]] = buffer[up_index];
        }
    }
}; 


class TensorProvider: public MetaProvider{
public:
    TensorProvider(const QuantumCircuit& qc): MetaProvider{qc},
                                            dptr(new Data(1<<qc.get_qubits().size())) { 
        (*dptr)[0] = 1; state = State(qc.get_qubits(), dptr); 
    }
    
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
    //  PR(Double angle, const PauliString& ps);
    void inplace_evolve(const Operator& op){
        mask buffer_mask(~op.get_shape().pos_down.m & state.get_shape().pos_up.m);
        int dif = 1 << op.get_qubits().size();

        std::vector<int> expand;
        mask op_mask(op.get_shape().pos_down.m & state.get_shape().pos_up.m);
        for (int j=0; j < (dif); j++){
            expand.push_back(op_mask.expand(j));
        }

        std::vector<std::thread> threads(num_thread);
        int size = state.get_dptr()->size() / dif / num_thread;
        int num_th=num_thread;
        int j = 0;
// _fill(size*j, 
//                                             size*(j+1), 
//                                             std::cref(*(op.get_dptr().get())), 
//                                             std::ref(*(state.get_dptr().get())),
//                                             std::cref(buffer_mask), 
//                                             dif,
//                                             std::ref(expand));
        for (int j=0; j<num_th; j++){
            threads[j] = std::thread(_fill, size*j, 
                                            size*(j+1), 
                                            *(op.get_dptr().get()), 
                                            std::ref(*(state.get_dptr().get())),
                                            std::cref(buffer_mask), 
                                            dif,
                                            std::ref(expand));
        }
        for (int j=0; j<num_th; j++){
            threads[j].join();
        }
    }
    State state;
    DataPtr dptr;
    // ParameterSet ps;
};




#endif