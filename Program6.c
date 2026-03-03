// Write a program in C to delete an element at a desired position from an array.

#include <stdio.h>

void deleteFromPos(int arr[], int n, int p){
    for(int i=p-1;i<n-1;i++){
        arr[i]=arr[i+1];
    }
}

int main(){
    int n, pos;
    printf("Enter number of elements in array: ");
    scanf("%d", &n);
    int arr[n];
    for(int i=0;i<n;i++){
        printf("Enter element %d: ", (i+1));
        scanf("%d", &arr[i]);
    }
    printf("What position element do you wish to delete?: ");
    scanf("%d", &pos);
    deleteFromPos(arr, n, pos);
    printf("Array after deletion: ");
    for(int i=0;i<n-1;i++){
        printf("%d ", arr[i]);
    }
    return 0;
}