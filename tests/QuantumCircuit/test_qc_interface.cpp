#include <bits/stdc++.h>
#include <string>
#include <algorithm>
#include <memory>
#include "test_qc_interface.h"

using ::testing::Combine;
using ::testing::Values;

TEST_P(InstuctionSetUp, TestAddInstuction) {
  
  QuantumCircuit qc{Qubits{0,1,2,3,4,5,6}};
  int exp = l.size();
  BufferPtr bf{new Buffer()};
  for (auto x: l){
    qc.add_instuction(makeInsPtr(new MockInstuction(bf, x)));
  }
  int res = qc.get_instr().size();
  std::cout << res << '\n';

  EXPECT_FLOAT_EQ(exp, res) << ERR_PREFIX
                                    << "Different circuit length";
}

TEST_P(InstuctionSetUp, TestExecuteCircuit) {
  
  QuantumCircuit qc{Qubits{0,1,2,3,4,5,6}};
  BufferPtr bf{new Buffer()};
  MockExecutor exec(qc, bf);
  for (auto x: l){
    qc.add_instuction(makeInsPtr(new MockInstuction(bf, x)));
  }
  // std::string exp = bf->s;
  std::string exp = qc.get_qcr().s;
  exec.run();
  std::string res = bf->s;
  
  EXPECT_TRUE(exp == res) << ERR_PREFIX 
                                    << res << std::endl << exp;
}

TEST_P(InstuctionSetUp, TestComposeCircuit) {
  
  QuantumCircuit qc{Qubits{0,1,2,3,4,5,6}};
  QuantumCircuit cqc{Qubits{0,1,2,3,4,5,6}};
  BufferPtr bf{new Buffer()};
  MockExecutor exec(qc, bf);
  MockExecutor cexec(cqc, bf);

  for (auto x: l){
    qc.add_instuction(makeInsPtr(new MockInstuction(bf, x)));
  }
  cqc.compose(qc);

  exec.run();
  std::string exp = bf->s;
  cexec.run();
  std::string res = bf->s;

  EXPECT_TRUE(cqc.get_instr().size() == 1) << ERR_PREFIX 
                                    << "diff sizes";
  EXPECT_TRUE(exp == res) << ERR_PREFIX 
                                    << res << std::endl << exp;
}

TEST_P(InstuctionSetUp, TestDeComposeCircuit) {
  
  QuantumCircuit qc{Qubits{0,1,2,3,4,5,6}};
  QuantumCircuit cqc{Qubits{0,1,2,3,4,5,6}};
  BufferPtr bf{new Buffer()};
  MockExecutor exec(qc, bf);
  MockExecutor cexec(cqc, bf);

  for (auto x: l){
    qc.add_instuction(makeInsPtr(new MockInstuction(bf, x)));
  }
  cqc.compose(qc);
  cqc.decompose();

  exec.run();
  std::string exp = bf->s;
  cexec.run();
  std::string res = bf->s;

  EXPECT_TRUE(cqc.get_instr().size() == l.size()) << ERR_PREFIX 
                                    << "diff sizes";

  EXPECT_TRUE(exp == res) << ERR_PREFIX 
                                    << res << std::endl << exp;
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