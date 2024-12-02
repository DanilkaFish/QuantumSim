#ifndef _TEST_QCI
#define _TEST_QCI

#include <iostream>
#include <tuple>
#include <string>
#include <random>
#include <gtest/gtest.h>

#include "common_test.h"
#include "tensorspec.h"
#include "state_evolve.h"
#include "QuantumCircuit.h"


using ::testing::TestWithParam;  

State random(Qubits qubs){
  Data data(1 << qubs.size(), 0);
  double norm=0;
  for (auto& x: data){
    x = DataType(double(std::rand())/(1<<30), double(std::rand())/(1<<30));
    norm += std::real(std::conj(x)*x);
  }
  norm = std::sqrt(norm); 
  for (auto& x: data){
    x = x/norm;
  } 
  return State(qubs, data);
}

State zeros(Qubits qubs){
  Data data(1 << qubs.size(), 0);
  data[0] = 1;
  return State(qubs, data);
}

State ones(Qubits qubs){
  Data data(1 << qubs.size(), 0);
  data[data.size() - 1] = 1;
  return State(qubs, data);
}

State Hzeros(Qubits qubs){
  Data data(1 << qubs.size(), 1./sqrt(1 << qubs.size()));
  return State(qubs, data);
}

State Hones(Qubits qubs){
  Data data(1 << qubs.size());
  DataType d = 1./sqrt(1 << qubs.size());
  for (int i=0; i<data.size(); i++){
    if (index_sum(i) % 2){
      data[i] = d * (-1.);
    }else{
      data[i] = d;
    }
  }
  return State(qubs, data);
}

class SimpleSetUp : public TestWithParam<std::tuple<std::vector<InstructionPtr>>> {
 protected:
  std::vector<InstructionPtr> un_set;
  void SetUp() override {
    un_set = std::get<0>(GetParam());
  }
};

class SimpleCircsTest : public TestWithParam<std::tuple<State, std::vector<InstructionPtr>, State>> {
 protected:
  State init_state;
  std::vector<InstructionPtr> un_set;
  State exp_state;
  void SetUp() override {
    init_state = std::get<0>(GetParam());
    un_set = std::get<1>(GetParam());
    exp_state = std::get<2>(GetParam());
  }
};

class PauliRotationTest : public TestWithParam<std::tuple<State, double, PauliString, State>> {
  protected:
  State init_state;
  double angle;
  PauliString ps;
  State exp_state;
  void SetUp() override {
    init_state = std::get<0>(GetParam());
    angle = std::get<1>(GetParam());
    ps = std::get<2>(GetParam());
    exp_state = std::get<3>(GetParam());
  }
};

#endif