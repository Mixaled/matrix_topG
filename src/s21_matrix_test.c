#include "s21_matrix.h"

#include <check.h>
#include <stdlib.h>
#define GOOD 1

void set_all_matrix(matrix_t *A, double value) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = value;
    }
  }
}

void set_diagonal_matrix(matrix_t *A, float number) {
  int pos_i = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (pos_i == j) A->matrix[i][j] = number;
    }
    pos_i++;
  }
}
void set_vertical_matrix(matrix_t *A, float number) {
  int cols = A->columns / 2;
  int pos_i = cols;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (pos_i == j) A->matrix[i][j] = number;
    }
  }
}

START_TEST(test_s21_create_matrix) {
  matrix_t result;
  int status = s21_create_matrix(3, 3, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_remove_matrix) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_eq(A.matrix, NULL);
}
END_TEST

START_TEST(test_s21_eq_matrix) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  set_all_matrix(&A, 1);
  set_all_matrix(&B, 1);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);

  set_diagonal_matrix(&A, 2);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_sum_matrix) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  set_all_matrix(&A, 1);
  set_all_matrix(&B, 2);
  s21_sum_matrix(&A, &B, &result);

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], 3.0);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_sub_matrix) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  set_all_matrix(&A, 3);
  set_all_matrix(&B, 1);
  s21_sub_matrix(&A, &B, &result);

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], 2.0);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_number) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  set_all_matrix(&A, 2);
  s21_mult_number(&A, 3, &result);

  // printf("Input matrix A:\n");
  // for (int i = 0; i < A.rows; i++) {
  //     for (int j = 0; j < A.columns; j++) {
  //         printf("%f ", A.matrix[i][j]);
  //     }
  //     printf("\n");
  // }
  //
  // printf("Result matrix:\n");
  // for (int i = 0; i < result.rows; i++) {
  //     for (int j = 0; j < result.columns; j++) {
  //         printf("%f ", result.matrix[i][j]);
  //     }
  //     printf("\n");
  // }

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], 6.0);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_matrix) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  set_all_matrix(&A, 2);
  set_all_matrix(&B, 3);
  s21_mult_matrix(&A, &B, &result);

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], 18.0);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_transpose) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  set_vertical_matrix(&A, 1);
  s21_transpose(&A, &result);

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], A.matrix[j][i]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_calc_complements) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  s21_calc_complements(&A, &result);
  ck_assert_double_eq(result.matrix[0][0], -3);
  ck_assert_double_eq(result.matrix[0][1], 6);
  ck_assert_double_eq(result.matrix[0][2], -3);
  ck_assert_double_eq(result.matrix[1][0], 6);
  ck_assert_double_eq(result.matrix[1][1], -12);
  ck_assert_double_eq(result.matrix[1][2], 6);
  ck_assert_double_eq(result.matrix[2][0], -3);
  ck_assert_double_eq(result.matrix[2][1], 6);
  ck_assert_double_eq(result.matrix[2][2], -3);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 112.0;
  A.matrix[0][1] = 243.0;
  A.matrix[0][2] = 3.0;
  A.matrix[0][3] = -8.0;
  A.matrix[1][0] = 47.0;
  A.matrix[1][1] = 51.0;
  A.matrix[1][2] = -66.0;
  A.matrix[1][3] = 99.0;
  A.matrix[2][0] = -74.0;
  A.matrix[2][1] = 85.0;
  A.matrix[2][2] = 97.0;
  A.matrix[2][3] = 63.0;
  A.matrix[3][0] = -13.0;
  A.matrix[3][1] = 79.0;
  A.matrix[3][2] = -99.0;
  A.matrix[3][3] = -121.0;

  s21_calc_complements(&A, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = -2879514.0;
  X.matrix[0][1] = -1236631.0;
  X.matrix[0][2] = -1685096.0;
  X.matrix[0][3] = 880697.0;
  X.matrix[1][0] = 1162090.0;
  X.matrix[1][1] = -714015.0;
  X.matrix[1][2] = 4046255.0;
  X.matrix[1][3] = -3901600.0;
  X.matrix[2][0] = 4362897.0;
  X.matrix[2][1] = -2049432.0;
  X.matrix[2][2] = -532912.0;
  X.matrix[2][3] = -1370781.0;
  X.matrix[3][0] = 3412773.0;
  X.matrix[3][1] = -1569493.0;
  X.matrix[3][2] = 3144517.0;
  X.matrix[3][3] = 1284666.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, GOOD);
}
END_TEST

START_TEST(s21_calc_complements_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[0][3] = 9.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[2][3] = 21.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 3.0;

  s21_calc_complements(&A, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 0.0;
  X.matrix[0][1] = -30.0;
  X.matrix[0][2] = -108.0;
  X.matrix[0][3] = 106.0;
  X.matrix[1][0] = 138.0;
  X.matrix[1][1] = -726.0;
  X.matrix[1][2] = -1137.0;
  X.matrix[1][3] = 1061.0;
  X.matrix[2][0] = 0.0;
  X.matrix[2][1] = 12.0;
  X.matrix[2][2] = 57.0;
  X.matrix[2][3] = -47.0;
  X.matrix[3][0] = 0.0;
  X.matrix[3][1] = 6.0;
  X.matrix[3][2] = -75.0;
  X.matrix[3][3] = 57.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, GOOD);
}
END_TEST

START_TEST(test_s21_determinant) {
  matrix_t A;
  double result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  s21_determinant(&A, &result);

  ck_assert_double_eq(result, 0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &result);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 6;
  A.matrix[2][2] = 0;

  s21_inverse_matrix(&A, &result);

  ck_assert_double_eq_tol(result.matrix[0][0], -24, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 18, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][2], 5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 20, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], -15, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][2], -4, 1e-6);
  ck_assert_double_eq_tol(result.matrix[2][0], -5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[2][1], 4, 1e-6);
  ck_assert_double_eq_tol(result.matrix[2][2], 1, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *matrix_operations_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Matrix Operations");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_calc_complements_01);
  tcase_add_test(tc_core, s21_calc_complements_02);

  tcase_add_test(tc_core, test_s21_create_matrix);
  tcase_add_test(tc_core, test_s21_remove_matrix);
  tcase_add_test(tc_core, test_s21_eq_matrix);
  tcase_add_test(tc_core, test_s21_sum_matrix);
  tcase_add_test(tc_core, test_s21_sub_matrix);
  tcase_add_test(tc_core, test_s21_mult_number);
  tcase_add_test(tc_core, test_s21_mult_matrix);
  tcase_add_test(tc_core, test_s21_transpose);
  tcase_add_test(tc_core, test_s21_calc_complements);
  tcase_add_test(tc_core, test_s21_determinant);
  tcase_add_test(tc_core, test_s21_inverse_matrix);

  suite_add_tcase(s, tc_core);

  return s;
}
int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = matrix_operations_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}