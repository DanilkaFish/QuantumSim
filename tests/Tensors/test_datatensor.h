#ifndef _TEST_TENSOR_CRTP
#define _TEST_TENSOR_CRTP

#include <iostream>
#include <tuple>

#include "tests/common_test.h"
#include "inc/Tensors/tensor.h"

#include <gtest/gtest.h>
using ::testing::TestWithParam;  

#include <string>

Tensor X(int qub=0){
  return Tensor(Qubits{qub}, Qubits{qub}, {0,1,1,0});
}

Tensor Y(int qub=0){
  return Tensor(Qubits{qub}, Qubits{qub}, {0, {0,-1}, {0, 1}, 0});
}

Tensor I(int qub=0){
  return Tensor{Qubits{qub}, Qubits{qub}, {1,0,0,1}};
}

Tensor Z(int qub=0){
  return Tensor{Qubits{qub}, Qubits{qub}, {1,0,0,-1}};
}

Tensor CX(){
  return Tensor({0,1},{0,1}, {
    1,0,0,0,
    0,1,0,0,
    0,0,0,1,
    0,0,1,0
  });
}

class PowerProdTest : public TestWithParam<std::tuple<Tensor>> {
 protected:
  Tensor _T;

  void SetUp() override {
    _T = std::get<0>(GetParam());
  }
};

class PauliProdTest : public TestWithParam<std::tuple<Tensor,Tensor, Tensor>> {
 protected:
  Tensor Tl;
  Tensor Tr;
  Tensor res;

  void SetUp() override {
    Tl = std::get<0>(GetParam());
    Tr = std::get<1>(GetParam());
    res = std::get<2>(GetParam());
  }
};


class CXTest : public TestWithParam<std::tuple<Tensor, Tensor, Tensor, Tensor>> {
 protected:
  Tensor T1;
  Tensor T2;
  Tensor T3;
  Tensor T4;

  void SetUp() override {
    T1 = std::get<0>(GetParam());
    T2 = std::get<1>(GetParam());
    T3 = std::get<2>(GetParam());
    T4 = std::get<3>(GetParam());
  }
};

class BraketTest : public TestWithParam<Qubits> {
 protected:
  Qubits qubs;

  void SetUp() override {
    qubs = GetParam();
  }
};


#endif