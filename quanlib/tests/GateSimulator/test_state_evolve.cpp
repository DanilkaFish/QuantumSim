#include <bits/stdc++.h>
#include <string>
#include <algorithm>
#include <memory>
#include "test_state_evolve.h"
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
    StateProvider exec(qc);
    exec.init_state = st_init;
    exec.state_evolve();
    if (i % 2 == 1){
    }else{
      EXPECT_TRUE(compare(st_init, exec.get_evolved_state())) << ERR_PREFIX << "expected:\n" << st_init << "result: \n" << exec.get_evolved_state() << "\n";
    }
    
  }
}


TEST_P(SimpleCircsTest, TestCirc) {
  
  // for(int i=1; i<6; i++){
    QuantumCircuit qc(un_set);
    StateProvider exec(qc);
    exec.init_state = init_state;
    exec.state_evolve();
    EXPECT_TRUE(compare(exp_state, exec.get_evolved_state())) << ERR_PREFIX << "expected:\n" << exp_state << "result: \n" << exec.get_evolved_state() << "\n" ;
    
  // }
}

TEST_P(PauliRotationTest, TestAdditivity){
  QuantumCircuit qc1({BaseInstr::PR(ps, 1*angle), BaseInstr::PR(ps, 1*angle)});
  QuantumCircuit qc2({BaseInstr::PR(ps, 2*angle)});
  StateProvider exec1(qc1);
  StateProvider exec2(qc2);
  exec1.init_state = init_state;
  exec2.init_state = init_state;
  exec1.state_evolve();
  exec2.state_evolve();
  double res = std::abs(Tensor{exec1.get_evolved_state().conj()* exec2.get_evolved_state()}[0]);
  EXPECT_TRUE( std::abs(res-1) < 0.0000001) << ERR_PREFIX << "exec1:\n" << exec1.get_evolved_state() << "exec2 : \n" << exec2.get_evolved_state() << "\n" ;
}

TEST_P(PauliRotationTest, TestDecomposition){
  QuantumCircuit qc1({BaseInstr::PR(ps, 1*angle)});
  QuantumCircuit qc2 = qc1.decompose();
  StateProvider exec1(qc1);
  StateProvider exec2(qc2);
  exec1.init_state = init_state;
  exec2.init_state = init_state;
  exec1.state_evolve();
  exec2.state_evolve();
  double res = std::abs(Tensor{exec1.get_evolved_state().conj()* exec2.get_evolved_state()}[0]);
  EXPECT_TRUE( std::abs(res-1) < 0.0000001) << ERR_PREFIX << "exec1:\n" << exec1.get_evolved_state() << "exec2 : \n" << exec2.get_evolved_state() << "\n" ;
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


INSTANTIATE_TEST_CASE_P(ComboValues, PauliRotationTest,
                        Combine(Values(
                                  random({0,1,2,3}),
                                  zeros({0,1,2,3}),
                                  ones({0,1,2,3}) 
                                  ),
                                Values(0.1, 1, 0.5, 3.1416/4),
                                Values(
                                  PauliString("xyz",{0,1,2} ),
                                  PauliString("zzz",{0,1,2} ),
                                  PauliString("yyx",{0,1,2} ),
                                  PauliString("zzy",{0,1,2} ),
                                  PauliString("xyz",{0,3,2} ),
                                  PauliString("xyz",{3,1,2} ),
                                  PauliString("xx",{0,3} )
                                  ),
                                Values(zeros({0,1,2,3}))
                              )
                       );


// INSTANTIATE_TEST_CASE_P(ComboValues, PauliRotationTest,
    //                     Combine(Values(
    // {ones({0,1,2,3}), zeros({0,1,2,3}), random({0,1,2,3})}),
    // std::vector<InstructionPtr>{BaseInstr::CX(0,1)},
    // std::vector<InstructionPtr>{BaseInstr::X(0)},
    // std::vector<InstructionPtr>{BaseInstr::X(0), BaseInstr::X(1)},
    // std::vector<InstructionPtr>{BaseInstr::X(0), BaseInstr::Y(1), BaseInstr::Z(2)},
    // std::vector<InstructionPtr>{BaseInstr::X(0), BaseInstr::Y(1), BaseInstr::I(2)},
    // std::vector<InstructionPtr>{BaseInstr::TOF(0,1,2)}
    //                               )
    //                         )
    //                       );