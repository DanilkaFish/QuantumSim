#include "algorithms/Grover.h"
#include "QuantumCircuit.h"

std::vector<int> to_bin(int n, int range){
    std::vector<int> binv;
    for(int i = 0; i < range; n = n / 2){
        binv.push_back(n % 2);
        i++;
    }
    return binv;
}

std::tuple<QuantumCircuit, Qubits, Qubit> Oracle(int n, std::vector<int> one_values){
    QuantumCircuit main_qc;
    std::vector<int> binv;
    int len = n;
    int rev_count =0;
    for (auto v : one_values){
        QuantumCircuit qc;
        binv = to_bin(v, n);
        for (int i = 0; i < n/2; i++){
            rev_count = 1;
            if (!binv[2*i]){
                qc.add_instruction(BaseInstr::X(2*i));
                rev_count+=2;
            }
            if (!binv[2*i + 1]){
                qc.add_instruction(BaseInstr::X(2*i + 1));
                rev_count+=2;
            }
            qc.add_instruction(BaseInstr::TOF(2*i, 2*i + 1, n + i));
            if (!binv[2*i])
                qc.add_instruction(BaseInstr::X(2*i));
            if (!binv[2*i + 1])
                qc.add_instruction(BaseInstr::X(2*i + 1));
        }
        int sdv = n;
        if (n % 2 == 1){
            rev_count = 1;
            if (!binv[n-1]){
                rev_count += 2;
                qc.add_instruction(BaseInstr::X(n-1));
                qc.add_instruction(BaseInstr::TOF(n-1, n, n + n/2));
                qc.add_instruction(BaseInstr::X(n-1));
            }else{
                qc.add_instruction(BaseInstr::TOF(n-1, n, n + n/2));
            }
            sdv++;
        }

        len = n / 2;
        while (len > 1){
            rev_count = 1;
            for (int i=0; i < len/2; i++)
                qc.add_instruction(BaseInstr::TOF(sdv + 2*i, sdv + 2*i + 1, len + sdv + i));
            sdv += len;
            if (len % 2 == 1){
                qc.add_instruction(BaseInstr::TOF(sdv - 1, sdv, sdv + 1));
                sdv++;
            }
            len = len/2;
        }
        auto it = qc.rbegin();
        for (int i=0; i < rev_count; i++){it++;}
        QuantumCircuit cqc;
        for (; it != qc.rend(); it++){
            cqc.add_instruction(*it);
        }
        qc.compose(cqc);
        // qc = qc.decompose();
        main_qc.compose(qc);
    }
    return std::tuple<QuantumCircuit, Qubits, Qubit>(main_qc, Qubits(n), Qubit(2*n-2));
}

// QuantumCircuit Grover(QuantumCircuit& oracle, int n, int _k);
QuantumCircuit Grover(QuantumCircuit& oracle, Qubits main_qubits, Qubit trg,  int num_layers){
    const int n = main_qubits.size();
    int hilb_n = 1 << n;
    DataPtr difptr(new Data(hilb_n*hilb_n, 0));
    for(int i = 1; i < hilb_n; i++){
        (*difptr)[i*hilb_n + i] = -1;
    }
    (*difptr)[0] = 1;

    QuantumCircuit qc;
    for (auto x: main_qubits){
        qc.add_instruction(BaseInstr::H(x));
    }
    qc.add_instruction(BaseInstr::X(trg));
    qc.add_instruction(BaseInstr::H(trg));


    QuantumCircuit _qc;
    _qc.compose(oracle);

    for (auto x: main_qubits){
        _qc.add_instruction(BaseInstr::H(x));
    }

    _qc.add_instruction(BaseInstr::U(main_qubits, difptr));

    for (auto x: main_qubits){
        _qc.add_instruction(BaseInstr::H(x));
    }
    for (int i = 0; i < num_layers; i++){
        qc.compose(_qc);

    }
    return qc;
};