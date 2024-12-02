#ifndef _TEST_QCI
#define _TEST_QCI

#include <iostream>
#include <tuple>


#include "common_test.h"
#include "QuantumCircuit.h"
#include "instruction.h"
#include "drawer.h"
#include <gtest/gtest.h>
using ::testing::TestWithParam;  


#include <string>

struct Buffer{
public:
  std::string s;
};

typedef std::shared_ptr<Buffer> BufferPtr;


class MockProvider: public MetaProvider{
public:
  // using Executor::Executor;
  BufferPtr bfptr;
  MockProvider(const QuantumCircuit& qc, BufferPtr bfptr): MetaProvider{qc}, bfptr{bfptr} {} 
  void SetUp() override {bfptr->s = "";}
};


class MockInstuction: public Instruction{
public:  
  MockInstuction(BufferPtr _bfptr, Qubits qubs) : bfptr{_bfptr}, Instruction{qubs} { }
  virtual void apply(MetaProvider& mp) override {
    MockProvider& mock = static_cast<MockProvider&>(mp);
    mock.bfptr->s = mock.bfptr->s + this->name + ":" + this->qubits.to_str() + ";";
  }
private:
  BufferPtr bfptr;

};


class InstuctionSetUp : public TestWithParam<std::tuple<std::vector<Qubits>>> {
 protected:
  std::vector<Qubits> l;

  void SetUp() override {
    l = std::get<0>(GetParam());
  }

};


#endif