#include <stdio.h>
#include <stdlib.h>

void fcfs(int at[], int bt[], int p[], int n){
    float tatSum=0, wtSum=0;
    int ct[n];
    int tat[n];
    int wt[n];
    for(int i=0;i<n-1;i++){
        for(int j=1;j<n-i-1;j++){
            if(at[i]>at[j]){
                int temp=at[i];
                at[i]=at[j];
                at[j]=temp;

                temp=p[i];
                p[i]=p[j];
                p[j]=temp;

                temp=bt[i];
                bt[i]=bt[j];
                bt[j]=temp;
            }
        }
    }

    ct[0]=at[0]+bt[0];
    for(int i=0;i<n;i++){
        if(ct[i-1]<at[i])
            ct[i]=at[i]+bt[i];
        else
            ct[i]=ct[i-1]+bt[i];
    }

    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        tatSum=tatSum+tat[i];
        wtSum=wtSum+wt[i];
    }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("Average Turn Around Time is: %.2f\n", (tatSum/n));
    printf("Average Waiting Time is: %.2f\n", (wtSum/n));
}

int main(){
    int p[]={1, 2, 3, 4, 5};
    int at[]={0, 0, 0, 0, 0};
    int bt[]={3, 4, 1, 5, 6};
    int n=sizeof(p)/sizeof(p[0]);
    fcfs(at, bt, p, n);
    return 0;
}