#include "s21_matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int ret = 0;
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
    }
  } else {
    ret = 1;
  }
  return ret;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->rows = 0;
  A->columns = 0;
  A->matrix = NULL;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (!A->matrix || !B->matrix) {
    return FAILURE;
  }
  int ret = SUCCESS;
  if (A->rows != B->rows || A->columns != B->columns) {
    ret = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) ret = FAILURE;
      }
    }
  }
  return ret;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  s21_create_matrix(A->rows, A->columns, result);
  if (!A->matrix || !B->matrix) {
    return 1;
  }
  if (A->rows != B->rows || A->columns != B->columns) {
    return 2;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }
  return 0;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  s21_create_matrix(A->rows, A->columns, result);
  if (!A->matrix || !B->matrix) {
    return 1;
  }
  if (A->rows != B->rows || A->columns != B->columns) {
    return 2;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return 0;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  s21_create_matrix(A->rows, A->columns, result);
  if (!A->matrix) {
    return 1;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return 0;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  s21_create_matrix(A->rows, B->columns, result);
  if (!A->matrix || !B->matrix) {
    return 1;
  }
  if (A->columns != B->rows) {
    return 2;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return 0;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  s21_create_matrix(A->columns, A->rows, result);
  if (!A->matrix) {
    return 1;
  }
  if (A->rows != result->columns || A->columns != result->rows) {
    return 2;
  }
  for (int i = 0; i < A->columns; i++) {
    for (int j = 0; j < A->rows; j++) {
      result->matrix[i][j] = A->matrix[j][i];
    }
  }
  return 0;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  s21_create_matrix(A->rows, A->columns, result);
  if (!A->matrix) {
    return 1;
  }
  if (A->rows != A->columns || A->rows < 2) {
    return 2;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = s21_minor(A, i, j) * pow(-1, i + j + 2);
    }
  }
  return 0;
}

int s21_minor(matrix_t *mat, int i, int j) {
  double ret = 0;
  matrix_t B;
  s21_create_matrix(mat->rows - 1, mat->columns - 1, &B);
  s21_helper(mat, &B, i, j);
  s21_determinant(&B, &ret);
  s21_remove_matrix(&B);
  return ret;
}

int s21_determinant(matrix_t *A, double *result) {
  *result = 0;
  if (!A->matrix) {
    return 1;
  }
  if (A->rows != A->columns) {
    return 2;
  }
  int n = A->rows;
  if (n == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else if (n == 1) {
    *result = A->matrix[0][0];
  } else {
    matrix_t B;
    s21_create_matrix(A->rows - 1, A->columns - 1, &B);
    double res;
    for (int k = 1; k <= n; k++) {
      s21_helper(A, &B, 0, k - 1);
      s21_determinant(&B, &res);
      *result = *result + pow(-1, k + 1) * A->matrix[0][k - 1] * res;
    }
    s21_remove_matrix(&B);
  }
  return 0;
}

void s21_helper(matrix_t *A, matrix_t *B, int c, int k) {
  int x = 0;
  int y = 0;
  for (int i = 0; i < A->rows - 1; i++) {
    y = 0;
    for (int j = 0; j < A->columns - 1; j++) {
      if (i == c) x = 1;
      if (j == k) y = 1;
      B->matrix[i][j] = A->matrix[i + x][j + y];
    }
  }
}

void s21_equalize(matrix_t *A, matrix_t *B) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      B->matrix[i][j] = A->matrix[i][j];
    }
  }
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  s21_create_matrix(A->rows, A->columns, result);
  if (!A->matrix) {
    return 1;
  }
  if (A->rows != A->columns || A->rows < 2) {
    return 2;
  }
  int ret = 0;
  double det = 0;
  s21_determinant(A, &det);
  if (det == 0) {
    ret = 2;
  } else {
    matrix_t B, C, D;
    s21_calc_complements(A, &B);
    s21_transpose(&B, &C);
    s21_mult_number(&C, 1 / det, &D);
    s21_equalize(&D, result);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
    s21_remove_matrix(&D);
  }
  return ret;
}
