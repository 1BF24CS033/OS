//Write a program in C to find the sum of rows and columns of a matrix.

#include <stdio.h>

void matrixSums(int r, int c, int arr[r][c]){
    for (int i=0;i<r;i++) {
        int rSum = 0;
        for (int j=0;j<c;j++) {
            rSum += arr[i][j];
        }
        printf("Sum of Row %d: %d\n", i + 1, rSum);
    }
    for (int j=0;j<c;j++) {
        int cSum = 0;
        for (int i=0;i<r;i++) {
            cSum += arr[i][j];
        }
        printf("Sum of Column %d: %d\n", j + 1, cSum);
    }
}

int main(){
    int row, column;
    printf("How many rows in the matrix?: ");
    scanf("%d", &row);
    printf("How many columns in the matrix?: ");
    scanf("%d", &column);
    int matrixA[row][column];
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            printf("Enter element [%d][%d]: ", (i+1), (j+1));
            scanf("%d", &matrixA[i][j]);
        }
    }
    matrixSums(row, column, matrixA);
    return 0;
}