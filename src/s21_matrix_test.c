#include "s21_matrix.h"

#include <check.h>

int s21_create_matrix_from_1(int rows, int columns, matrix_t *result) {
  if (!rows || !columns) {
    return 1;
  }

  int flag = _SUCCS;
  result->rows = rows;
  result->columns = columns;

  result->matrix = (double **)calloc(rows, sizeof(double *));
  if (result->matrix == NULL) {
    flag = _ERROR;
    result->rows = result->columns = 0;
  }

  for (int i = 0; i < rows && !flag; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      flag = _ERROR;
      result->rows = result->columns = 0;
    } else {
    }
    for (int j = 0; j < columns; j++) {
      result->matrix[i][j] = columns * i + j + 1.0;
    }
  }

  return flag;
}

void s21_initialization(matrix_t *A) {
  int count = 1;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = count++;
    }
  }
}

// создать матрицу
START_TEST(s21_create_matrix_1) {
  matrix_t A;
  // s21_create_matrix(2147483647, 2147483647, &A);
  s21_create_matrix(1, 2, &A);

  ck_assert_int_eq(1, A.rows);
  ck_assert_int_eq(2, A.columns);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_2) {
  matrix_t A = {0};

  ck_assert_int_eq(1, s21_create_matrix(100, 0, &A));
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_3) {
  matrix_t A = {0};

  ck_assert_int_eq(1, s21_create_matrix(0, 1, &A));
  s21_remove_matrix(&A);
}
END_TEST

// удалить матрицу
START_TEST(s21_remove_matrix_1) {
  matrix_t A = {0};
  s21_create_matrix(1, 2, &A);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_remove_matrix_2) {
  matrix_t A = {0};

  s21_remove_matrix(&A);
}
END_TEST

