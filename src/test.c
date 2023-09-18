#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_matrix.h"

void initialize_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      srand(time(NULL));
      A->matrix[i][j] = rand();
    }
  }
}

START_TEST(create1) {
  matrix_t mat = {0};
  int x = s21_create_matrix(3, 3, &mat);
  s21_remove_matrix(&mat);
  ck_assert_int_eq(x, 0);
}
END_TEST

START_TEST(create2) {
  matrix_t mat = {0};
  int x = s21_create_matrix(-3, 3, &mat);
  s21_remove_matrix(&mat);
  ck_assert_int_eq(x, 1);
}
END_TEST

START_TEST(create3) {
  matrix_t mat = {0};
  int x = s21_create_matrix(2777777, 3, &mat);
  s21_remove_matrix(&mat);
  ck_assert_int_eq(x, 0);
}
END_TEST

START_TEST(eq1) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  B.matrix[0][0] = 2;
  B.matrix[0][1] = 5;
  B.matrix[0][2] = 7;
  B.matrix[1][0] = 6;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;
  B.matrix[2][0] = 5;
  B.matrix[2][1] = -2;
  B.matrix[2][2] = -3;
  int x = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(x, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq2) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 6;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  B.matrix[0][0] = 2;
  B.matrix[0][1] = 5;
  B.matrix[0][2] = 7;
  B.matrix[1][0] = 6;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;
  B.matrix[2][0] = 5;
  B.matrix[2][1] = -2;
  B.matrix[2][2] = -3;
  int x = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(x, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq3) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = 2;
  B.matrix[0][1] = 5;
  B.matrix[0][2] = 7;
  B.matrix[1][0] = 6;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;
  B.matrix[2][0] = 5;
  B.matrix[2][1] = -2;
  B.matrix[2][2] = -3;
  int x = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(x, 0);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t ans = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &C);
  s21_create_matrix(3, 3, &ans);
  initialize_matrix(&A);
  initialize_matrix(&B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      C.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
    }
  }
  int x = s21_sum_matrix(&A, &B, &ans);
  ck_assert_int_eq(x, 0);
  ck_assert_int_eq(s21_eq_matrix(&C, &ans), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&ans);
}
END_TEST

START_TEST(sum2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t ans = {0};
  s21_create_matrix(3, 4, &B);
  initialize_matrix(&B);
  int x = s21_sum_matrix(&A, &B, &ans);
  ck_assert_int_eq(x, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t ans = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 4, &B);
  s21_create_matrix(3, 3, &ans);
  initialize_matrix(&A);
  initialize_matrix(&B);
  int x = s21_sum_matrix(&A, &B, &ans);
  ck_assert_int_eq(x, 2);
  // ck_assert_int_eq(s21_eq_matrix(&C, &ans), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&ans);
}
END_TEST

START_TEST(sub1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t ans = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &C);
  s21_create_matrix(3, 3, &ans);
  initialize_matrix(&A);
  initialize_matrix(&B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      C.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
    }
  }
  int x = s21_sub_matrix(&A, &B, &ans);
  ck_assert_int_eq(x, 0);
  ck_assert_int_eq(s21_eq_matrix(&C, &ans), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&ans);
}
END_TEST

START_TEST(sub2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t ans = {0};
  s21_create_matrix(3, 4, &B);
  initialize_matrix(&B);
  int x = s21_sub_matrix(&A, &B, &ans);
  ck_assert_int_eq(x, 1);
  // ck_assert_int_eq(s21_eq_matrix(&C, &ans), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t ans = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 4, &B);
  s21_create_matrix(3, 3, &ans);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 6;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  B.matrix[0][0] = 2;
  B.matrix[0][1] = 5;
  B.matrix[0][2] = 7;
  B.matrix[1][0] = 6;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;
  B.matrix[2][0] = 5;
  B.matrix[2][1] = -2;
  B.matrix[2][2] = -3;
  int x = s21_sub_matrix(&A, &B, &ans);
  ck_assert_int_eq(x, 2);
  // ck_assert_int_eq(s21_eq_matrix(&C, &ans), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&ans);
}
END_TEST

