//Write a program in C to find the sum of the left diagonals of a matrix.

#include <stdio.h>

int diagonalSum(int n, int arr[n][n]){
    int sum=0;
    for(int i=0;i<n;i++){
        sum=sum+(arr[i][i]);
    }
    return sum;
}

int main(){
    int size;
    printf("What is the size of the matrix?: ");
    scanf("%d", &size);
    int matrixA[size][size];
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            printf("Enter element [%d][%d]: ", (i+1), (j+1));
            scanf("%d", &matrixA[i][j]);
        }
    }
    int sum=diagonalSum(size, matrixA);
    printf("Sum of diagonal elements is: %d", sum);
    return 0;
}