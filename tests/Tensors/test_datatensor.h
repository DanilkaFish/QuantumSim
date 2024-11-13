#ifndef _TEST_TENSOR_CRTP
#define _TEST_TENSOR_CRTP

#include <iostream>
#include <tuple>

#include "tests/common_test.h"
#include "inc/Tensors/tensor.h"

#include <gtest/gtest.h>
using ::testing::TestWithParam;  

#include <string>

Tensor X(Int qub=0){
  return Tensor({{qub}, {qub}}, {0,1,1,0});
}

Tensor Y(Int qub=0){
  return Tensor({{qub}, {qub}}, {0, {0,-1}, {0, 1}, 0});
}

Tensor I(Int qub=0){
  return Tensor{{{qub}, {qub}}, {1,0,0,1}};
}

Tensor Z(Int qub=0){
  return Tensor{{{qub}, {qub}}, {1,0,0,-1}};
}

Tensor CX(){
  return Tensor({{0,1},{0,1}}, {
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


#endif