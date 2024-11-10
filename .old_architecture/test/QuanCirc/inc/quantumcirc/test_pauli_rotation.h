#ifndef _TEST_PR
#define _TEST_PR

#include <gtest/gtest.h>
#include "code/QuanCirc/inc/quantumcirc/unitary.h"

#include <iostream>
#include <string>
#include <tuple>

using ::testing::TestWithParam;  

#include "test/common_test.h"


class PrTest : public TestWithParam<std::tuple<std::tuple<IntArr, std::string>, Double>> {
 protected:
  IntArr qubits;
  std::string s;
  Double angle;

  void SetUp() override {
    qubits = std::get<0>(std::get<0>(GetParam()));
    s = std::get<1>(std::get<0>(GetParam()));
    angle = std::get<1>(GetParam());
  }

};




#endif