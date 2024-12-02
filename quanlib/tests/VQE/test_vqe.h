#ifndef _TEST_QCI
#define _TEST_QCI

#include <iostream>
#include <tuple>


#include "common_test.h"
#include "QuantumCircuit.h"
#include "instruction.h"
#include "drawer.h"
#include "vqe.h"
#include <gtest/gtest.h>
using ::testing::TestWithParam;  


#include <string>

struct Buffer{
public:
  std::string s;
};

typedef std::shared_ptr<Buffer> BufferPtr;
constexpr int exp_steps = 20;
constexpr int multip = 2;

class MockProvider: public MetaProvider{
public:
  MockProvider(const QuantumCircuit& qc): MetaProvider{qc} {} 
  double init_q=1./2;
  double q=1./2;
  double evaluate_cost() override { state_evolve(); return q;}
  void SetUp() override { q=init_q; }
};


class MockInstuction: public Instruction{
public:  
  MockInstuction(Qubits qubs, ParameterPtr angle) : Instruction{qubs}, angle{angle} { }
  virtual void apply(MetaProvider& mp) override {
    MockProvider& mock = static_cast<MockProvider&>(mp);
    mock.q = mock.q*angle->value;
  }
private:
  ParameterPtr angle;
};

class MockOptimizer: public Optimizer{
public:
  using Optimizer::Optimizer;
  DoubleVec init_value;
protected:
    using Optimizer::mp; 
    virtual std::pair<DoubleVec, double> _update() {
      double res = mp.evaluate_cost();
      DoubleVec params = pv.get_row_values();
      for(auto& x: params){
        x = x/multip;
      }
      return std::pair<DoubleVec, double>(params, res);
    };
    virtual void SetUp() override { pv.set_row_values(init_value); };
    virtual bool is_to_stop(std::pair<DoubleVec, double> data){
      return (data.second < 1./(1 << exp_steps));
    }
};


class MockCallback: public Callback{
public:  
  int gen=0;
  int sub=0;
  std::vector<double> mean;
  virtual void general_write(DoubleVec params, double cost){ gen++; mean.push_back(cost); }
};


class OptimizationTest : public TestWithParam<std::tuple<int,int>> {
 protected:
  int num_instruction;
  int max_steps;
  ParameterVector pvec;
  void SetUp() override {
    num_instruction = std::get<0>(GetParam());
    max_steps = std::get<1>(GetParam());
  }
};


#endif