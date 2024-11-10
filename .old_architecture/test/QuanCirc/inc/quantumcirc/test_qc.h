#ifndef _TEST_INSTR
#define _TEST_INSTR

#include <gtest/gtest.h>
#include "code/QuanCirc/inc/quantumcirc/quantumcircuit.h"

#include <iostream>
#include <tuple>

using ::testing::TestWithParam;  

#include "test/common_test.h"


class ProdTest : public TestWithParam<std::tuple<IntArr, IntArr>> {
 protected:
  IntArr l;
  IntArr r;

  void SetUp() override {
    l = std::get<0>(GetParam());
    r = std::get<1>(GetParam());
  }

};


#endif