// сравнить матрицы (равно)
START_TEST(s21_eq_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  ck_assert_int_eq(1, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_2) {
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(1, 0, &A);
  s21_create_matrix(1, 1, &B);
  ck_assert_int_eq(0, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_3) {
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 1;
  s21_create_matrix(1, 1, &B);

  ck_assert_int_eq(0, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// summa
START_TEST(s21_sum_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R;

  s21_create_matrix_from_1(5, 5, &A);
  s21_create_matrix_from_1(5, 5, &R);

  ck_assert_int_eq(1, s21_sum_matrix(&A, &B, &R));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST
START_TEST(s21_sum_matrix_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R;

  s21_create_matrix_from_1(5, 5, &A);
  s21_create_matrix_from_1(2, 5, &B);
  s21_create_matrix_from_1(5, 5, &R);

  ck_assert_int_eq(2, s21_sum_matrix(&A, &B, &R));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST
START_TEST(s21_sum_matrix_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R;

  s21_create_matrix_from_1(5, 5, &A);
  s21_create_matrix_from_1(5, 5, &B);
  // s21_create_matrix_from_1(5, 5, &R);
  s21_sum_matrix(&A, &B, &R);

  for (int i = 0; i < R.rows; i++) {
    for (int j = 0; j < R.columns; j++) {
      ck_assert_double_eq(R.matrix[i][j], (R.columns * i + j + 1.0) * 2.0);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

// delenie
START_TEST(s21_sub_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R;

  s21_create_matrix_from_1(5, 5, &A);
  s21_create_matrix_from_1(5, 5, &R);

  ck_assert_int_eq(1, s21_sub_matrix(&A, &B, &R));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST
START_TEST(s21_sub_matrix_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R;

  s21_create_matrix_from_1(5, 5, &A);
  s21_create_matrix_from_1(2, 5, &B);
  s21_create_matrix_from_1(5, 5, &R);

  ck_assert_int_eq(2, s21_sub_matrix(&A, &B, &R));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST
START_TEST(s21_sub_matrix_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R;

  s21_create_matrix_from_1(5, 5, &A);
  s21_create_matrix_from_1(5, 5, &B);
  s21_sub_matrix(&A, &B, &R);

  for (int i = 0; i < R.rows; i++) {
    for (int j = 0; j < R.columns; j++) {
      ck_assert_double_eq(R.matrix[i][j], (R.columns * i + j + 1.0) * 0);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

// mult num
START_TEST(s21_mult_number_1) {
  matrix_t A = {0};
  matrix_t R;
  double b = 0.0;

  s21_create_matrix_from_1(5, 5, &R);
  ck_assert_int_eq(1, s21_mult_number(&A, b, &R));
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

// mult matrix
START_TEST(s21_mult_matrix_0) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R;

  s21_create_matrix_from_1(3, 3, &A);

  ck_assert_int_eq(1, s21_mult_matrix(&A, &B, &R));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
START_TEST(s21_mult_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R;

  s21_create_matrix_from_1(3, 1, &A);
  s21_create_matrix_from_1(2, 3, &B);
  ck_assert_int_eq(2, s21_mult_matrix(&A, &B, &R));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_mult_matrix_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R;

  s21_create_matrix_from_1(3, 3, &A);
  s21_create_matrix_from_1(3, 3, &B);
  s21_mult_matrix(&A, &B, &R);

  ck_assert_double_eq(30, R.matrix[0][0]);
  ck_assert_double_eq(36, R.matrix[0][1]);
  ck_assert_double_eq(42, R.matrix[0][2]);
  ck_assert_double_eq(66, R.matrix[1][0]);
  ck_assert_double_eq(81, R.matrix[1][1]);
  ck_assert_double_eq(96, R.matrix[1][2]);
  ck_assert_double_eq(102, R.matrix[2][0]);
  ck_assert_double_eq(126, R.matrix[2][1]);
  ck_assert_double_eq(150, R.matrix[2][2]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

// trans
START_TEST(s21_transpose_1) {
  matrix_t A = {0};
  matrix_t R;

  s21_transpose(&A, &R);
  ck_assert_int_eq(1, s21_transpose(&A, &R));
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_transpose_2) {
  matrix_t A = {0};
  matrix_t R;

  s21_create_matrix_from_1(3, 3, &A);
  s21_transpose(&A, &R);
  ck_assert_double_eq(1, R.matrix[0][0]);
  ck_assert_double_eq(4, R.matrix[0][1]);
  ck_assert_double_eq(7, R.matrix[0][2]);
  ck_assert_double_eq(2, R.matrix[1][0]);
  ck_assert_double_eq(5, R.matrix[1][1]);
  ck_assert_double_eq(8, R.matrix[1][2]);
  ck_assert_double_eq(3, R.matrix[2][0]);
  ck_assert_double_eq(6, R.matrix[2][1]);
  ck_assert_double_eq(9, R.matrix[2][2]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST
START_TEST(s21_transpose_3) {
  matrix_t A = {0};
  matrix_t R;

  s21_create_matrix_from_1(1, 3, &A);
  s21_transpose(&A, &R);

  ck_assert_double_eq(1, R.matrix[0][0]);
  ck_assert_double_eq(2, R.matrix[1][0]);
  ck_assert_double_eq(3, R.matrix[2][0]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

// calc
START_TEST(s21_calc_complements_1) {
  matrix_t A = {0};
  matrix_t R;

  ck_assert_int_eq(1, s21_calc_complements(&A, &R));
  s21_remove_matrix(&A);
}
END_TEST
START_TEST(s21_calc_complements_2) {
  matrix_t A = {0};
  matrix_t R;

  s21_create_matrix_from_1(4, 3, &A);
  ck_assert_int_eq(2, s21_calc_complements(&A, &R));
  s21_remove_matrix(&A);
}
END_TEST
START_TEST(s21_calc_complements_3) {
  matrix_t A = {0};
  matrix_t R = {0};

  s21_create_matrix_from_1(3, 3, &A);
  s21_calc_complements(&A, &R);
  ck_assert_double_eq(-3, R.matrix[0][0]);
  ck_assert_double_eq(6, R.matrix[0][1]);
  ck_assert_double_eq(-3, R.matrix[0][2]);
  ck_assert_double_eq(6, R.matrix[1][0]);
  ck_assert_double_eq(-12, R.matrix[1][1]);
  ck_assert_double_eq(6, R.matrix[1][2]);
  ck_assert_double_eq(-3, R.matrix[2][0]);
  ck_assert_double_eq(6, R.matrix[2][1]);
  ck_assert_double_eq(-3, R.matrix[2][2]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

// determinant
START_TEST(s21_determinant_1) {
  matrix_t A = {0};
  double d = 0.0;

  ck_assert_int_eq(1, s21_determinant(&A, &d));
  s21_remove_matrix(&A);
}
END_TEST
START_TEST(s21_determinant_2) {
  matrix_t A = {0};
  double d = 0.0;

  s21_create_matrix_from_1(3, 1, &A);
  ck_assert_int_eq(2, s21_determinant(&A, &d));
  s21_remove_matrix(&A);
}
END_TEST
START_TEST(s21_determinant_3) {
  matrix_t A;
  double d = 0.0;

  s21_create_matrix_from_1(5, 5, &A);
  s21_determinant(&A, &d);
  ck_assert_double_eq(d, (0.0));
  s21_remove_matrix(&A);
}
END_TEST
START_TEST(s21_determinant_4) {
  matrix_t A = {0};
  double d = 0.0;

  s21_create_matrix_from_1(1, 1, &A);
  s21_determinant(&A, &d);
  ck_assert_double_eq(d, 1.0);
  s21_remove_matrix(&A);
}
END_TEST

// inverse
START_TEST(s21_inverse_matrix_1) {
  matrix_t A = {0};
  matrix_t R;

  ck_assert_int_eq(1, s21_inverse_matrix(&A, &R));
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_2) {
  matrix_t A = {0};
  matrix_t R;

  s21_create_matrix_from_1(3, 1, &A);
  ck_assert_int_eq(2, s21_inverse_matrix(&A, &R));
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(s21_inverse_matrix_3) {
  matrix_t A = {0};
  matrix_t R;
  s21_create_matrix_from_1(1, 1, &A);

  s21_inverse_matrix(&A, &R);
  ck_assert_double_eq(R.matrix[0][0], 1.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(s21_create_matrix_test_1) {
  matrix_t A1 = {0};
  int rez1 = s21_create_matrix(0, 0, &A1);
  ck_assert_int_eq(rez1, 1);
  s21_remove_matrix(&A1);
}
END_TEST

START_TEST(s21_create_matrix_test_2) {
  matrix_t A2 = {0};
  int rez2 = s21_create_matrix(2, 0, &A2);
  ck_assert_int_eq(rez2, 1);
  s21_remove_matrix(&A2);
}
END_TEST

START_TEST(s21_create_matrix_test_3) {
  matrix_t A3 = {0};
  int rez3 = s21_create_matrix(0, 2, &A3);
  ck_assert_int_eq(rez3, 1);
  s21_remove_matrix(&A3);
}
END_TEST

START_TEST(s21_create_matrix_test_4) {
  matrix_t A4 = {0};
  int rez4 = s21_create_matrix(2, 2, &A4);
  ck_assert_int_eq(rez4, 0);
  s21_remove_matrix(&A4);
}
END_TEST

START_TEST(s21_create_matrix_test_5) {
  matrix_t A5 = {0};
  int rez5 = s21_create_matrix(-2, -2, &A5);
  ck_assert_int_eq(rez5, 1);
  s21_remove_matrix(&A5);
}
END_TEST

START_TEST(s21_sum_matrix_test) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_initialization(&A);
  s21_initialization(&B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &C), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sum_matrix_test_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(-1, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_initialization(&A);
  s21_initialization(&B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &C), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  // s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sum_matrix_test_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(1, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_initialization(&A);
  s21_initialization(&B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &C), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  // s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sum_matrix_test_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &D);
  s21_initialization(&A);
  s21_initialization(&B);
  s21_sum_matrix(&A, &B, &C);
  D.matrix[0][0] = 2;
  D.matrix[1][0] = 8;
  D.matrix[2][0] = 14;
  ck_assert_int_eq(D.matrix[0][0], C.matrix[0][0]);
  ck_assert_int_eq(D.matrix[1][0], C.matrix[1][0]);
  ck_assert_int_eq(D.matrix[2][0], C.matrix[2][0]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&D);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sub_matrix_test) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_initialization(&A);
  s21_initialization(&B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &C), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sub_matrix_test_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(-1, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_initialization(&A);
  s21_initialization(&B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &C), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sub_matrix_test_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(1, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_initialization(&A);
  s21_initialization(&B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &C), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sub_matrix_test_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &D);
  s21_initialization(&A);
  s21_initialization(&B);
  s21_sub_matrix(&A, &B, &C);
  D.matrix[0][0] = 0;
  D.matrix[1][0] = 0;
  D.matrix[2][0] = 0;
  ck_assert_int_eq(D.matrix[0][0], C.matrix[0][0]);
  ck_assert_int_eq(D.matrix[1][0], C.matrix[1][0]);
  ck_assert_int_eq(D.matrix[2][0], C.matrix[2][0]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&D);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_number_test) {
  matrix_t A = {0};
  matrix_t C = {0};
  double B = -0.1151118;
  s21_create_matrix(-1, 3, &A);
  ck_assert_int_eq(s21_mult_number(&A, B, &C), 1);
}
END_TEST

START_TEST(s21_mult_number_test_2) {
  matrix_t A = {0};
  matrix_t C = {0};
  double B = -0.1151118;
  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(s21_mult_number(&A, B, &C), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_number_test_3) {
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t D = {0};
  double B = -1;
  s21_create_matrix(3, 3, &D);
  D.matrix[0][0] = -1;
  D.matrix[1][0] = -4;
  D.matrix[2][0] = -7;
  s21_create_matrix(3, 3, &A);
  s21_initialization(&A);
  s21_mult_number(&A, B, &C);
  ck_assert_int_eq(D.matrix[0][0], C.matrix[0][0]);
  ck_assert_int_eq(D.matrix[1][0], C.matrix[1][0]);
  ck_assert_int_eq(D.matrix[2][0], C.matrix[2][0]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(s21_mult_matrix_test) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_initialization(&A);
  s21_initialization(&B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_matrix_test_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(12, 32, &A);
  s21_create_matrix(32, 45, &B);
  s21_initialization(&A);
  s21_initialization(&B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_matrix_test_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(12, 32, &A);
  s21_create_matrix(3, 45, &B);
  s21_initialization(&A);
  s21_initialization(&B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_matrix_test_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(-1, 32, &A);
  s21_create_matrix(3, 45, &B);
  s21_initialization(&A);
  s21_initialization(&B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_matrix_test_5) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &D);
  s21_initialization(&A);
  s21_initialization(&B);
  D.matrix[0][0] = 30;
  D.matrix[1][0] = 66;
  D.matrix[2][0] = 102;
  s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(D.matrix[0][0], C.matrix[0][0]);
  ck_assert_int_eq(D.matrix[1][0], C.matrix[1][0]);
  ck_assert_int_eq(D.matrix[2][0], C.matrix[2][0]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&D);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_transpose_test) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(5, 3, &A);
  s21_initialization(&A);
  ck_assert_int_eq(s21_transpose(&A, &B), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_transpose_test_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(-5, 3, &A);
  s21_initialization(&A);
  ck_assert_int_eq(s21_transpose(&A, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_transpose_test_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &C);
  s21_initialization(&A);
  C.matrix[0][0] = 1;
  C.matrix[0][1] = 3;
  C.matrix[0][2] = 5;
  C.matrix[1][0] = 2;
  C.matrix[1][1] = 4;
  C.matrix[1][2] = 6;
  s21_transpose(&A, &B);
  ck_assert_int_eq(C.matrix[0][0], B.matrix[0][0]);
  ck_assert_int_eq(C.matrix[0][1], B.matrix[0][1]);
  ck_assert_int_eq(C.matrix[0][2], B.matrix[0][2]);
  ck_assert_int_eq(C.matrix[1][0], B.matrix[1][0]);
  ck_assert_int_eq(C.matrix[1][1], B.matrix[1][1]);
  ck_assert_int_eq(C.matrix[1][2], B.matrix[1][2]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_calc_complements_test) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(5, 5, &A);
  s21_initialization(&A);
  ck_assert_int_eq(s21_calc_complements(&A, &B), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
START_TEST(s21_calc_complements_test_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(-1, 5, &A);
  s21_initialization(&A);
  ck_assert_int_eq(s21_calc_complements(&A, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_calc_complements_test_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(5, 3, &A);
  s21_initialization(&A);
  ck_assert_int_eq(s21_calc_complements(&A, &B), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_calc_complements_test_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(1, 1, &A);
  s21_initialization(&A);
  ck_assert_int_eq(s21_calc_complements(&A, &B), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(s21_calc_complements_test_5) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
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

  C.matrix[0][0] = -1;
  C.matrix[0][1] = 38;
  C.matrix[0][2] = -27;
  C.matrix[1][0] = 1;
  C.matrix[1][1] = -41;
  C.matrix[1][2] = 29;
  C.matrix[2][0] = -1;
  C.matrix[2][1] = 34;
  C.matrix[2][2] = -24;
  s21_calc_complements(&A, &B);
  ck_assert_int_eq(C.matrix[0][0], B.matrix[0][0]);
  ck_assert_int_eq(C.matrix[0][1], B.matrix[0][1]);
  ck_assert_int_eq(C.matrix[0][2], B.matrix[0][2]);
  ck_assert_int_eq(C.matrix[1][0], B.matrix[1][0]);
  ck_assert_int_eq(C.matrix[1][1], B.matrix[1][1]);
  ck_assert_int_eq(C.matrix[1][2], B.matrix[1][2]);
  ck_assert_int_eq(C.matrix[2][0], B.matrix[2][0]);
  ck_assert_int_eq(C.matrix[2][1], B.matrix[2][1]);
  ck_assert_int_eq(C.matrix[2][2], B.matrix[2][2]);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}

START_TEST(s21_determinant_test) {
  matrix_t A = {0};
  double B = 0;
  s21_create_matrix(-1, 3, &A);
  s21_initialization(&A);
  ck_assert_int_eq(s21_determinant(&A, &B), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_2) {
  matrix_t A = {0};
  double B = 0;
  s21_create_matrix(2, 3, &A);
  s21_initialization(&A);
  ck_assert_int_eq(s21_determinant(&A, &B), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_3) {
  matrix_t A = {0};
  double B = 0;
  s21_create_matrix(3, 3, &A);
  s21_initialization(&A);
  ck_assert_int_eq(s21_determinant(&A, &B), 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_4) {
  matrix_t A = {0};
  double B = 0;
  s21_create_matrix(4, 4, &A);
  s21_initialization(&A);
  s21_determinant(&A, &B);
  ck_assert_int_eq(B, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_test) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(-1, 3, &A);
  s21_initialization(&A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_inverse_matrix_test_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_initialization(&A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &B), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *s21_matrix_suite(void) {
  Suite *suite;

  suite = suite_create("s21_matrix");
  TCase *tcase_core = tcase_create("Core");

  // создать матрицу
  tcase_add_test(tcase_core, s21_create_matrix_1);
  tcase_add_test(tcase_core, s21_create_matrix_2);
  tcase_add_test(tcase_core, s21_create_matrix_3);
  // удалить матрицу
  tcase_add_test(tcase_core, s21_remove_matrix_1);
  tcase_add_test(tcase_core, s21_remove_matrix_2);
  // сравнить матрицы (равно)
  tcase_add_test(tcase_core, s21_eq_matrix_1);
  tcase_add_test(tcase_core, s21_eq_matrix_2);
  tcase_add_test(tcase_core, s21_eq_matrix_3);
  // summa
  tcase_add_test(tcase_core, s21_sum_matrix_1);
  tcase_add_test(tcase_core, s21_sum_matrix_2);
  tcase_add_test(tcase_core, s21_sum_matrix_3);
  // delenie
  tcase_add_test(tcase_core, s21_sub_matrix_1);
  tcase_add_test(tcase_core, s21_sub_matrix_2);
  tcase_add_test(tcase_core, s21_sub_matrix_3);
  // mult num
  tcase_add_test(tcase_core, s21_mult_number_1);
  tcase_add_test(tcase_core, s21_mult_number_test_2);
  tcase_add_test(tcase_core, s21_mult_number_test_3);
  // mult matrix
  tcase_add_test(tcase_core, s21_mult_matrix_0);
  tcase_add_test(tcase_core, s21_mult_matrix_1);
  tcase_add_test(tcase_core, s21_mult_matrix_2);
  // trans
  tcase_add_test(tcase_core, s21_transpose_1);
  tcase_add_test(tcase_core, s21_transpose_2);
  tcase_add_test(tcase_core, s21_transpose_3);
  // calc
  tcase_add_test(tcase_core, s21_calc_complements_1);
  tcase_add_test(tcase_core, s21_calc_complements_2);
  tcase_add_test(tcase_core, s21_calc_complements_3);
  // det
  tcase_add_test(tcase_core, s21_determinant_1);
  tcase_add_test(tcase_core, s21_determinant_2);
  tcase_add_test(tcase_core, s21_determinant_3);
  tcase_add_test(tcase_core, s21_determinant_4);
  // inverse
  tcase_add_test(tcase_core, s21_inverse_matrix_1);
  tcase_add_test(tcase_core, s21_inverse_matrix_2);
  tcase_add_test(tcase_core, s21_inverse_matrix_3);

  tcase_add_test(tcase_core, s21_create_matrix_test_1);
  tcase_add_test(tcase_core, s21_create_matrix_test_2);
  tcase_add_test(tcase_core, s21_create_matrix_test_3);
  tcase_add_test(tcase_core, s21_create_matrix_test_4);
  tcase_add_test(tcase_core, s21_create_matrix_test_5);
  tcase_add_test(tcase_core, s21_eq_matrix_1);
  tcase_add_test(tcase_core, s21_eq_matrix_2);
  tcase_add_test(tcase_core, s21_sum_matrix_test);
  tcase_add_test(tcase_core, s21_sum_matrix_test_2);
  tcase_add_test(tcase_core, s21_sum_matrix_test_3);
  tcase_add_test(tcase_core, s21_sum_matrix_test_4);
  tcase_add_test(tcase_core, s21_sub_matrix_test);
  tcase_add_test(tcase_core, s21_sub_matrix_test_2);
  tcase_add_test(tcase_core, s21_sub_matrix_test_3);
  tcase_add_test(tcase_core, s21_sub_matrix_test_4);
  tcase_add_test(tcase_core, s21_mult_number_test);
  tcase_add_test(tcase_core, s21_mult_matrix_test);
  tcase_add_test(tcase_core, s21_mult_matrix_test_2);
  tcase_add_test(tcase_core, s21_mult_matrix_test_3);
  tcase_add_test(tcase_core, s21_mult_matrix_test_4);
  tcase_add_test(tcase_core, s21_mult_matrix_test_5);
  tcase_add_test(tcase_core, s21_transpose_test);
  tcase_add_test(tcase_core, s21_transpose_test_2);
  tcase_add_test(tcase_core, s21_transpose_test_3);
  tcase_add_test(tcase_core, s21_calc_complements_test);
  tcase_add_test(tcase_core, s21_calc_complements_test_2);
  tcase_add_test(tcase_core, s21_calc_complements_test_3);
  tcase_add_test(tcase_core, s21_calc_complements_test_4);
  tcase_add_test(tcase_core, s21_calc_complements_test_5);
  tcase_add_test(tcase_core, s21_determinant_test);
  tcase_add_test(tcase_core, s21_determinant_test_2);
  tcase_add_test(tcase_core, s21_determinant_test_3);
  tcase_add_test(tcase_core, s21_determinant_test_4);
  tcase_add_test(tcase_core, s21_inverse_matrix_test);
  tcase_add_test(tcase_core, s21_inverse_matrix_test_2);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  Suite *suite = s21_matrix_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  if (failed_count == 0) {
    printf("\033[32mAll tests passed!\033[0m\n");
    return EXIT_SUCCESS;
  } else {
    printf("\033[31mSome tests failed!\033[0m\n");
    return EXIT_FAILURE;
  }
}
