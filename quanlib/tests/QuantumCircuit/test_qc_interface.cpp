#include <bits/stdc++.h>
#include <string>
#include <algorithm>
#include <memory>
#include "test_qc_interface.h"

using ::testing::Combine;
using ::testing::Values;

TEST_P(InstuctionSetUp, TestAddInstuction) {
  
  QuantumCircuit qc;
  int exp = l.size();
  BufferPtr bf{new Buffer()};
  for (auto x: l){
    qc.add_instruction(InstructionPtr(new MockInstuction(bf, x)));
  }
  int res = qc.size();
  std::cout << res << '\n';

  EXPECT_FLOAT_EQ(exp, res) << ERR_PREFIX
                                    << "Different circuit length";
}

TEST_P(InstuctionSetUp, TestExecuteCircuit) {
  
  QuantumCircuit qc;
  BufferPtr bf{new Buffer()};
  MockProvider exec(qc, bf);
  for (auto x: l){
    qc.add_instruction(InstructionPtr(new MockInstuction(bf, x)));
  }
  // std::string exp = bf->s;
  std::string exp = qc.get_qcr().s;
  exec.state_evolve();
  std::string res = bf->s;
  
  EXPECT_TRUE(exp == res) << ERR_PREFIX 
                                    << res << std::endl << exp << "hello";
}

TEST_P(InstuctionSetUp, TestComposeCircuit) {
  
  QuantumCircuit qc;
  QuantumCircuit cqc;
  BufferPtr bf{new Buffer()};
  MockProvider exec(qc, bf);
  MockProvider cexec(cqc, bf);

  for (auto x: l){
    qc.add_instruction(InstructionPtr(new MockInstuction(bf, x)));
  }
  cqc.compose(qc);

  exec.state_evolve();
  std::string exp = bf->s;
  cexec.state_evolve();
  std::string res = bf->s;

  EXPECT_TRUE(cqc.size() == 1) << ERR_PREFIX 
                                    << "diff sizes";

  EXPECT_TRUE(exp == res) << ERR_PREFIX 
                                    << res << std::endl << exp;
  cqc.compose(qc);
  cqc.compose(cqc);

}

TEST_P(InstuctionSetUp, TestDeComposeCircuit) {
  
  QuantumCircuit qc;
  QuantumCircuit cqc;
  BufferPtr bf{new Buffer()};
  MockProvider exec(qc, bf);
  MockProvider cexec(cqc, bf);

  for (auto x: l){
    qc.add_instruction(InstructionPtr(new MockInstuction(bf, x)));
  }
  cqc.compose(qc);
  cqc = cqc.decompose();
  EXPECT_TRUE(cqc.size() == qc.size()) << ERR_PREFIX 
                                  << "diff sizes" << cqc.size() << std::endl << qc.size();
  exec.state_evolve();
  std::string exp = bf->s;
  cexec.state_evolve();
  std::string res = bf->s;


  EXPECT_TRUE(exp == res) << ERR_PREFIX 
                                    << res << std::endl << exp;
  // cqc.compose(cqc.decompose());
}

std::vector<Qubits> qc = std::vector<Qubits>{Qubits({1})};
INSTANTIATE_TEST_CASE_P(ComboValues, InstuctionSetUp,
                        Combine(Values(
                                  std::vector<Qubits>{},
                                  std::vector<Qubits>{Qubits({0})},
                                  std::vector<Qubits>{Qubits({1})},
                                  std::vector<Qubits>{Qubits({1}), Qubits({2})},
                                  std::vector<Qubits>{Qubits({1}), Qubits({2}), Qubits({3})},
                                  std::vector<Qubits>{Qubits({2}), Qubits({3}), Qubits({1})},
                                  std::vector<Qubits>{Qubits({0}), Qubits({0}),Qubits({0}),Qubits({0}),Qubits({0})},
                                  std::vector<Qubits>{Qubits({1,2,3})},
                                  std::vector<Qubits>{Qubits({1,2,3}), Qubits({0,2,3}),Qubits({1,2,3}),Qubits({0})}
                                  )
                            )
                          );
