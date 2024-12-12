// #include <bits/stdc++.h>
// #include <string>
// #include <algorithm>
// #include <memory>
// #include "test_vqe.h"

// using ::testing::Combine;
// using ::testing::Values;


// TEST_P(OptimizationTest, TestGeneration){
//   for (int i=0; i<num_instruction; i++){
//     pvec.gen_next();
//   }
//   EXPECT_TRUE(num_instruction == pvec.size()) << ERR_PREFIX << "gen_next is not working in ParamtereVector";
// }

// TEST_P(OptimizationTest, TestSet){
//   DoubleVec update(num_instruction, 2);
//   for (int i=0; i<num_instruction; i++){
//     pvec.gen_next();
//   }
//   pvec.set_row_values(update);
//   for (int i=0; i<num_instruction; i++){
//     EXPECT_TRUE(update[i] == pvec.get_i(i)->value) << ERR_PREFIX << "gen_next is not working in ParamtereVector";
//   }
// }

// TEST_P(OptimizationTest, TestGet){
//   DoubleVec update(num_instruction, 2);
//   for (int i=0; i<num_instruction; i++){
//     pvec.gen_next();
//   }
//   pvec.set_row_values(update);
//   DoubleVec updated = pvec.get_row_values();
//   for (int i=0; i<num_instruction; i++){
//     EXPECT_TRUE(update[i] == updated[i]) << ERR_PREFIX << "gen_next is not working in ParamtereVector";
//   }
// }



// TEST_P(OptimizationTest, convergenceandcallback) {
  
//   QuantumCircuit qc;
//   for(int i=0; i<num_instruction; i++){
//     qc.add_instruction(InstructionPtr(new MockInstuction(Qubits{0,1}, pvec.gen_next())));
//   }

//   MockProvider exec(qc);
//   MockCallback cb{};
//   MockOptimizer opt(exec, pvec, cb);
//   opt.init_value = DoubleVec(num_instruction, 1);
//   auto res = opt.optimize(max_steps);
//   if ((num_instruction > 0) & (max_steps*num_instruction > exp_steps)){
//     EXPECT_TRUE(res.second < 1./(1<<exp_steps)) << ERR_PREFIX
//                                       <<"enough steps " << res.second;
//   }else{
//     EXPECT_TRUE(cb.gen == max_steps) << ERR_PREFIX
//                                       << "not enough steps\n" << cb.gen << "\n" << max_steps;
//   }
// }

// INSTANTIATE_TEST_CASE_P(ComboValues, OptimizationTest,
//                         Combine(Values(0,1,5),
//                                 Values(1,10,100))
//                           );
