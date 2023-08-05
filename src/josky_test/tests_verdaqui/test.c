#include "test.h"

#include <assert.h>
#include <check.h>
#include <math.h>

#include "../s21_matrix.h"

Suite *s21_remove_matrix_suite(void);
Suite *s21_create_matrix_suite(void);
Suite *s21_sumsub_suite(void);
Suite *s21_matrix_mult_suite(void);
Suite *s21_matrix_mult_suite_2(void);
Suite *s21_mult_number_suite(void);
Suite *s21_eq_matrix_suite(void);
Suite *s21_inverse_matrix_suite(void);
Suite *s21_transpose_suite(void);
Suite *s21_calc_complements_suite(void);
Suite *s21_determinant_suite(void);

typedef Suite *(*SuiteFn)();

int main(void) {
  int number_failed = 0;
  const SuiteFn suites[] = {s21_remove_matrix_suite, s21_create_matrix_suite,
                            s21_sumsub_suite,        s21_matrix_mult_suite,
                            s21_matrix_mult_suite_2, s21_mult_number_suite,
                            s21_eq_matrix_suite,     s21_inverse_matrix_suite,
                            s21_transpose_suite,     s21_calc_complements_suite,
                            s21_determinant_suite};
  int suites_len = sizeof(suites) / sizeof(suites[0]);

  SRunner *sr = srunner_create(NULL);

  for (int i = 0; i < suites_len; i++) srunner_add_suite(sr, suites[i]());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}

int s21_compare_doubles(double a, double b) { return fabs(a - b) < 1e-7; }

void s21_fill_matrix_from_local_array(double *local_array, int rows,
                                      int columns, matrix_t *matrix) {
  assert(local_array != NULL);
  assert(rows > 0 && columns > 0);
  assert(s21_create_matrix(rows, columns, matrix) == OK);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix->matrix[i][j] = local_array[i * columns + j];
    }
  }
}

#warning UNCOMMENT THIS WHEN USE YOUR S21_MATRIX.H!!!
/*
void s21_nullify_matrix(matrix_t *matrix) {
  matrix->matrix = NULL;
  matrix->rows = 0;
  matrix->columns = 0;
}

bool s21_is_matrix_valid(const matrix_t *A) {
  return A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0;
}
*/
