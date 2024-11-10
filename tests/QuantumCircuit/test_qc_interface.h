#ifndef _TEST_QCI
#define _TEST_QCI

#include <iostream>
#include <tuple>


#include "tests/common_test.h"


#include "inc/QuantumCircuit/__init__.h"

#include <gtest/gtest.h>
using ::testing::TestWithParam;  


#include <string>
struct Buffer{
public:
  std::string s;
};

typedef std::shared_ptr<Buffer> BufferPtr;

class MockInstuction: public Instruction{
public:  
  MockInstuction(BufferPtr _bfptr, Qubits qubs) : bfptr{_bfptr}, Instruction{qubs} { }
private:
  BufferPtr bfptr;
  void apply() override{
    bfptr->s = bfptr->s + this->name + ":" + this->qubits.to_str() + ";";
  }
};

class MockExecutor: public Executor{
public:
  // using Executor::Executor;

  BufferPtr bfptr;
  MockExecutor(QuantumCircuit& qc, BufferPtr bfptr): Executor{qc}, bfptr{bfptr} {} 
  void SetUp() override {bfptr->s = "";}
};

class InstuctionSetUp : public TestWithParam<std::tuple<std::vector<Qubits>>> {
 protected:
  std::vector<Qubits> l;

  void SetUp() override {
    l = std::get<0>(GetParam());
  }

};


#endif