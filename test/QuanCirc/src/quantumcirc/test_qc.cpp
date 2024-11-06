#include "test/QuanCirc/inc/quantumcirc/test_qc.h"
#include "code/QuanCirc/inc/quantumcirc/unitary.h"
// #include
#include <bits/stdc++.h>
#include <string>
#include <algorithm>

using ::testing::Combine;
using ::testing::Values;


TEST_P(ProdTest, TestCheckQubits) {
  Instruction res = instruction_prod(Instruction{tensor::HSMatrix(l.size()), l}, Instruction{tensor::HSMatrix(r.size()), r});
  IntArr comm_qubits;
  for (auto x: l){
      if (std::find(r.begin(), r.end(), x) != r.end()){
          comm_qubits.push_back(x);
      }
  }

  EXPECT_EQ(r.size() + l.size() - comm_qubits.size(), res.qubits.size()) << ERR_PREFIX
                                    << "tot!";
}

TEST_P(ProdTest, TestCheckIdentityProd) {
  Instruction left = Instruction{instr::I(), IntArr{l[0]}};
  for(int i=1; i<l.size(); i++){
    left = instruction_prod(left, Instruction{instr::I(), IntArr{l[i]}});
  }
  Instruction right = Instruction{instr::I(), IntArr{r[0]}};
  for(int i=1; i<r.size(); i++){
    right = instruction_prod(right, Instruction{instr::I(), IntArr{r[i]}});
  }

  Instruction res = instruction_prod(left, right);

  Instruction expect{tensor::HSMatrix{res.qubits.size()}, res.qubits};
  int n = 1 << res.qubits.size();
  for(int i=0; i<expect.un.size(); i++){
    if (i / n == i % n){
        expect.un[i] = 1;
    }else{
        expect.un[i] = 0;
    }
  }

  for (int i=0; i<expect.un.size(); i++){
    EXPECT_EQ(expect.un[i], res.un[i]) << ERR_PREFIX
                                        << i;
  }
}

TEST_P(ProdTest, TestCheckXProd) {
  Instruction left = Instruction{instr::X(), IntArr{l[0]}};
  for(int i=1; i<l.size(); i++){
    left = instruction_prod(left, Instruction{instr::X(), IntArr{l[i]}});
  }
  Instruction right = Instruction{instr::X(), IntArr{r[0]}};
  for(int i=1; i<r.size(); i++){
    right = instruction_prod(right, Instruction{instr::X(), IntArr{r[i]}});
  }

  Instruction res = instruction_prod(left, right);
//   Instruction res = left;

  Instruction expect{tensor::HSMatrix{res.qubits.size()}, res.qubits};
  int n = 1 << res.qubits.size();
  for(int i=0; i<expect.un.size(); i++){
    if (i / n + i % n == n - 1){
        expect.un[i] = 1;
    }else{
        expect.un[i] = 0;
    }
  }

  for (int i=0; i<expect.un.size(); i++){
    EXPECT_EQ(expect.un[i], res.un[i]) << ERR_PREFIX
                                        << i;
  }
}

INSTANTIATE_TEST_CASE_P(ComboValues, ProdTest,
                        Combine(Values(IntArr{2}, IntArr{2,3,5}, IntArr{1,2,5}, IntArr{1}),
                                Values(IntArr{1,2,5}, IntArr{2,1,5}, IntArr{5,7,3,4}, IntArr{1})));

// INSTANTIATE_TEST_CASE_P(ComboValues, ProdTest,
//                         Combine(Values(IntArr{1,2,5}, IntArr{1,2}, IntArr{2,3,5}),
//                                 Values(IntArr{1,2,5})));