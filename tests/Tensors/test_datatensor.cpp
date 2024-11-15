#include "test_datatensor.h"
#include <cstdlib>

using ::testing::Combine;
using ::testing::Values;




TEST_P(PowerProdTest, TestPowerProd) {
  for(int num_prod=1; num_prod<10; num_prod++){
    Tensor T{_T};
    for (int i=1; i<num_prod; i++){
      T = T * _T;
    }
    if (num_prod % 2 ){
      EXPECT_TRUE(_T == T) << ERR_PREFIX << "expected:\n" << _T << "result: \n" << T << "\n" << num_prod;
    }else{
      EXPECT_TRUE(I() == T) << ERR_PREFIX << "expected:\n" << I() << "result: \n" << T << "\n" << num_prod;
    }
  }
}


TEST_P(PowerProdTest, TestSimpleSumProd) {

  for(int num_prod=1; num_prod<10; num_prod++){
    Tensor T{_T};
    for (int i=1; i<num_prod; i++){
      T = T + _T;
    }
    Tensor res{Tensor(num_prod)*_T};
    EXPECT_TRUE(T == res) << ERR_PREFIX << "expected:\n" << res << "result: \n" << T<< "\n" << num_prod;
  }
}

TEST_P(PauliProdTest, TestCommProd) {

  Tensor T = Tl*Tr;
  EXPECT_TRUE(T == res) << ERR_PREFIX << "expected:\n" << res << "result: \n" << T<< "\n";
}

TEST_P(CXTest, CXviasum) {

  Tensor T = Tensor(0.5)*(T1 + T2 + T3 - T4);
  Tensor res = CX();
  EXPECT_TRUE(T == res) << ERR_PREFIX << "expected:\n" << res << "result: \n" << T<< "\n";
}

TEST(SimpleTests, CX_acting) {

  // Tensor T = Tensor(0.5)*(T1 + T2 + T3 - T4);
  Tensor _CX = CX();
  Tensor res = _CX*Tensor{{{0,1}, {}}, DataPtr{ new Data{0,0,1,0}}};
  Tensor exp = Tensor{{{0,1}, {}}, DataPtr{ new Data{0,0,0,1}}};
  EXPECT_TRUE(exp == res) << ERR_PREFIX << "expected:\n" << exp << "result: \n" << res<< "\n";
}

TEST_P(BraketTest, ProdTest) {
  Data data;
  for (int i=0; i<(1 << qubs.qubs.size()); i++)
    data.push_back({std::rand(), std::rand()}); // undefined behaviour but doesnt matter
  DataType exp=0;
  for (auto x: data){
    exp += std::conj(x)*x;
  }
  Tensor T{Shape{qubs,{}}, data};
  Tensor res = T.conj()*T;
  EXPECT_TRUE(res == Tensor{exp}) << ERR_PREFIX << "expected:\n" << res << "result: \n" << exp<< "\n";
}


INSTANTIATE_TEST_CASE_P(SelectValues, PowerProdTest,
                        Values(I(), X(), Y(), Z())
                          );

INSTANTIATE_TEST_CASE_P(SelectValues, PauliProdTest,
                        Values(
                          std::tuple<Tensor,Tensor,Tensor>(I(), X(), X()), 
                          std::tuple<Tensor,Tensor,Tensor>(I(), Y(), Y()), 
                          std::tuple<Tensor,Tensor,Tensor>(I(), Z(), Z()), 
                          std::tuple<Tensor,Tensor,Tensor>(X(), I(), X()), 
                          std::tuple<Tensor,Tensor,Tensor>(Y(), I(), Y()), 
                          std::tuple<Tensor,Tensor,Tensor>(Z(), I(), Z()), 
                          std::tuple<Tensor,Tensor,Tensor>(X(), Y(), Tensor(DataType{0,1})*Z()), 
                          std::tuple<Tensor,Tensor,Tensor>(Y(), Z(), Tensor(DataType{0,1})*X()), 
                          std::tuple<Tensor,Tensor,Tensor>(Z(), X(), Tensor(DataType{0,1})*Y())
                          )
                          );

INSTANTIATE_TEST_CASE_P(ComboValues, CXTest,
                        Combine(
                          Values(I(0)*I(1), I(1)*I(0)),
                          Values(I(0)*X(1), X(1)*I(0)),
                          Values(Z(0)*I(1), I(1)*Z(0)),
                          Values(Z(0)*X(1), X(1)*Z(0))
                        )
                          );

INSTANTIATE_TEST_CASE_P(SelectValues, BraketTest,
                          Values(Qubits{0}, Qubits{0,1}, Qubits{0,1,2}, Qubits{0,1,2,3}, Qubits{3,2,1,0}, Qubits{123,432,5,1})
                          );

