from qiskit import QuantumCircuit, QuantumRegister
from qiskit.quantum_info import Statevector
qc = QuantumCircuit(3)
qc.h(0)
qc.h(1)
qc.unitary(data, )
state = Statevector([1,0,0,0,0,0,0,0], dims=8)
state.da
ev_state = state.evolve(qc)
i = 1 +1j
print(ev_state)