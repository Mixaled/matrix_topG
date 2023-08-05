#include <stdio.h>

#include "s21_matrix.h"
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

int main() {
  matrix_t A, B, C;
  int status;
  // create
  status = s21_create_matrix(3, 3, &A);
  if (status == OK) {
    printf("create_matrix: OK\n");
  } else {
    printf("create_matrix: Failed\n");
  }
  status = s21_create_matrix(0, 0, &B);
  if (status == MATRIX_INCORRECT) {
    printf("create_matrix with incorrect input: OK\n");
  } else {
    printf("create_matrix with incorrect input: Failed\n");
  }
  status = s21_create_matrix(10000, 10000, &C);
  if (status == MATRIX_INCORRECT) {
    printf("big matrix: Failed\n");
  } else {
    printf("big matrix: OK\n");
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  // eq_matrix
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  set_all_matrix(&A, 1);
  set_all_matrix(&B, 1);
  if (s21_eq_matrix(&A, &B) == 1) {
    printf("s21_eq_matrix: OK\n");
  } else {
    printf("s21_eq_matrix: Failed\n");
  }

  set_diagonal_matrix(&A, 2);
  if (s21_eq_matrix(&A, &B) == 0) {
    printf("s21_eq_matrix with non-equal: OK\n");
  } else {
    printf("s21_eq_matrix with non-equal: Failed\n");
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  // Sum and sub
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  // s21_create_matrix(3, 3, &C);

  set_all_matrix(&A, 1);
  set_all_matrix(&B, 2);
  s21_sum_matrix(&A, &B, &C);
  int score = 0;
  for (int i = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      if (C.matrix[i][j] == 3.0) score++;
    }
  }
  if (score == 9)
    printf("sum: OK\n");
  else
    printf("sum: Failed score: %d\n", score);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  // sub
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  set_all_matrix(&A, 3);
  set_all_matrix(&B, 1);
  s21_sub_matrix(&A, &B, &C);
  int score2 = 0;
  for (int i = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      if (C.matrix[i][j] == 2.0) score2++;
    }
  }
  if (score2 == 9)
    printf("sub: OK\n");
  else
    printf("sub: Failed score: %d\n", score);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  return 0;
}
