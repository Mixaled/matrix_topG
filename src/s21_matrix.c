#include "s21_matrix.h"

#include <math.h>
#include <stdlib.h>

#define S21_EPS 1e-7
//(double *) malloc(columns * sizeof(double))

void s21_nullify_matrix(matrix_t *matrix) { *matrix = (matrix_t){NULL, 0, 0}; }
bool s21_is_matrix_valid(const matrix_t *A) {
  return A->matrix != NULL && A->rows > 0 && A->columns > 0;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = OK;
  if (result == NULL) {
    status = MATRIX_INCORRECT;
  } else if (rows <= 0 || columns <= 0) {
    result->matrix = NULL;
    result->rows = 0;
    result->columns = 0;
    status = MATRIX_INCORRECT;
  } else {
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      status = MATRIX_INCORRECT;
    } else {
      result->rows = rows;
      result->columns = columns;

      for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          s21_remove_matrix(result);
          status = MATRIX_INCORRECT;
          break;
        }
      }
    }
  }
  return status;
}


void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->rows > 0 && A->columns > 0) {
      for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
      free(A->matrix);
    }
    A->columns = 0;
    A->rows = 0;
    A->matrix = NULL;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = 1;
  if (A == NULL || B == NULL || A->rows <= 0 || A->columns <= 0 ||
      B->rows <= 0 || B->columns <= 0) {
    result = 0;
  } else if (A->columns != B->columns || A->rows != B->rows) {
    result = 0;
  } else {
    for (int i = 0; i < A->rows && result; i++) {
      for (int j = 0; j < A->columns && result; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > S21_EPS) {
          result = 0;
        }
      }
    }
  }
  return result;
}
int full_check(matrix_t *A, matrix_t *B) {
  //, matrix_t *result
  if (!s21_is_matrix_valid(A) || !s21_is_matrix_valid(B))
    return MATRIX_INCORRECT;

  if (A->rows != B->rows || A->columns != B->columns) return CALC_ERR;

  // if (s21_create_matrix(A->rows, A->columns, result) != OK ||
  //     s21_create_matrix(B->rows, B->columns, result) != OK)
  // return MATRIX_INCORRECT;
  return OK;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = full_check(A, B);
  int res2 = s21_create_matrix(A->rows, B->columns, result);
  if (res == OK && res2 == OK)
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
  else
    s21_remove_matrix(result);
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = full_check(A, B);
  int res2 = s21_create_matrix(A->rows, B->columns, result);
  if (res == OK && res2 == OK)
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
  else
    s21_remove_matrix(result);
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0)
    return MATRIX_INCORRECT;
  int res = s21_create_matrix(A->rows, A->columns, result);
  if (res != OK) return res;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (A == NULL || B == NULL || result == NULL)
    return MATRIX_INCORRECT;
  else if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0)
    return MATRIX_INCORRECT;
  else if (A->columns != B->rows) {
    return CALC_ERR;
  } else {
    res = s21_create_matrix(A->rows, B->columns, result);
    if (res == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          double join = 0;
          for (int k = 0; k < B->rows; k++) {
            join += A->matrix[i][k] * B->matrix[k][j];
          }
          result->matrix[i][j] = join;
        }
      }
    } else {
      return CALC_ERR;
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (A == NULL || A->rows <= 0 || A->columns <= 0 || result == NULL)
    res = MATRIX_INCORRECT;
  else if ((res = s21_create_matrix(A->columns, A->rows, result)) != OK) {
    res = CALC_ERR;
  } else {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[j][i] = A->matrix[i][j];
  }
  return res;
}
void byte_matrix(matrix_t *A, int row, int col, matrix_t *result) {
  int rows = A->rows - 1;
  int cols = A->columns - 1;
  s21_create_matrix(rows, cols, result);
  for (int i = 0, m = 0; i < A->rows; i++) {
    if (i == row) {
      continue;
    } else {
      for (int j = 0, n = 0; j < A->columns; j++) {
        if (j == col) {
          continue;
        } else {
          result->matrix[m][n] = A->matrix[i][j];
          n++;
        }
      }
      m++;
    }
  }
}

int s21_determinant(matrix_t *A, double *result) {
  (*result) = 0.0;
  int res = OK;
  if (A == NULL || A->rows <= 0 || A->columns <= 0) {
    res = MATRIX_INCORRECT;
  } else if (A->rows == A->columns) {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->columns == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
    } else {
      int row = 69;
      row = A->rows;
      matrix_t temp;
      int minus = 1;
      double det = 69;
      for (int i = 0; i < row; i++) {
        det = 0;
        byte_matrix(A, 0, i, &temp);
        s21_determinant(&temp, &det);
        s21_remove_matrix(&temp);
        *result += A->matrix[0][i] * det * minus;
        minus = -minus;
      }
    }
  } else {
    res = CALC_ERR;
  }
  if (res != OK) {
    *result = NAN;
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A == NULL || A->rows <= 0 || A->columns <= 0) {
    return MATRIX_INCORRECT;
  }

  if (A->rows != A->columns) {
    return CALC_ERR;
  }

  int res = s21_create_matrix(A->rows, A->columns, result);
  if (res != OK) {
    return res;
  }
  if (A->rows == 1) {
    result->matrix[0][0] = 1;  // pow(A->matrix[0][0], 2);
    return OK;
  }

  matrix_t temp;
  double minor, minus;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      byte_matrix(A, i, j, &temp);
      int res = s21_determinant(&temp, &minor);
      if (res != 0) {
        return CALC_ERR;
      }
      minus = ((i + j) % 2) ? -1 : 1;
      result->matrix[i][j] = minor * minus;
      s21_remove_matrix(&temp);
    }
  }

  return OK;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || A->rows <= 0 || A->columns <= 0) {
    return MATRIX_INCORRECT;
  }

  if (A->rows != A->columns) {
    return CALC_ERR;
  }

  double det = 0;
  s21_determinant(A, &det);

  if (det == 0) {
    return CALC_ERR;
  }

  matrix_t temp;
  s21_calc_complements(A, result);
  s21_transpose(result, &temp);
  s21_remove_matrix(result);
  s21_mult_number(&temp, (1 / det), result);
  s21_remove_matrix(&temp);

  return OK;
}

// int main() {
//   double a_0[] = {1, 2, 3};
//   double a_1[] = {4, 5, 6};
//   double a_2[] = {7, 8, 9};
//   double *a_[] = {&a_0[0], &a_1[0], &a_2[0]};
//   matrix_t a = {.rows = 3, .columns = 3, .matrix = &a_[0]};
//   double result;
//   s21_determinant(&a, &result);
//   double best = 0.0;
//
//   double b_0[] = {2, 5, 7};
//   double b_1[] = {6, 3, 4};
//   double b_2[] = {5, -2, -3};
//   double *b_[] = {&b_0[0], &b_1[0], &b_2[0]};
//   matrix_t b = {.rows = 3, .columns = 3, .matrix = &b_[0]};
//   s21_determinant(&b, &result);
//   best = -1.0;
//
//   double c_0[] = {2, 5, 7, 8};
//   double c_1[] = {6, 3, -4, 5};
//   double c_2[] = {5, -2, -3, 2};
//   double c_3[] = {5, -2, -3, -4};
//   double *c_[] = {&c_0[0], &c_1[0], &c_2[0], &c_3[0]};
//   matrix_t c = {.rows = 4, .columns = 4, .matrix = &c_[0]};
//   s21_determinant(&c, &result);
//   best = 1398;
//   return 0;
// }