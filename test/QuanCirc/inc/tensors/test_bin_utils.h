#ifndef _TEST_BIN_UTILS
#define _TEST_BIN_UTILS

#include <gtest/gtest.h>
#include "code/QuanCirc/inc/tensors/bin_utils.h"

#include <iostream>
#include <tuple>

using ::testing::TestWithParam;  // GTest parametric test fixture

const char *ERR_PREFIX = ">> ";     // For printed error descriptions
const char *NOTE_PREFIX = "  $$ ";  // For printed notes/comments

class BinTest : public TestWithParam<std::tuple<float, float, float>> {
 protected:
  // Declare some member variables local to each test case
  int num, pos, chg;

  // GTest runs this before any test code
  void SetUp() override {
    // `GetParam()` fetches the parameter, then we unpack the tuple
    num = std::get<0>(GetParam());
    pos = std::get<1>(GetParam());
    chg = std::get<2>(GetParam());
  }

  // GTest runs after all test code
//   void TearDown() override {  }
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