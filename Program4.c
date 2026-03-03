// Write a program in C to count the total number of duplicate elements in an array.


#include <stdio.h>

int no_of_duplicates(int arr[], int n){
    int c=0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]==arr[j]){
                c++;
                break;
            }
        }
    }
    return c;
}

int main(){
    int n;
    printf("How many elements in the array?: ");
    scanf("%d", &n);
    int arr[n];
    for(int i=0;i<n;i++){
        printf("Enter element %d: ", (i+1));
        scanf("%d", &arr[i]);
    }
    int num = no_of_duplicates(arr, n);
    printf("Number of duplicates in the array is: %d", num);
    return 0;
}