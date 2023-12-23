#include "matrix.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

double *get_adjusted_row(double **matrix, uint32_t width, uint32_t row,
                         double factor) {
  double *adjusted = malloc((width - row) * sizeof(double));
#pragma omp parallel for
  for (uint32_t i = 0; i < width - row; i++) {
    adjusted[i] = matrix[row][row + i] * factor;
  }
  return adjusted;
}

void subtract_row(double **matrix, uint32_t width, uint32_t row,
                  uint32_t start_pos, double *adjusted) {
#pragma omp parallel for
  for (uint32_t i = 0; i < width - start_pos; i++) {
    matrix[row][start_pos + i] -= adjusted[i];
  }
}

void triangulize(double **matrix, uint32_t height, uint32_t width) {
  for (uint32_t row_1 = 0; row_1 < height; row_1++) {
#pragma omp parallel for
    for (uint32_t row_2 = row_1 + 1; row_2 < height; row_2++) {
      double factor = matrix[row_2][row_1] / matrix[row_1][row_1];
      double *adjusted = get_adjusted_row(matrix, width, row_1, factor);
      subtract_row(matrix, width, row_2, row_1, adjusted);
      free(adjusted);
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

  // free matrix
  for (int i = 0; i < height; i++) {
    free(matrix[i]);
  }
  free(matrix);
}
