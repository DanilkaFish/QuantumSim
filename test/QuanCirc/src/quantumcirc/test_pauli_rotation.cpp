#include "test/QuanCirc/inc/quantumcirc/test_pauli_rotation.h"
#include "code/QuanCirc/inc/quantumcirc/unitary.h"
// #include <bits/stdc++.h>
// #include <string>
// #include <algorithm>

using ::testing::Combine;
using ::testing::Values;


TEST_P(PrTest, TestUnitary) {
  PauliString ps(s, qubits, true);
  Instruction I = Instruction{instr::I(), IntArr{qubits[0]}};
  for(int i=1; i < qubits.size(); i++){
    I = instruction_prod(I, Instruction{instr::I(), IntArr{qubits[i]}});
  }
  Instruction Pauli = ps.to_instruction();
  Instruction expect = Instruction{Complex(cos(angle/2)) * I.un + sin(angle/2) * tensor::i*(Pauli.un), Pauli.qubits};
  QuantumCircuit qc{10};
  qc.add_instruction(instr::PR(angle,  ps));
  std::cout << qc;
  for (auto x: qc.get_qc_data()){
    std::cout<<x.un;
  }
  Instruction res = qc.to_instruction();
  std::cout << res.un;
  std::cout << expect.un;
  for (int i=0; i<expect.un.size(); i++){
    ASSERT_NEAR(expect.un[i].real(), res.un[i].real(), 0.000001) << ERR_PREFIX << i;
    ASSERT_NEAR(expect.un[i].imag(), res.un[i].imag(), 0.000001) << ERR_PREFIX << i;
  }
}

INSTANTIATE_TEST_CASE_P(ComboValues, PrTest,
                        Combine(Values( 
                                       std::make_tuple(IntArr{1}, "x"), 
                                       std::make_tuple(IntArr{1}, "z"),
                                       std::make_tuple(IntArr{3,1}, "xy"),
                                       std::make_tuple(IntArr{3,1}, "yz"),
                                       std::make_tuple(IntArr{3,1}, "xx"),
                                       std::make_tuple(IntArr{3,1,4,6,5}, "xyzzz"),
                                       std::make_tuple(IntArr{1}, "y"),
                                       std::make_tuple(IntArr{3,1}, "zz")
                                       ),
                                Values(0., 321., 3.14/2.)));

