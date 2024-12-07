#include "pybind.h"
#include <iostream>

namespace py = pybind11;
// ;
// State from_qiskit_state_to_State(py::array_t<DataType> qiskit_state)

State from_qiskit_state_to_State(py::array qiskit_state){
    DataPtr dptr(new Data{});
    for (auto x: qiskit_state){
        dptr->push_back(DataType{py::float_(x.attr("real")), py::float_(x.attr("imag"))});
    }
    int size = qiskit_state.size();
    int i = 0;
    while (size > 0 ){
        i++;
        size = size << 1;
    }
    return State(Qubits(i), dptr);
}
// py::object from_State_to_qiskit_state(const State& st){
//     static py::object numpy = py::module_::import("numpy");
//     static py::object qiskit_qi = py::module_::import("qiskit.quantum_info");
//     py::buffer_info bi(
//         st.get_dptr().get(),                               /* Pointer to buffer */
//         sizeof(DataType),                          /* Size of one scalar */
//         "Complex",
//         // py::format_descriptor<DataType>::format(), /* Python struct-style format descriptor */
//         1,                                      /* Number of dimensions */
//         { st.get_shape().size() },                 /* Buffer dimensions */
//         { sizeof(DataType)*st.get_shape().size() }
//     );
//     return qiskit_qi.attr("Statevector")(bi);
// }



// TODO
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
    // py::array_t<DataType>
    py::array_t<DataType> array({size, size}, new DataType[size*size]);
    // py::buffer_info bi(
    //     dptr.get(),                               /* Pointer to buffer */
    //     sizeof(DataType),                          /* Size of one scalar */
    //     // "Complex",
    //     py::format_descriptor<DataType>::format(), /* Python struct-style format descriptor */
    //     2,                                      /* Number of dimensions */
    //     { size, size},                 /* Buffer dimensions */
    //     { sizeof(DataType)*size, sizeof(DataType)}
    // );
    for (int i =0; i<size*size; i++){
        array[py::int_(i)] = (*dptr)[i];
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
    pyqc.attr("cx")(qubs_to_int[qubs[0]]);

};
void QiskitProvider::TOF(const Qubits& qubs ){
    static py::object tof_unitary;
    pyqc.attr("unitary")(tof_unitary, qubs_to_list(qubs));

};
void QiskitProvider::H(const Qubits& qubs)  {
    pyqc.attr("h")(qubs_to_int[qubs[0]]);

};
void QiskitProvider::S(const Qubits& qubs)  {
    pyqc.attr("s")(qubs_to_int[qubs[0]]);

};
void QiskitProvider::Sdag(const Qubits& qubs) {
    pyqc.attr("sdag")(qubs_to_int[qubs[0]]);

} ;
void QiskitProvider::U(const Qubits& qubs, DataPtr dptr) {
    pyqc.attr("unitary")(numpy_op_array(dptr), qubs_to_list(qubs));

} ;
void QiskitProvider::PR(const PauliString& ps, double angle) {
    py::print("pauli rotation not implemented");
};
void QiskitProvider::Rx(const Qubits& qubs, double angle) {
    pyqc.attr("rx")(angle, qubs_to_int[qubs[0]]);
};

void QiskitProvider::Ry(const Qubits& qubs, double angle) {
    pyqc.attr("ry")(angle, qubs_to_int[qubs[0]]);
};

void QiskitProvider::Rz(const Qubits& qubs, double angle) {
    pyqc.attr("rz")(angle, qubs_to_int[qubs[0]]);
};
