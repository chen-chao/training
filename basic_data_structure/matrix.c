#include <stdio.h>
#include <stdlib.h>

int **mat = NULL;

void init(size_t row, size_t col) {
    size_t i, j; 
    mat = (int **)calloc(row, sizeof(int *));

    for (i = 0; i < row; i++) {
        mat[i] = (int *)calloc(col, sizeof(int));
        for (j = 0; j < col; j++) {
            mat[i][j] = i*col + j;
            /* *(*(mat+i)+j) = i*col + j; */
        }
    }
}

void iter_row(size_t row, size_t col) {
    size_t i, j;
    printf("iterating col using index:\n");

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    printf("iterating col using pointer:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", *((*(mat+i))+j));
        }
        printf("\n");
    }
}

void iter_col(size_t row, size_t col) {
    size_t i, j;
    printf("iterating row using index:\n");
    for (j = 0; j < col; j++) {
        for (i = 0; i < row; i++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("iterating row using pointer:\n");
    for (j = 0; j < col; j++) {
        for (i = 0; i < row; i++) {
            printf("%d ", *((*(mat+i))+j));
        }
        printf("\n");
    }
}

void iter_flat(size_t row, size_t col) {
    size_t i, hi = row*col;

    for (i = 0; i < hi; i++) {
        printf("%d ", **(mat+i));
    }
    printf("\n");
}

int main() {
    size_t row = 5, col = 4;
    init(row, col);
    iter_row(row, col);
    iter_col(row, col);
    /* iter_flat(row, col); */
}
