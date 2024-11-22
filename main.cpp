#include "inc/QuantumCircuit/__init__.h"
#include "inc/GateSimulator/__init__.h"
int main(){
    QuantumCircuit qc;
    DataPtr dptr( new Data{(0.0647265,-0.0147986),   (-0.136957,0.311306),    (0.826655,0.243897),   (0.361068,-0.081901),
              (-0.0570977,0.389438) ,  (-0.550067,0.256655) , (0.0583355,0.0166723) , (-0.617309,-0.303119),
              (0.0300017,-0.445766) ,    (0.42624,0.254302) , (-0.0823076,0.457651) , (-0.313011,-0.489742),
              (-0.700512,-0.387745) ,  (-0.232282,0.464306) , (-0.156386,-0.113128) ,   (0.102058,0.204283)});

    int n =22;
    for (int i=0; i< n; i++) 
        for (int j=0; j< n; j++)
            if (i != (j + 10) % n)
                qc.add_instruction(BaseInstr::U(Qubits{i, (j + 10) % n}, dptr));
    TensorProvider exec(qc);
    exec.run();
    std::cout << exec.state;
}