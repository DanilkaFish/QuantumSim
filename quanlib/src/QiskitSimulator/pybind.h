#include <pybind11/embed.h> // everything needed for embedding
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <map>

#include "QuantumCircuit.h"
#include "instruction.h"
#include "state_evolve.h"

namespace py = pybind11;

State from_qiskit_state_to_State(py::array qiskit_state);
// py::object numpy_op_array(DataPtr dptr);
py::array_t<DataType> numpy_op_array(DataPtr dptr);

class QiskitProvider: public MetaProvider{
public:
    QiskitProvider(const QuantumCircuit& qc): MetaProvider{qc} {
        qiskit = py::module_::import("qiskit");
        qiskit_quantum_info = py::module_::import("qiskit.quantum_info");
        int num_qubits = qc.get_qubits().size();
        py::array_t<DataType> array(1 << num_qubits, new DataType[1<<num_qubits]);
        array[py::int_(0)] = 1;
        state = qiskit_quantum_info.attr("Statevector")(array);
        pyqc = qiskit.attr("QuantumCircuit")(py::int_(num_qubits));
        int i = 0;
        for (auto x :qc.get_qubits()){
            py::print(py::int_(i));
            qubs_to_int[x] = py::int_(i++);
        }
        apply_instructions();
        py::print(pyqc);
    }
    void I(const Qubits& qubs) override;
    void X(const Qubits& qubs) override;
    void Y(const Qubits& qubs) override;
    void Z(const Qubits& qubs) override;
    void CX(const Qubits& qubs) override ;
    void TOF(const Qubits& qubs ) override;
    void H(const Qubits& qubs) override ;
    void S(const Qubits& qubs) override ;
    void Sdag(const Qubits& qubs) override ;
    void U(const Qubits& qubs, DataPtr dptr) override ;
    void PR(const PauliString& ps, double angle) override;
    void Rx(const Qubits& qubs, double angle) override;
    void Ry(const Qubits& qubs, double angle) override;
    void Rz(const Qubits& qubs, double angle) override;
    virtual void state_evolve() override {
        py::print(state);
        evolved_state = state.attr("evolve")(pyqc);
        py::print(evolved_state);
    }
    State get_state_evolve(){
        return from_qiskit_state_to_State(evolved_state.attr("data"));
    }

    virtual void SetUp() override{
        // py::print(qc);
    }
    
    virtual double evaluate_cost() override { return 0;};
private:
    py::list qubs_to_list(const Qubits& qubs){ 
        py::list list{};
        for (auto x: qubs){
            list.attr("append")(qubs_to_int[x]);
        }
        return list;
    }
    py::scoped_interpreter guard{};
    py::object pyqc;
    py::object qiskit;
    py::object qiskit_quantum_info;
    py::object state;
    py::object qr;
    py::object evolved_state;
    std::map<Qubit, py::int_> qubs_to_int;
};
