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
  for (int i=0; i<(1 << qubs.qubs.size()); i++)
    vec.push_back({std::rand(), std::rand()}); //undefined behaviour

  State st_init(qubs, vec);

  for(int i=1; i<6; i++){
    QuantumCircuit qc{qubs};
    for(int j=0; j<i; j++){
      for (auto& x: un_set){
        qc.add_instuction(x); 
      }
    }
    int len_exp = i * un_set.size();
    int len_res = qc.get_instr().size();
    EXPECT_FLOAT_EQ(len_exp, len_res) << ERR_PREFIX
                                      << "Non expected circuit length";

    PureSim exec(qc, st_init);
    exec.run();

    if (i % 2 == 1){

    }else{
      EXPECT_TRUE(compare(st_init, exec.sdptr->state)) << ERR_PREFIX << "expected:\n" << st_init << "result: \n" << exec.sdptr->state << "\n";
    }
    
  }
}


TEST_P(SimpleCircsTest, TestCirc) {
  
  // for(int i=1; i<6; i++){
    QuantumCircuit qc(InstructionSet{un_set});
    PureSim exec(qc, init_state);
    exec.run();
    EXPECT_TRUE(compare(exp_state, exec.sdptr->state)) << ERR_PREFIX << "expected:\n" << exp_state << "result: \n" << exec.sdptr->state << "\n";
    
  // }
}


INSTANTIATE_TEST_CASE_P(SelectValues, SimpleCircsTest,
                        Values(
std::tuple<State,std::vector<InstructionPtr>,State>{zeros({0}),{Gate::H(0)}, Hzeros({0})},
std::tuple<State,std::vector<InstructionPtr>,State>{ones({0}),{Gate::H(0)}, Hones({0})},
std::tuple<State,std::vector<InstructionPtr>,State>{zeros({0,1,2,3}),{Gate::H(0), Gate::H(1), Gate::H(2), Gate::H(3)}, Hzeros({0,1,2,3})},
std::tuple<State,std::vector<InstructionPtr>,State>{ones({0,1,2,3}),{Gate::H(0), Gate::H(1), Gate::H(2), Gate::H(3)}, Hones({0,1,2,3})},
std::tuple<State,std::vector<InstructionPtr>,State>{zeros({0,1}), {Gate::CX(0,1)}, zeros({0,1})},
std::tuple<State,std::vector<InstructionPtr>,State>{zeros({0,1,2}), {Gate::CX(0,1), Gate::CX(1,2)}, zeros({0,1,2})},
std::tuple<State,std::vector<InstructionPtr>,State>{ones({0,1,2}), {Gate::CX(0,1), Gate::CX(1,2)}, State{{0,1,2}, {0,0,0,0,0,1,0,0}}},
std::tuple<State,std::vector<InstructionPtr>,State>{State{{0,1}, {0,1,0,0}}, {Gate::CX(0,1)}, State{{0,1}, {0,1,0,0}}},
std::tuple<State,std::vector<InstructionPtr>,State>{State{{0,1}, {0,0,1,0}}, {Gate::CX(0,1)}, State{{0,1}, {0,0,0,1}}},
std::tuple<State,std::vector<InstructionPtr>,State>{State{{0,1}, {0,0,0,1}}, {Gate::CX(0,1)}, State{{0,1}, {0,0,1,0}}}
                                  )
                          );


INSTANTIATE_TEST_CASE_P(ComboValues, SimpleSetUp,
                        Combine(Values(
                                  std::vector<InstructionPtr>{},
                                  std::vector<InstructionPtr>{Gate::CX(0,1)},
                                  std::vector<InstructionPtr>{Gate::X(0)},
                                  std::vector<InstructionPtr>{Gate::X(0), Gate::X(1)},
                                  std::vector<InstructionPtr>{Gate::X(0), Gate::Y(1), Gate::Z(2)},
                                  std::vector<InstructionPtr>{Gate::X(0), Gate::Y(1), Gate::I(2)},
                                  std::vector<InstructionPtr>{Gate::TOF(0,1,2)}
                                  )
                            )
                          );
