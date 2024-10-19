#ifndef _TEST_BIN_UTILS
#define _TEST_BIN_UTILS

#include <gtest/gtest.h>
#include "code/QuanCirc/inc/tensors/bin_utils.h"

#include <iostream>
#include <tuple>

using ::testing::TestWithParam;  

#include "test/common_test.h"


class BinTest : public TestWithParam<std::tuple<float, float, float>> {
 protected:
  int num, pos, chg;

  void SetUp() override {
    num = std::get<0>(GetParam());
    pos = std::get<1>(GetParam());
    chg = std::get<2>(GetParam());
  }

};

class Power2Test : public TestWithParam<int> {
 protected:
  int n;

  void SetUp() override {
    n = GetParam();
  }

};

class BinsTest : public TestWithParam<std::tuple<float, IntArr, int>> {
protected:
    int num;
    IntArr poss;
    int chg;

    void SetUp() override {
        num = std::get<0>(GetParam());
        poss = std::get<1>(GetParam());
        chg = std::get<2>(GetParam());
    }

};

#endif