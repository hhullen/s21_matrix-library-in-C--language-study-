#include "s21_matrix_oop_test.h"

TEST(test_constructor, default_constructor) {
  S21Matrix test;

  run_through_matrix_num(test, 0.00000001);
}

TEST(test_constructor, pametrized_constructor) {
  S21Matrix test(5, 5);

  run_through_matrix_num(test, 0.00000001);
  EXPECT_EQ(test.get_cols(), 5);
  EXPECT_EQ(test.get_rows(), 5);
}

TEST(test_constructor, copy_constructor) {
  S21Matrix test_init(5, 5);
  fill_matrix(&test_init, 2);

  S21Matrix test(test_init);

  run_through_matrix_num(test, 2);
  EXPECT_EQ(test.get_cols(), 5);
  EXPECT_EQ(test.get_rows(), 5);
}

TEST(test_constructor, move_constructor) {
  S21Matrix test_init(5, 5);
  fill_matrix(&test_init, 2);

  S21Matrix test(std::move(test_init));

  run_through_matrix_num(test, 2);
  EXPECT_EQ(test.get_cols(), 5);
  EXPECT_EQ(test.get_rows(), 5);
}

TEST(test_operations, eq_matrix) {
  S21Matrix test, test2;

  fill_matrix(&test, 2.00000001);
  fill_matrix(&test2, 2);
  EXPECT_TRUE(test.eq_matrix(test2));
}

TEST(test_operations, sum_matrix) {
  S21Matrix test, test2;

  fill_matrix(&test, 2.00000001);
  test.sum_matrix(test);
  fill_matrix(&test2, 4);
  EXPECT_TRUE(test.eq_matrix(test2));
}

TEST(test_operations, sub_matrix) {
  S21Matrix test, test2;

  fill_matrix(&test, 4.00000001);
  fill_matrix(&test2, 2);
  test.sub_matrix(test2);
  EXPECT_TRUE(test.eq_matrix(test2));
}

TEST(test_operations, mul_number) {
  S21Matrix test, test2;

  fill_matrix(&test, 4.00000001);
  fill_matrix(&test2, 16);
  test.mul_number(4);
  EXPECT_TRUE(test.eq_matrix(test2));
}

TEST(test_operations, mul_matrix) {
  S21Matrix test(3, 2), test2(2, 3), result(3, 3);

  test.set_element(0, 0, 1);
  test.set_element(0, 1, 4);
  test.set_element(1, 0, 2);
  test.set_element(1, 1, 5);
  test.set_element(2, 0, 3);
  test.set_element(2, 1, 6);

  test2.set_element(0, 0, 1);
  test2.set_element(0, 1, -1);
  test2.set_element(0, 2, 1);
  test2.set_element(1, 0, 2);
  test2.set_element(1, 1, 3);
  test2.set_element(1, 2, 4);

  result.set_element(0, 0, 9);
  result.set_element(0, 1, 11);
  result.set_element(0, 2, 17);
  result.set_element(1, 0, 12);
  result.set_element(1, 1, 13);
  result.set_element(1, 2, 22);
  result.set_element(2, 0, 15);
  result.set_element(2, 1, 15);
  result.set_element(2, 2, 27);

  test.mul_matrix(test2);
  EXPECT_TRUE(test.eq_matrix(result));
}

TEST(test_operations, transpose) {
  S21Matrix test(3, 2), result(2, 3);

  test.set_element(0, 0, 1);
  test.set_element(0, 1, 4);
  test.set_element(1, 0, 2);
  test.set_element(1, 1, 5);
  test.set_element(2, 0, 3);
  test.set_element(2, 1, 6);

  result.set_element(0, 0, 1);
  result.set_element(0, 1, 2);
  result.set_element(0, 2, 3);
  result.set_element(1, 0, 4);
  result.set_element(1, 1, 5);
  result.set_element(1, 2, 6);

  test = test.transpose();
  EXPECT_TRUE(test.eq_matrix(result));
}

