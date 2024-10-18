#ifndef _TEST_BIN_UTILS
#define _TEST_BIN_UTILS

#include <gtest/gtest.h>
#include "code/QuanCirc/inc/tensors/tensor.h"

#include <iostream>
#include <tuple>

using ::testing::Test;  // GTest parametric test fixture
using namespace tensor;
const char *ERR_PREFIX = ">> ";     // For printed error descriptions
const char *NOTE_PREFIX = "  $$ ";  // For printed notes/comments

class AxisOperationTest : public Test{
    protected:
    // HSMatrix l, r;

    // void SetUp() override{
    //     l = instr::CX();
    //     r = instr::H();
    // }

};

#endif