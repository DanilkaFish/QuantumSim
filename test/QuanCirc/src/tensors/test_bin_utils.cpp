#include "test/QuanCirc/inc/tensors/test_bin_utils.h"
#include <bits/stdc++.h>
#include <string>
// GTest param generators so we don't have to write the namespace everywhere
using ::testing::Combine;
using ::testing::Values;

/* TEST_P pulls the parametric fixture of the same name from the header.
 * A list of parameters is later instantiated for *all* tests in the suite
 * (i.e. tests that are using this parametric fixture)
 *****************************************************************************/

/* Test the `add` method with various values
 *****************************************************************************/
TEST_P(BinTest, TestGetValByPos) {
  int result;
  result = bit_on_pos(num, pos);

  std::string bin_num = std::bitset<64>(num).to_string();
  int expected = int(bin_num[bin_num.size() - 1 - pos]) - int('0') ;

  // Notice the 'FLOAT' designation in our check
  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to add numbers correctly!";
}

/* Test the `mult` method with various values
 *****************************************************************************/
TEST_P(BinTest, TestChgOnPos) {
  int result;
  result = change_on_pos(num, pos, chg);

  int expected ;
  std::string bin_num = std::bitset<64>(num).to_string();
  std::string bin_chg = std::bitset<64>(chg).to_string();
  bin_num[pos] = bin_chg[pos];
  int expected = std::stoi(bin_num, nullptr, 2);

  // Notice the 'FLOAT' designation in our check
  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to multiply numbers correctly!";
}

TEST_P(BinsTest, TestGetValByPoss) {
  int result;
  result = bit_on_pos(num, poss);

  std::string bin_num = std::bitset<64>(num).to_string();
  std::string bin_chg = std::bitset<64>(0).to_string();
  for (auto pos: poss)
    bin_chg[pos] = bin_num[pos];
  int expected = std::stoi(bin_chg, nullptr, 2);

  // Notice the 'FLOAT' designation in our check
  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to add numbers correctly!";
}

/* Test the `mult` method with various values
 *****************************************************************************/
TEST_P(BinsTest, TestChgOnPoss) {
  int result;
  result = change_on_pos(num, poss, chg);

  std::string bin_num = std::bitset<64>(num).to_string();
  std::string bin_chg = std::bitset<64>(chg).to_string();
  for (auto pos: poss)
    bin_num[pos] = bin_chg[pos];
  int expected = std::stoi(bin_num, nullptr, 2);
  
  // Notice the 'FLOAT' designation in our check
  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to multiply numbers correctly!";
}

/* Define the parameter sets
 *
 * The parameter sets are run for all test cases in the test suite
 * (e.g. SweepTest in this case)
 *****************************************************************************/
// Explicitly list test cases using `Values`. This is 2 sets of params
INSTANTIATE_TEST_CASE_P(ComboValues, BinTest,
                        Combine(Values(1, 3, 20, 123, 128, 255),
                                Values(0, 2,  5),
                                Values(0, 10, 255)));

// Use `Combine` to generate all param combinations. This is 9 sets of params
INSTANTIATE_TEST_CASE_P(ComboValues, BinsTest,
                        Combine(Values(1, 3, 20, 123, 128, 255),
                                Values(IntArr{0, 2,  5}),
                                Values(0, 10, 255)));
