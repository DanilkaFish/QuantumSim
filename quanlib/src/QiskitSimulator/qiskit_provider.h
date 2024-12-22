#include "python_singleton.h"
#include <map>

#include "QuantumCircuit.h"
#include "instruction.h"
#include "state_evolve.h"


State from_qiskit_state_to_State(py::array qiskit_state);
py::object from_State_to_qiskit_state(State& state);

class QiskitProvider: public MetaProvider{
public:
    QiskitProvider(const QuantumCircuit& qc);
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
    void print() const { py::print(pyqc); }
    virtual void state_evolve() override;
    State get_evolved_state();
    void set_init_state(const State& st);
    virtual void SetUp() override;
    virtual double evaluate_cost() override;
    // virtual ~QiskitProvider() noexcept {}
private:
    RunPython& rp;
    py::list qubs_to_list(const Qubits& qubs);
    py::object pyqc;
    py::object qiskit;
    py::object qiskit_quantum_info;
    py::object state;
    py::object qr;
    py::object evolved_state;
    std::map<Qubit, py::int_> qubs_to_int;
};
