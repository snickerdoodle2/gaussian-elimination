#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


int main(void) {
    uint32_t height;
    scanf("%d", &height);
    uint32_t width = height + 1;

    // alloc matrix
    double ** matrix = (double **) malloc(height * sizeof(long*));
    if (matrix == NULL) return 1;
    for (int i = 0; i < height; i++) {
        matrix[i] = (double *) malloc(width * sizeof(long));
        if (matrix[i] == NULL) return 1;
    }

    // load data into matrix
    load_matrix(matrix, width, height);


    // free matrix
    for (int i = 0; i < height; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

