// Write a program in C to find the second smallest element in an array.


#include <stdio.h>
#include <limits.h>

void second_smallest(int arr[], int n){
    int second_smallest=INT_MAX;
    int smallest=arr[0];
    for(int i=0;i<n;i++){
        if(arr[i]<smallest){
            second_smallest=smallest;
            smallest=arr[i];
        }
        else if(arr[i] < second_smallest && arr[i]!=smallest){
            second_smallest=arr[i];
        }
    }
    printf("The second smallest element is: %d", second_smallest);
}

int main(){
    int n;
    printf("How many elements?: ");
    scanf("%d", &n);
    int arr1[n];
    for(int i=0;i<n;i++){
        printf("Enter element %d: ", (i+1));
        scanf("%d", &arr1[i]);
    }
    second_smallest(arr1, n);
    return 0;
}