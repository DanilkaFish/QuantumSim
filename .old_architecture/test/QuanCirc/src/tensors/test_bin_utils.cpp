#include "test/QuanCirc/inc/tensors/test_bin_utils.h"
#include <bits/stdc++.h>
#include <string>
#include <algorithm>

using ::testing::Combine;
using ::testing::Values;

TEST_P(BinTest, TestGetValByPos) {
  int result;
  result = bit_on_pos(num, pos);

  std::string bin_num = std::bitset<64>(num).to_string();
  int expected = int(bin_num[bin_num.size() - 1 - pos]) - int('0') ;

  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to get value!";
}

TEST_P(Power2Test, TestFindPower) {
  int result;
  int num = 1 << n;
  result = find_power_2(num);
  EXPECT_EQ(n, result) << ERR_PREFIX
                                    << "Failed to get value!";
}

TEST_P(BinTest, TestChgOnPos) {
  int result;
  result = change_on_pos(num, pos, chg);

  std::string bin_num = std::bitset<64>(num).to_string();
  std::string bin_chg = std::bitset<64>(chg).to_string();
  bin_num[bin_num.size() - 1 -pos] = bin_chg[0];
  int expected = std::stoi(bin_num, nullptr, 2);

  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to change value!";
}

TEST_P(BinsTest, TestGetValByPoss) {
  int result;
  result = bit_on_pos(num, poss);

  std::string bin_num = std::bitset<64>(num).to_string();
  std::string bin_chg = std::bitset<64>(0).to_string();
  for (int i = 0; i < poss.size(); i++)
    bin_chg[bin_num.size() - 1 - i] = bin_num[bin_num.size() - 1 - poss[i]];
  int expected = std::stoi(bin_chg, nullptr, 2);

  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to get value based on array!";
}

TEST_P(BinsTest, TestChgOnPoss) {
  int result;
  result = change_on_pos(num, poss, chg);

  std::string bin_num = std::bitset<64>(num).to_string();
  std::string bin_chg = std::bitset<64>(chg).to_string();
  for (int i = 0; i < poss.size(); i++)
    bin_num[bin_num.size() - 1 - poss[i]] = bin_chg[bin_num.size() - 1 - i];
  int expected = std::stoi(bin_num, nullptr, 2);
  
  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to change value based on array";
}

TEST_P(BinTest, TestDelOnPoss) {
  int result;
  result = del_on_pos(num, IntArr{pos});

  std::string bin_num = std::bitset<64>(num).to_string();
  std::string exp_s;
  for (int i = 0; i < 64; i++){
    if ( pos != i ){
      exp_s.push_back(bin_num[bin_num.size() - 1 - i]);
    }
  }
  std::reverse(exp_s.begin(), exp_s.end());
  int expected = std::stoi(exp_s, nullptr, 2);

  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to change value based on array";
}

TEST_P(BinsTest, TestDelOnPoss) {
  int result;
  result = del_on_pos(num, poss);

  std::string bin_num = std::bitset<64>(num).to_string();
  std::string exp_s;
  for (int i = 0; i < 64; i++){
    if (std::find(poss.begin(), poss.end(), i) == poss.end()){
      exp_s.push_back(bin_num[bin_num.size() - 1 - i]);
    }
  }
  std::reverse(exp_s.begin(), exp_s.end());
  int expected = std::stoi(exp_s, nullptr, 2);

  EXPECT_FLOAT_EQ(expected, result) << ERR_PREFIX
                                    << "Failed to change value based on array";
}

INSTANTIATE_TEST_CASE_P(ComboValues, BinTest,
                        Combine(Values(1, 3, 20, 123, 128, 255),
                                Values(0, 2,  5),
                                Values(0, 10, 255)));

INSTANTIATE_TEST_CASE_P(ComboValues, BinsTest,
                        Combine(Values(1, 3, 20, 123, 128, 255),
                                Values(IntArr{0, 2,  5}),
                                Values(0, 10, 255)));

INSTANTIATE_TEST_CASE_P(SelectValues, Power2Test,
                        Values(0, 1, 2, 3, 4, 5, 10, 30));