TEST(test_operations, calc_complements) {
  S21Matrix test(3, 3), result(3, 3);

  test.set_element(0, 0, 1);
  test.set_element(0, 1, 2);
  test.set_element(0, 2, 3);
  test.set_element(1, 0, 0);
  test.set_element(1, 1, 4);
  test.set_element(1, 2, 2);
  test.set_element(2, 0, 5);
  test.set_element(2, 1, 2);
  test.set_element(2, 2, 1);

  result.set_element(0, 0, 0);
  result.set_element(0, 1, 10);
  result.set_element(0, 2, -20);
  result.set_element(1, 0, 4);
  result.set_element(1, 1, -14);
  result.set_element(1, 2, 8);
  result.set_element(2, 0, -8);
  result.set_element(2, 1, -2);
  result.set_element(2, 2, 4);

  test = test.calc_complements();
  EXPECT_TRUE(test.eq_matrix(result));
}

TEST(test_operations, determinant) {
  S21Matrix test(3, 3);
  double det = 0.0;

  test.set_element(0, 0, 1);
  test.set_element(0, 1, 2);
  test.set_element(0, 2, 3);
  test.set_element(1, 0, 0);
  test.set_element(1, 1, 4);
  test.set_element(1, 2, 2);
  test.set_element(2, 0, 5);
  test.set_element(2, 1, 2);
  test.set_element(2, 2, 1);

  det = test.determinant();
  EXPECT_TRUE(det - (-40) < ACCURACY);
}

TEST(test_operations, inverse_matrix) {
  S21Matrix test(3, 3), result(3, 3);

  test.set_element(0, 0, 2);
  test.set_element(0, 1, 5);
  test.set_element(0, 2, 7);
  test.set_element(1, 0, 6);
  test.set_element(1, 1, 3);
  test.set_element(1, 2, 4);
  test.set_element(2, 0, 5);
  test.set_element(2, 1, -2);
  test.set_element(2, 2, -3);

  result.set_element(0, 0, 1);
  result.set_element(0, 1, -1);
  result.set_element(0, 2, 1);
  result.set_element(1, 0, -38);
  result.set_element(1, 1, 41);
  result.set_element(1, 2, -34);
  result.set_element(2, 0, 27);
  result.set_element(2, 1, -29);
  result.set_element(2, 2, 24);

  test = test.inverse_matrix();
  EXPECT_TRUE(test.eq_matrix(result));
}

TEST(test_accessors_mutators, set_element__get_element) {
  S21Matrix test(3, 3);

  test.set_element(2, 2, 13.5);
  EXPECT_TRUE(test.get_element(2, 2) - 13.5 < ACCURACY);
}

TEST(test_accessors_mutators, get_rows__get_cols) {
  S21Matrix test(3, 6);

  EXPECT_TRUE(test.get_cols() - 6 < ACCURACY);
  EXPECT_TRUE(test.get_rows() - 3 < ACCURACY);
}

TEST(test_accessors_mutators, set_rows__set_cols) {
  S21Matrix test(3, 3);

  test.set_cols(5);
  test.set_rows(10);

  fill_matrix(&test, 42.1);

  EXPECT_TRUE(test.get_cols() - 5 < ACCURACY);
  EXPECT_TRUE(test.get_rows() - 10 < ACCURACY);

  EXPECT_TRUE(test.get_element(0, 4) - 42.1 < ACCURACY);
  EXPECT_TRUE(test.get_element(9, 4) - 42.1 < ACCURACY);
}

TEST(test_operators, eq_eq) {
  S21Matrix test(3, 3);

  fill_matrix(&test, 9.123);
  EXPECT_TRUE(test == test);
}

TEST(test_operators, plus) {
  S21Matrix test(3, 3), result(3, 3);

  fill_matrix(&test, 7);
  fill_matrix(&result, 14);
  test = test + test;
  EXPECT_TRUE(test == result);
}

