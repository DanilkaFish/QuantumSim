#include "code/QuanCirc/inc/quantumcircuit.h"
#include <vector>

std::vector<int> to_bin(int n, int range){
    std::vector<int> binv;
    for(int i = 0; i < range; n = n / 2){
        binv.push_back(n % 2);
        i++;
    }
    return binv;
}

QuantumCircuit build_grover_circ(int n, std::vector<int> vs){
    QuantumCircuit main_qc{2*n - 1};
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
                qc.add_instruction(instr::TOF(), IntArr{sdv-1,sdv, sdv + len/2 + 1});
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