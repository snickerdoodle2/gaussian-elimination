#include "matrix.h"
#include <omp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG false

double *get_adjusted_row(double **matrix, uint32_t width, uint32_t row,
                         double factor) {
  double *adjusted = malloc((width - row) * sizeof(double));
#pragma omp parallel for
  for (uint32_t i = 0; i < width - row; i++) {
    if (DEBUG) {
      printf("Krok B %d %d (Watek nr %d)\n", row, i, omp_get_thread_num());
    }
    adjusted[i] = matrix[row][row + i] * factor;
  }
  return adjusted;
}

void subtract_row(double **matrix, uint32_t width, uint32_t row,
                  uint32_t start_pos, double *adjusted) {
#pragma omp parallel for
  for (uint32_t i = 0; i < width - start_pos; i++) {
    if (DEBUG) {
      printf("Krok C %d %d (Watek nr %d)\n", row, i, omp_get_thread_num());
    }
    matrix[row][start_pos + i] -= adjusted[i];
  }
}

void triangulize(double **matrix, uint32_t height, uint32_t width) {
  for (uint32_t row_1 = 0; row_1 < height; row_1++) {
#pragma omp parallel for
    for (uint32_t row_2 = row_1 + 1; row_2 < height; row_2++) {
      if (DEBUG) {
        printf("Krok A %d %d (Watek nr %d)\n", row_1, row_2,
               omp_get_thread_num());
      }
      double factor = matrix[row_2][row_1] / matrix[row_1][row_1];
      double *adjusted = get_adjusted_row(matrix, width, row_1, factor);
      subtract_row(matrix, width, row_2, row_1, adjusted);
      free(adjusted);
    }
  }
}

void eliminate(double **matrix, uint32_t height, uint32_t width) {
  for (uint32_t row = 0; row < height; row++) {
    double factor = matrix[row][row];
    for (uint32_t col = 0; col < width; col++) {
      matrix[row][col] /= factor;
    }
  }

  for (int row_1 = height - 1; row_1 >= 0; row_1--) {
    for (int row_2 = row_1 - 1; row_2 >= 0; row_2--) {
      double factor = matrix[row_2][row_1] / matrix[row_1][row_1];
      for (uint32_t col = row_1; col < width; col++) {
        matrix[row_2][col] -= matrix[row_1][col] * factor;
      }
    }
  }
}

int main(void) {
  uint32_t height;
  scanf("%d", &height);
  uint32_t width = height + 1;

  // alloc matrix
  double **matrix = (double **)malloc(height * sizeof(long *));
  if (matrix == NULL)
    return 1;
  for (int i = 0; i < height; i++) {
    matrix[i] = (double *)malloc(width * sizeof(long));
    if (matrix[i] == NULL)
      return 1;
  }

  // load data into matrix
  load_matrix(matrix, width, height);
  printf("\nPostac poczatkowa: \n");
  print_matrix(matrix, width, height);

  triangulize(matrix, height, width);
  printf("\nPostac po eliminacji (wspolbiezne):\n");
  print_matrix(matrix, width, height);

  eliminate(matrix, height, width);
  printf("\nPostac jednostkowa:\n");
  print_matrix(matrix, width, height);

  // free matrix
  for (int i = 0; i < height; i++) {
    free(matrix[i]);
  }
  free(matrix);
}
