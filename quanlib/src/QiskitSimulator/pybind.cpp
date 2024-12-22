#include "qiskit_provider.h"
#include <iostream>

namespace py = pybind11;

int _reverse(int i, int n){
    n--;
    int out=0;
    // std::cerr << " n : " << n << std::endl;
    for (int j=0; j<=n/2.; j++){
        out += ((i & (1<<j)) << (n - 2*j));
    }
    for (int j=0; j<n/2.; j++){
        out += ((i & (1<<(n-j))) >> (n - 2*j));
    }
    // std::cerr << " i : " << i<<" out : " << out << std::endl;
    return i;
    return out;
}

py::object from_State_to_qiskit_state(const State& st){
    static py::object numpy = py::module_::import("numpy");
    static py::object qiskit_qi = py::module_::import("qiskit.quantum_info");
    int size = st.get_dptr()->size();
    int n = st.get_shape().size();
    py::array_t<DataType> array({size}, new DataType[size]);
    for (int j =0; j<size; j++){
        array[py::int_(j)] = st[_reverse(j, n)];
    }
    return qiskit_qi.attr("Statevector")(array);
}

State from_qiskit_state_to_State(py::array qiskit_state){
    DataPtr dptr(new Data{});
    int size = qiskit_state.size();
    int n = 0;
    while (size > 0 ){
        n++;
        size = size >> 1;
    }
    n--;
    size = qiskit_state.size();
    for (int i=0; i<size;i++){
        dptr->push_back(DataType{*static_cast<const DataType *>(qiskit_state.data(_reverse(i,n)))});
            // py::float_(qiskit_state), py::float_(x.attr("imag"))});
    }
    return State(Qubits(n), dptr);
}

QiskitProvider::QiskitProvider(const QuantumCircuit& qc): MetaProvider{qc}, rp{RunPython::getInstance()} {
    qiskit = py::module_::import("qiskit");
    qiskit_quantum_info = py::module_::import("qiskit.quantum_info");
    int num_qubits = qc.get_qubits().size();
    py::array_t<DataType> array(1 << num_qubits, new DataType[1<<num_qubits]);
    array[py::int_(0)] = 1;
    state = qiskit_quantum_info.attr("Statevector")(array);
    pyqc = qiskit.attr("QuantumCircuit")(py::int_(num_qubits));
    int i = 0;
    for (auto x :qc.get_qubits()){
        qubs_to_int[x] = py::int_(x.num);
    }
    apply_instructions();
}


py::list QiskitProvider::qubs_to_list(const Qubits& qubs){ 
    py::list list{};
    for (auto x: qubs){
        list.attr("append")(qubs_to_int[x]);
    }
    return list;
}

void QiskitProvider::state_evolve(){
    evolved_state = state.attr("evolve")(pyqc);
}

State QiskitProvider::get_evolved_state(){
    return from_qiskit_state_to_State(evolved_state.attr("data"));
}

void QiskitProvider::set_init_state(const State& st) {
    state = from_State_to_qiskit_state(st);
}

void QiskitProvider::SetUp() {}

double QiskitProvider::evaluate_cost(){ return 0;}





py::array_t<DataType> numpy_op_array(DataPtr dptr){
    static py::object numpy = py::module_::import("numpy");
    static py::object qiskit_qi = py::module_::import("qiskit.quantum_info");
    int size = dptr->size();
    for (int i=1; i<size; i=i<<1){
        if (i*i == size){
            size = i;
            break;
        }
    }
    py::array_t<DataType> array({size, size}, new DataType[size*size]);
    for (int i =0; i<size; i++){
        for (int j =0; j<size; j++){
            array[py::int_(i)][py::int_(j)] = (*dptr)[i*size + j];
            // array[py::int_(j)][] = j;
        }
    }
    return array;
}



void QiskitProvider::I(const Qubits& qubs){
    pyqc.attr("id")(qubs_to_int[qubs[0]]);
} 
void QiskitProvider::X(const Qubits& qubs){
    pyqc.attr("x")(qubs_to_int[qubs[0]]);
} 
void QiskitProvider::Y(const Qubits& qubs){
    pyqc.attr("y")(qubs_to_int[qubs[0]]);
} 
void QiskitProvider::Z(const Qubits& qubs){
    pyqc.attr("z")(qubs_to_int[qubs[0]]);
} 
void QiskitProvider::CX(const Qubits& qubs)  {
    pyqc.attr("cx")(qubs_to_int[qubs[0]], qubs_to_int[qubs[1]]);

};
void QiskitProvider::TOF(const Qubits& qubs ){
    static py::array_t<DataType> data = numpy_op_array(DataPtr(new Data{1,0,0,0,0,0,0,0,
                    0,1,0,0,0,0,0,0,
                    0,0,1,0,0,0,0,0,
                    0,0,0,0,0,0,0,1,
                    0,0,0,0,1,0,0,0,
                    0,0,0,0,0,1,0,0,
                    0,0,0,0,0,0,1,0,
                    0,0,0,1,0,0,0,0}));
    pyqc.attr("unitary")(data, qubs_to_list(qubs));
};

void QiskitProvider::H(const Qubits& qubs)  {
    pyqc.attr("h")(qubs_to_int[qubs[0]]);

};
void QiskitProvider::S(const Qubits& qubs)  {
    pyqc.attr("s")(qubs_to_int[qubs[0]]);

};
void QiskitProvider::Sdag(const Qubits& qubs) {
    pyqc.attr("sdg")(qubs_to_int[qubs[0]]);

} ;
void QiskitProvider::U(const Qubits& qubs, DataPtr dptr) {
    pyqc.attr("unitary")(numpy_op_array(dptr), qubs_to_list(qubs));

} ;
void QiskitProvider::PR(const PauliString& ps, double angle) {
    pyqc.attr("unitary")(numpy_op_array(bm::PR(ps, angle).get_dptr()), qubs_to_list(ps.get_sorted_qubs()));
};
void QiskitProvider::Rx(const Qubits& qubs, double angle) {
    pyqc.attr("rx")(-angle, qubs_to_int[qubs[0]]);
};

void QiskitProvider::Ry(const Qubits& qubs, double angle) {
    pyqc.attr("ry")(-angle, qubs_to_int[qubs[0]]);
};

void QiskitProvider::Rz(const Qubits& qubs, double angle) {
    pyqc.attr("rz")(-angle, qubs_to_int[qubs[0]]);
};
