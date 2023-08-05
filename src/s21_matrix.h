#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdbool.h>

#define SUCCESS 1
#define FAILURE 0
#define S21_NAN (0.0 / 0.0L)
#define OK 0
#define ERROR 1
#define CALC_ERROR 2

#define MATRIX_INCORRECT 1
#define CALC_ERR 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Main functions
int s21_create_matrix(int rows, int columns, matrix_t *result);  // done+
void s21_remove_matrix(matrix_t *A);                             // done+

int s21_eq_matrix(matrix_t *A, matrix_t *B);  // done+

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);  // done+
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);  // done+

int s21_mult_number(matrix_t *A, double number, matrix_t *result);  // done+
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);    // done+

int s21_transpose(matrix_t *A, matrix_t *result);         // done+
int s21_calc_complements(matrix_t *A, matrix_t *result);  // done+
int s21_determinant(matrix_t *A, double *result);         // done+
int s21_inverse_matrix(matrix_t *A, matrix_t *result);    // done+

// Other very handy functions
void s21_nullify_matrix(matrix_t *matrix);    // done
bool s21_is_matrix_valid(const matrix_t *A);  // done
// void s21_print_matrix(matrix_t *A, const char *double_format);  // done

#endif  // SRC_S21_MATRIX_H_