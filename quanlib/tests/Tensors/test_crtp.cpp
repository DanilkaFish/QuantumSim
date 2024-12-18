// #include <bits/stdc++.h>
// #include <string>
// #include <algorithm>
// #include <memory>
#include "test_crtp.h"

using ::testing::Combine;
using ::testing::Values;


TEST_P(OpSequanTest, TestShapeProd) {
  MockTensor T{ls[0]};
  std::cerr << T.get_shape();
  for (int i=1; i<ls.size(); i++){
	  T = T * MockTensor{ls[i]};
    std::cerr << T.get_shape();
  }
  EXPECT_TRUE(shape_prod == T.get_shape()) << ERR_PREFIX << "expected:\n" << shape_prod << "result: \n" << T.get_shape();
} 

// TEST_P(OpSequanTest, TestShapeSum) {
//   MockTensor T{ls[0]};
//   for (int i=1; i<ls.size(); i++){
// 	  T = T + MockTensor{ls[i]};
//   }
//   EXPECT_TRUE(shape_sum == T.get_shape()) << ERR_PREFIX << "expected:\n" << shape_sum << "result: \n" << T.get_shape();
// } 

TEST_P(Op4Test, TestSimProd) {
  MockTensor T = MockTensor{ls[0]} * MockTensor{ls[1]} * MockTensor{ls[2]} * MockTensor{ls[3]};
  EXPECT_TRUE(shape_prod == T.get_shape()) <<"\n" <<  ERR_PREFIX << "\n" << shape_prod << "expected \n" << T.get_shape();
}

// TEST_P(Op4Test, TestSimSum) {
//   MockTensor T = MockTensor{ls[0]} * MockTensor{ls[1]} * MockTensor{ls[2]} * MockTensor{ls[3]};
//   EXPECT_TRUE(shape_prod == T.get_shape()) <<"\n" <<  ERR_PREFIX << "\n" << shape_sum << "expected \n" << T.get_shape();
// }

TEST_P(ProdResTest, TestDataRes) {
  MockTensor T{ls[0]};
  for (int i=1; i<ls.size(); i++){
	  T = T * MockTensor{ls[i]};
  }

  EXPECT_TRUE(T.data == DataType(num_op)) << ERR_PREFIX << "\n" << "result  : " << T.data << "expected: " << num_op;
}

TEST_P(ConjTest, TestConj) {
  MockTensor T{shape_in};

  T = T.conj();
  EXPECT_TRUE(T.get_shape() == shape_out) << ERR_PREFIX << "\n" << "result  : " << T.get_shape() << "expected: " << shape_out;

  T = T.conj().conj();
  EXPECT_TRUE(T.get_shape() == shape_out) << ERR_PREFIX << "\n" << "result  : " << T.get_shape() << "expected: " << shape_out;
}



INSTANTIATE_TEST_CASE_P(SelectValues, OpSequanTest,
                        Values(
							std::tuple<std::vector<Shape>, Shape, Shape>({{Qubits{{0}}, Qubits{{0}}}}, {Qubits{{0}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0}}}),
							std::tuple<std::vector<Shape>, Shape, Shape>({{Qubits{{0}}, Qubits{{0}}}, {Qubits{{1,2}}, Qubits{{1,2}}}}, {Qubits{{0,1,2}}, Qubits{{0,1,2}}}, {Qubits{{0,1,2}}, Qubits{{0,1,2}}}),
							std::tuple<std::vector<Shape>, Shape, Shape>({{Qubits{{0}}, Qubits{{0}}}, {Qubits{}, Qubits{{1,2}}}}, {Qubits{{0}}, Qubits{{0,1,2}}}, {Qubits{{0}}, Qubits{{0,1,2}}}),
							std::tuple<std::vector<Shape>, Shape, Shape>({{Qubits{{0}}, Qubits{{0}}}, {Qubits{}, Qubits{{1,2}}}, {Qubits{{1,2}}, Qubits{{4,3}}}}, {Qubits{{0}}, Qubits{{0,3,4}}}, {Qubits{{0,1,2}}, Qubits{{0,1,2,3,4}}}),
							std::tuple<std::vector<Shape>, Shape, Shape>({{Qubits{{0}}, Qubits{{0}}}, {Qubits{{0,2}}, Qubits{{2}}}}, {Qubits{{0,2}}, Qubits{{2}}},  {Qubits{{0,2}}, Qubits{{0,2}}}),
							std::tuple<std::vector<Shape>, Shape, Shape>({{Qubits{{0}}, Qubits{{0}}}, {Qubits{{0,2}}, Qubits{{2}}}, {Qubits{{4,2}}, Qubits{{1,4}}}}, {Qubits{{0,2,4}}, Qubits{{1,4}}}, {Qubits{{0,2,4}}, Qubits{{0,2,1,4}}}),
              std::tuple<std::vector<Shape>, Shape, Shape>({{Qubits{{0,1,2,3,4}}, Qubits{{0,1,2,3,4,5,6,7,8}}}, {Qubits{{0,1,2,3,4,5,6,7,8}}, Qubits{{0,1,2,3,4}}}}, {Qubits{{0,1,2,3,4}},Qubits{{0,1,2,3,4}}}, {Qubits{{0,1,2,3,4,5,6,7,8}}, Qubits{{0,1,2,3,4,5,6,7,8}}})
                            )
                          );

