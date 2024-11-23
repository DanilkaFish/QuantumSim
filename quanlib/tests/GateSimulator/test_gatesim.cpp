#include <bits/stdc++.h>
#include <string>
#include <algorithm>
#include <memory>
#include "test_gatesim.h"
using ::testing::Combine;
using ::testing::Values;

TEST_P(SimpleSetUp, TestIdentityCictuits) {
  int n = 0;
  Qubits qubs{0,1,2,3,4};
  Data vec;
  for (int i=0; i<(1 << qubs.size()); i++)
    vec.push_back({std::rand(), std::rand()}); //undefined behaviour

  State st_init(qubs, vec);

  for(int i=1; i<6; i++){
    QuantumCircuit qc{};
    for(int j=0; j<i; j++){
      for (auto& x: un_set){
        qc.add_instruction(x); 
      }
    }
    int len_exp = i * un_set.size();
    int len_res = qc.size();
    EXPECT_FLOAT_EQ(len_exp, len_res) << ERR_PREFIX
                                      << "Non expected circuit length";
    TensorProvider exec(qc);
    exec.state = st_init;
    exec.run();
    if (i % 2 == 1){
    }else{
      EXPECT_TRUE(compare(st_init, exec.state)) << ERR_PREFIX << "expected:\n" << st_init << "result: \n" << exec.state << "\n";
    }
    
  }
}


TEST_P(SimpleCircsTest, TestCirc) {
  
  // for(int i=1; i<6; i++){
    QuantumCircuit qc(un_set);
    TensorProvider exec(qc);
    exec.state = init_state;
    exec.run();
    EXPECT_TRUE(compare(exp_state, exec.state)) << ERR_PREFIX << "expected:\n" << exp_state << "result: \n" << exec.state << "\n";
    
  // }
}


INSTANTIATE_TEST_CASE_P(SelectValues, SimpleCircsTest,
                        Values(
    std::tuple<State,std::vector<InstructionPtr>,State>{zeros({0}),{BaseInstr::H(0)}, Hzeros({0})},
    std::tuple<State,std::vector<InstructionPtr>,State>{ones({0}),{BaseInstr::H(0)}, Hones({0})},
    std::tuple<State,std::vector<InstructionPtr>,State>{zeros({0,1,2,3}),{BaseInstr::H(0), BaseInstr::H(1), BaseInstr::H(2), BaseInstr::H(3)}, Hzeros({0,1,2,3})},
    std::tuple<State,std::vector<InstructionPtr>,State>{ones({0,1,2,3}),{BaseInstr::H(0), BaseInstr::H(1), BaseInstr::H(2), BaseInstr::H(3)}, Hones({0,1,2,3})},
    std::tuple<State,std::vector<InstructionPtr>,State>{zeros({0,1}), {BaseInstr::CX(0,1)}, zeros({0,1})},
    std::tuple<State,std::vector<InstructionPtr>,State>{zeros({0,1,2}), {BaseInstr::CX(0,1), BaseInstr::CX(1,2)}, zeros({0,1,2})},
    std::tuple<State,std::vector<InstructionPtr>,State>{ones({0,1,2}), {BaseInstr::CX(0,1), BaseInstr::CX(1,2)}, State{{0,1,2}, {0,0,0,0,0,1,0,0}}},
    std::tuple<State,std::vector<InstructionPtr>,State>{State{{0,1}, {0,1,0,0}}, {BaseInstr::CX(0,1)}, State{{0,1}, {0,1,0,0}}},
    std::tuple<State,std::vector<InstructionPtr>,State>{State{{0,1}, {0,0,1,0}}, {BaseInstr::CX(0,1)}, State{{0,1}, {0,0,0,1}}},
    std::tuple<State,std::vector<InstructionPtr>,State>{State{{0,1}, {0,0,0,1}}, {BaseInstr::CX(0,1)}, State{{0,1}, {0,0,1,0}}}
                                  )
                          );


INSTANTIATE_TEST_CASE_P(ComboValues, SimpleSetUp,
                        Combine(Values(
    std::vector<InstructionPtr>{},
    std::vector<InstructionPtr>{BaseInstr::CX(0,1)},
    std::vector<InstructionPtr>{BaseInstr::X(0)},
    std::vector<InstructionPtr>{BaseInstr::X(0), BaseInstr::X(1)},
    std::vector<InstructionPtr>{BaseInstr::X(0), BaseInstr::Y(1), BaseInstr::Z(2)},
    std::vector<InstructionPtr>{BaseInstr::X(0), BaseInstr::Y(1), BaseInstr::I(2)},
    std::vector<InstructionPtr>{BaseInstr::TOF(0,1,2)}
                                  )
                            )
                          );
