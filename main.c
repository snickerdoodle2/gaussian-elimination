#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void load_matrix(double ** matrix, uint32_t width, uint32_t height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < height; x++) {
            scanf("%lf", &matrix[y][x]);
        }
    }

    for (int y = 0; y < height; y++) {
        scanf("%lf", &matrix[y][width - 1]);
    }
}

void print_matrix(double ** matrix, uint32_t width, uint32_t height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%.2lf ", matrix[y][x]);
        }
        printf("\n");
    }
}

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