TEST(test_operators, minus) {
  S21Matrix test(3, 3), result(3, 3);

  fill_matrix(&test, 14);
  fill_matrix(&result, 7);
  test = test - result;
  EXPECT_TRUE(test == result);
}

TEST(test_operators, multiply) {
  S21Matrix test(3, 2), test2(2, 3), result(3, 3);

  test.set_element(0, 0, 1);
  test.set_element(0, 1, 4);
  test.set_element(1, 0, 2);
  test.set_element(1, 1, 5);
  test.set_element(2, 0, 3);
  test.set_element(2, 1, 6);

  test2.set_element(0, 0, 1);
  test2.set_element(0, 1, -1);
  test2.set_element(0, 2, 1);
  test2.set_element(1, 0, 2);
  test2.set_element(1, 1, 3);
  test2.set_element(1, 2, 4);

  result.set_element(0, 0, 9);
  result.set_element(0, 1, 11);
  result.set_element(0, 2, 17);
  result.set_element(1, 0, 12);
  result.set_element(1, 1, 13);
  result.set_element(1, 2, 22);
  result.set_element(2, 0, 15);
  result.set_element(2, 1, 15);
  result.set_element(2, 2, 27);

  test = test * test2;
  EXPECT_TRUE(test.eq_matrix(result));
}

TEST(test_operators, plus_eq) {
  S21Matrix test(3, 3), result(3, 3);

  fill_matrix(&test, 7);
  fill_matrix(&result, 14);
  test += test;
  EXPECT_TRUE(test == result);
}

TEST(test_operators, minus_eq) {
  S21Matrix test(3, 3), result(3, 3);

  fill_matrix(&test, 14);
  fill_matrix(&result, 7);
  test -= result;
  EXPECT_TRUE(test == result);
}

TEST(test_operators, multiply_eq) {
  S21Matrix test(3, 2), test2(2, 3), result(3, 3);

  test.set_element(0, 0, 1);
  test.set_element(0, 1, 4);
  test.set_element(1, 0, 2);
  test.set_element(1, 1, 5);
  test.set_element(2, 0, 3);
  test.set_element(2, 1, 6);

  test2.set_element(0, 0, 1);
  test2.set_element(0, 1, -1);
  test2.set_element(0, 2, 1);
  test2.set_element(1, 0, 2);
  test2.set_element(1, 1, 3);
  test2.set_element(1, 2, 4);

  result.set_element(0, 0, 9);
  result.set_element(0, 1, 11);
  result.set_element(0, 2, 17);
  result.set_element(1, 0, 12);
  result.set_element(1, 1, 13);
  result.set_element(1, 2, 22);
  result.set_element(2, 0, 15);
  result.set_element(2, 1, 15);
  result.set_element(2, 2, 27);

  test *= test2;
  EXPECT_TRUE(test.eq_matrix(result));
}

TEST(test_operators, indexation) {
  S21Matrix test(4, 4);

  fill_matrix(&test, 39.567);

  EXPECT_TRUE(test(0, 0) - 39.567 < ACCURACY);
  EXPECT_TRUE(test(1, 0) - 39.567 < ACCURACY);
  EXPECT_TRUE(test(0, 2) - 39.567 < ACCURACY);
  EXPECT_TRUE(test(2, 0) - 39.567 < ACCURACY);
  EXPECT_TRUE(test(1, 1) - 39.567 < ACCURACY);
  EXPECT_TRUE(test(2, 2) - 39.567 < ACCURACY);
  EXPECT_TRUE(test(3, 3) - 39.567 < ACCURACY);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void run_through_matrix_num(S21Matrix test, double value) {
  for (int i = 0; i < test.get_rows(); i += 1) {
    for (int j = 0; j < test.get_cols(); j += 1) {
      EXPECT_NEAR(test(i, j), value, ACCURACY);
    }
  }
}

void fill_matrix(S21Matrix* test, double value) {
  for (int i = 0; i < test->get_rows(); i += 1) {
    for (int j = 0; j < test->get_cols(); j += 1) {
      test->set_element(i, j, value);
    }
  }
}
