#ifndef _TEST_TENSOR_CRTP
#define _TEST_TENSOR_CRTP

#include <iostream>
#include <tuple>

#include "tests/common_test.h"
#include "inc/Tensors/tensorexpr.h"

#include <gtest/gtest.h>
using ::testing::TestWithParam;  

#include <string>


class MockTensor: public Expression<MockTensor>{
public:
	MockTensor(const Shape& shape): shape{shape}, data(1) { 
  }

  template<typename E>
	MockTensor(const Expression<E> &e)
	{
		shape = e.get_shape();
		data = e[0];
	}

  const Shape& get_shape() const noexcept { return shape; }
  DataType operator[](int i) const { return data; }
    DataType data;
    Shape shape;
};


class OpSequanTest : public TestWithParam<std::tuple<std::vector<Shape>, Shape, Shape>> {
 protected:
  std::vector<Shape> ls;
  Shape shape_prod;
  Shape shape_sum;

  void SetUp() override {
    ls = std::get<0>(GetParam());
    shape_prod = std::get<1>(GetParam());
    shape_sum = std::get<2>(GetParam());
  }
};

class Op4Test : public TestWithParam<std::tuple<std::vector<Shape>, Shape, Shape>> {
 protected:
  std::vector<Shape> ls;
  Shape shape_prod;
  Shape shape_sum;

  void SetUp() override {
    ls = std::get<0>(GetParam());
    shape_prod = std::get<1>(GetParam());
    shape_sum = std::get<2>(GetParam());
  }
};

class ProdResTest : public TestWithParam<std::tuple<std::vector<Shape>, int>> {
 protected:
  std::vector<Shape> ls;
  int num_op;

  void SetUp() override {
    ls = std::get<0>(GetParam());
    num_op = std::get<1>(GetParam());
  }
};

class ConjTest : public TestWithParam<std::tuple<Shape, Shape>> {
 protected:
  Shape shape_in;
  Shape shape_out;

  void SetUp() override {
    shape_in = std::get<0>(GetParam());
    shape_out = std::get<1>(GetParam());
  }
};
#endif