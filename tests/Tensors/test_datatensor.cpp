#include "test_datatensor.h"

using ::testing::Combine;
using ::testing::Values;




// TEST_P(PowerProdTest, TestPowerProd) {
//   for(int num_prod=1; num_prod<10; num_prod++){
//     Tensor T{_T};
//     for (int i=1; i<num_prod; i++){
//       T = T * _T;
//     }
//     if (num_prod % 2 ){
//       EXPECT_TRUE(_T == T) << ERR_PREFIX << "expected:\n" << _T << "result: \n" << T << "\n" << num_prod;
//     }else{
//       EXPECT_TRUE(I() == T) << ERR_PREFIX << "expected:\n" << I() << "result: \n" << T << "\n" << num_prod;
//     }
//   }
// }


// TEST_P(PowerProdTest, TestSimpleSumProd) {

//   for(int num_prod=1; num_prod<10; num_prod++){
//     Tensor T{_T};
//     for (int i=1; i<num_prod; i++){
//       T = T + _T;
//     }
//     Tensor res{Tensor(num_prod)*_T};
//     EXPECT_TRUE(T == res) << ERR_PREFIX << "expected:\n" << res << "result: \n" << T<< "\n" << num_prod;
//   }
// }

// TEST_P(PauliProdTest, TestCommProd) {

//   Tensor T = Tl*Tr;
//   EXPECT_TRUE(T == res) << ERR_PREFIX << "expected:\n" << res << "result: \n" << T<< "\n";
// }

TEST(SimpleTest, CXviasum) {

  // Tensor T = (I(0)*Z(1) );
  Tensor T = Tensor{0.5}*(I(0)*I(1) + Z(0)*I(1) + I(0)*X(1) - Z(0)*X(1));
  Tensor res = CX();
  EXPECT_TRUE(T == res) << ERR_PREFIX << "expected:\n" << res << "result: \n" << T<< "\n";
}

// INSTANTIATE_TEST_CASE_P(SelectValues, PowerProdTest,
//                         Values(I(), X(), Y(), Z())
//                           );

// INSTANTIATE_TEST_CASE_P(SelectValues, PauliProdTest,
//                         Values(
//                           std::tuple<Tensor,Tensor,Tensor>(I(), X(), X()), 
//                           std::tuple<Tensor,Tensor,Tensor>(I(), Y(), Y()), 
//                           std::tuple<Tensor,Tensor,Tensor>(I(), Z(), Z()), 
//                           std::tuple<Tensor,Tensor,Tensor>(X(), I(), X()), 
//                           std::tuple<Tensor,Tensor,Tensor>(Y(), I(), Y()), 
//                           std::tuple<Tensor,Tensor,Tensor>(Z(), I(), Z()), 
//                           std::tuple<Tensor,Tensor,Tensor>(X(), Y(), Tensor(DataType{0,1})*Z()), 
//                           std::tuple<Tensor,Tensor,Tensor>(Y(), Z(), Tensor(DataType{0,1})*X()), 
//                           std::tuple<Tensor,Tensor,Tensor>(Z(), X(), Tensor(DataType{0,1})*Y())
//                           )
//                           );





