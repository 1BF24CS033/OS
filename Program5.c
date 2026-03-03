// Write a program in C to find the second largest element in an array.

#include <stdio.h>
#include <limits.h>

void second_largest(int arr[], int n){
    int second_largest=INT_MIN;
    int largest=INT_MIN;
    for(int i=0;i<n;i++){
        if(arr[i]>largest){
            second_largest=largest;
            largest=arr[i];
        }
        else if(arr[i]<largest && arr[i]>second_largest){
            second_largest=arr[i];
        }
    }
    if(second_largest==INT_MIN){
        printf("No second largest element available");
        return;
    }
    printf("The second largest element is: %d", second_largest);
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
    second_largest(arr1, n);
    return 0;
}