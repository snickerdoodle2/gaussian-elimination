#include "matrix.h"

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