START_TEST(mulnum1) {
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t ans;
  s21_create_matrix(3, 3, &A);
  double number = -2;
  s21_create_matrix(3, 3, &C);
  initialize_matrix(&A);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      C.matrix[i][j] = A.matrix[i][j] * number;
    }
  }
  int x = s21_mult_number(&A, number, &ans);
  ck_assert_int_eq(x, 0);
  ck_assert_int_eq(s21_eq_matrix(&C, &ans), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
  s21_remove_matrix(&ans);
}
END_TEST

START_TEST(mulmat1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t ans;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(3, 3, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;
  C.matrix[0][0] = 9;
  C.matrix[0][1] = 11;
  C.matrix[0][2] = 17;
  C.matrix[1][0] = 12;
  C.matrix[1][1] = 13;
  C.matrix[1][2] = 22;
  C.matrix[2][0] = 15;
  C.matrix[2][1] = 15;
  C.matrix[2][2] = 27;
  int x = s21_mult_matrix(&A, &B, &ans);
  ck_assert_int_eq(x, 0);
  ck_assert_int_eq(s21_eq_matrix(&C, &ans), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&ans);
}
END_TEST

START_TEST(trans1) {
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t ans;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  C.matrix[0][0] = 1;
  C.matrix[0][1] = 2;
  C.matrix[0][2] = 3;
  C.matrix[1][0] = 4;
  C.matrix[1][1] = 5;
  C.matrix[1][2] = 6;
  int x = s21_transpose(&A, &ans);
  ck_assert_int_eq(x, 0);
  ck_assert_int_eq(s21_eq_matrix(&C, &ans), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
  s21_remove_matrix(&ans);
}
END_TEST

START_TEST(calc1) {
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t ans = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  C.matrix[0][0] = 0;
  C.matrix[0][1] = 10;
  C.matrix[0][2] = -20;
  C.matrix[1][0] = 4;
  C.matrix[1][1] = -14;
  C.matrix[1][2] = 8;
  C.matrix[2][0] = -8;
  C.matrix[2][1] = -2;
  C.matrix[2][2] = 4;
  int x = s21_calc_complements(&A, &ans);
  ck_assert_int_eq(x, 0);
  ck_assert_int_eq(s21_eq_matrix(&C, &ans), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
  s21_remove_matrix(&ans);
}
END_TEST

START_TEST(det1) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  double number;
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  int x = s21_determinant(&A, &number);
  ck_assert_int_eq(x, 0);
  ck_assert_int_eq(number, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse1) {
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t ans = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  C.matrix[0][0] = 1;
  C.matrix[0][1] = -1;
  C.matrix[0][2] = 1;
  C.matrix[1][0] = -38;
  C.matrix[1][1] = 41;
  C.matrix[1][2] = -34;
  C.matrix[2][0] = 27;
  C.matrix[2][1] = -29;
  C.matrix[2][2] = 24;
  int x = s21_inverse_matrix(&A, &ans);
  // for (int i = 0; i < A.rows; i++) {
  //   for (int j = 0; j < A.columns; j++) {
  //     printf("%lf   ", ans.matrix[i][j]);
  //   }
  //   printf("\n");
  // }
  ck_assert_int_eq(x, 0);
  ck_assert_int_eq(s21_eq_matrix(&C, &ans), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
  s21_remove_matrix(&ans);
}
END_TEST

Suite *suite() {
  Suite *s;
  s = suite_create("Matrix");
  TCase *tc_all;
  tc_all = tcase_create("all tests");
  tcase_add_test(tc_all, create1);
  tcase_add_test(tc_all, create2);
  tcase_add_test(tc_all, create3);
  tcase_add_test(tc_all, eq1);
  tcase_add_test(tc_all, eq2);
  tcase_add_test(tc_all, eq3);
  tcase_add_test(tc_all, sum1);
  tcase_add_test(tc_all, sum2);
  tcase_add_test(tc_all, sum3);
  tcase_add_test(tc_all, sub1);
  tcase_add_test(tc_all, sub2);
  tcase_add_test(tc_all, sub3);
  tcase_add_test(tc_all, mulnum1);
  tcase_add_test(tc_all, mulmat1);
  tcase_add_test(tc_all, trans1);
  tcase_add_test(tc_all, calc1);
  tcase_add_test(tc_all, det1);
  tcase_add_test(tc_all, inverse1);
  suite_add_tcase(s, tc_all);

  return s;
}

int main() {
  int success = 0;
  Suite *s;
  SRunner *runner;
  s = suite();
  runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  success = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (success == 0);
}
