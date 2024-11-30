#include "code/QuanCirc/inc/algorithms/circuit_builders.h"
#include "code/QuanCirc/inc/algorithms/grover.h"
#include "code/QuanCirc/inc/quantumcirc/unitary.h"


std::vector<int> to_bin(int n, int range){
    std::vector<int> binv;
    for(int i = 0; i < range; n = n / 2){
        binv.push_back(n % 2);
        i++;
    }
    return binv;
}

QuantumCircuit build_grover_circ(int n, IntArr vs){
    QuantumCircuit main_qc{2*n-1};
    std::vector<int> binv;
    int len = n;
    int rev_count =0;
    for (auto v : vs){
        QuantumCircuit qc{2*n - 1};
        binv = to_bin(v, n);
        for (int i = 0; i < n/2; i++){
            rev_count = 1;
            if (!binv[2*i]){
                qc.add_instruction(instr::X(), IntArr{2*i});
                rev_count+=2;
            }
            if (!binv[2*i + 1]){
                qc.add_instruction(instr::X(), IntArr{2*i + 1});
                rev_count+=2;
            }
            qc.add_instruction(instr::TOF(), {2*i, 2*i + 1, n + i});
            if (!binv[2*i])
                qc.add_instruction(instr::X(), IntArr{2*i});
            if (!binv[2*i + 1])
                qc.add_instruction(instr::X(), IntArr{2*i + 1});
        }
        int sdv = n;
        if (n % 2 == 1){
            rev_count = 1;
            if (!binv[n-1]){
                rev_count += 2;
                qc.add_instruction(instr::X(), IntArr{n-1});
                qc.add_instruction(instr::TOF(), {n-1, n, n + n/2});
                qc.add_instruction(instr::X(), IntArr{n-1});
            }else{
                qc.add_instruction(instr::TOF(), {n-1, n, n + n/2});
            }
            sdv++;
        }

        len = n / 2;
        while (len > 1){
            rev_count = 1;
            for (int i=0; i < len/2; i++)
                qc.add_instruction(instr::TOF(), IntArr{sdv + 2*i, sdv + 2*i + 1, len + sdv + i});
            sdv += len;
            if (len % 2 == 1){
                qc.add_instruction(instr::TOF(), IntArr{sdv - 1, sdv, sdv + 1});
                sdv++;
            }
            len = len/2;
        }
        auto it = qc.get_qc_data().rbegin();
        for (int i=0; i < rev_count; i++){it++;}
        for (; it != qc.get_qc_data().rend(); it++){
            qc.add_instruction(*it);
        }
        main_qc.compose(qc);
    }
    return main_qc;
}


Grover::Grover(int n, IntArr ia, int _k=1): QuantumCircuit{2*n-1} {
    int hilb_n = 1 << n;
    QuantumCircuit qc = build_grover_circ(n, ia);
    ComplexArr dif(hilb_n*hilb_n, 0);
    for(int i = 0; i < hilb_n; i++){
        dif[i*hilb_n + i] = -1;
    }

    IntArr ran(n, 0);
    for (int i=0; i < n; i++){
        this->add_instruction(instr::H(), IntArr{i});
        ran[i] = i;
    }
    this->add_instruction(instr::X(), IntArr{2*n - 2});
    this->add_instruction(instr::H(), IntArr{2*n - 2});


    dif[0] = 1;
    for (int i=0; i < n; i++){
        qc.add_instruction(instr::H(), IntArr{i});
    }
    qc.add_instruction(tensor::HSMatrix(dif), ran);
    for (int i=0; i < n; i++){
        qc.add_instruction(instr::H(), IntArr{i});
    }
    for (int i = 0; i < _k; i++){
        this->compose(qc);

    }
};