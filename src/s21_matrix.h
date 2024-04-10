#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 0 - OK
#define _SUCCS 0
// 1 - Ошибка, некорректная матрица
#define _UNCOR 1
// 2 - Ошибка вычисления (несовпадающие размеры матриц;
// матрица, для которой нельзя провести вычисления и т.д.)
#define _ERROR 2

// custom matrix type
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Создание матриц
int s21_create_matrix(int rows, int columns, matrix_t *result);

// Очистка матриц
void s21_remove_matrix(matrix_t *A);

// Сравнение матриц
// SUCCESS 1
// FAILURE 0
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Сложение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Вычитание матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

//  Умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

// Умножение матрицы на матрицу
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/* Транспонирование матрицы (замена строк столбцами с сохранением номеров)
1 4 --> 1 2 3
2 5 --> 4 5 6
3 6 -->
*/
int s21_transpose(matrix_t *A, matrix_t *result);

// Минор матрицы и матрица алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result);

// Определитель матрицы (может быть только для квадратной матрицы)
int s21_determinant(matrix_t *A, double *result);

// Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result);