INSTANTIATE_TEST_CASE_P(SelectValues, ProdResTest,
                        Values(
                        std::tuple<std::vector<Shape>, int>({{Qubits{{0}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0}}}}, 1 << 1),
                        std::tuple<std::vector<Shape>, int>({{Qubits{{0}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0}}}},  1 << 2),
                        std::tuple<std::vector<Shape>, int>({{Qubits{{0}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0}}}}, 1 << 3),
                        std::tuple<std::vector<Shape>, int>({{Qubits{{0,1,2,3,4,5,6,7,8}}, Qubits{{0,1,2,3,4}}}, {Qubits{{0,1,2,3,4}}, Qubits{{0,1,2,3,4,5,6,7,8}}}}, 1 << 5),
                        std::tuple<std::vector<Shape>, int>({{Qubits{{0,1,2,3,4}}, Qubits{{0,1,2,3,4,5,6,7,8}}}, {Qubits{{0,1,2,3,4,5,6,7,8}}, Qubits{{0,1,2,3,4}}}}, 1 << 9)
                        ));

INSTANTIATE_TEST_CASE_P(SelectValues, Op4Test,
                        Values(
							std::tuple<std::vector<Shape>, Shape, Shape>({{Qubits{{0}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0}}}}, {Qubits{{0}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0}}}),
							std::tuple<std::vector<Shape>, Shape, Shape>({{Qubits{{0}}, Qubits{{0}}}, {Qubits{{1}}, Qubits{{1}}}, {Qubits{{2}}, Qubits{{2}}}, {Qubits{{0}}, Qubits{{0}}}}, {Qubits{{0,1,2}}, Qubits{{0,1,2}}}, {Qubits{{0,1,2}}, Qubits{{0,1,2}}}),
							std::tuple<std::vector<Shape>, Shape, Shape>({{Qubits{{0,1,2,3}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0,1,2,3}}}, {Qubits{{0,1,2,3}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0,1,2,3}}}}, {Qubits{{0,1,2,3}}, Qubits{{0,1,2,3}}}, {Qubits{{0,1,2,3}}, Qubits{{0,1,2,3}}}),
							std::tuple<std::vector<Shape>, Shape, Shape>({{Qubits{{0}}, Qubits{{0,1,2,3}}}, {Qubits{{0,1,2,3}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0,1,2,3}}}, {Qubits{{0,1,2,3}}, Qubits{{0}}}}, {Qubits{{0}}, Qubits{{0}}}, {Qubits{{0,1,2,3}}, Qubits{{0,1,2,3}}})
                            )
                          );

INSTANTIATE_TEST_CASE_P(SelectValues, ConjTest,
                        Values(
							std::tuple<Shape, Shape>({Qubits{{0}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0}}}),
							std::tuple<Shape, Shape>({Qubits{{0,1,2}}, Qubits{{0,1,2}}}, {Qubits{{0,1,2}}, Qubits{{0,1,2}}}),
							std::tuple<Shape, Shape>({Qubits{{0}}, Qubits{{1}}}, {Qubits{{1}}, Qubits{{0}}}),
							std::tuple<Shape, Shape>({Qubits{{0,1,2}}, Qubits{{0}}}, {Qubits{{0}}, Qubits{{0,1,2}}}),
							std::tuple<Shape, Shape>({Qubits{{0,1,2}}, Qubits{{0,3,4}}}, {Qubits{{0,3,4}}, Qubits{{0,1,2}}})
                            )
                          );


