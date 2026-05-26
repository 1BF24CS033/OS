#include <stdio.h>

void printResult(int process[],int n,int allocation[]){
    printf("\n%-10s %-15s %-15s\n","Process","Process Size","Block No.");
    for(int i=0;i<n;i++){
        printf("P%-9d %-15d",i+1,process[i]);
        if(allocation[i]!=-1)
            printf("%-15d\n",allocation[i]+1);
        else
            printf("%-15s\n","Not Allocated");
    }
}

void firstFit(int block[],int m,int process[],int n){
    int allocation[20],used[20];
    for(int i=0;i<n;i++) allocation[i]=-1;
    for(int i=0;i<m;i++) used[i]=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!used[j] && block[j]>=process[i]){
                allocation[i]=j;
                used[j]=1;
                break;
            }
        }
    }
    printf("\n\n \t\t FIRST FIT \n");
    printResult(process,n,allocation);
}

void bestFit(int block[],int m,int process[],int n){
    int allocation[20],used[20];
    for(int i=0;i<n;i++) allocation[i]=-1;
    for(int i=0;i<m;i++) used[i]=0;
    for(int i=0;i<n;i++){
        int best=-1;
        for(int j=0;j<m;j++){
            if(!used[j] && block[j]>=process[i]){
                if(best==-1 || block[j]<block[best])
                    best=j;
            }
        }
        if(best!=-1){
            allocation[i]=best;
            used[best]=1;
        }
    }
    printf("\n\n \t\t BEST FIT \n");
    printResult(process,n,allocation);
}

void worstFit(int block[],int m,int process[],int n){
    int allocation[20],used[20];
    for(int i=0;i<n;i++) allocation[i]=-1;
    for(int i=0;i<m;i++) used[i]=0;
    for(int i=0;i<n;i++){
        int worst=-1;
        for(int j=0;j<m;j++){
            if(!used[j] && block[j]>=process[i]){
                if(worst==-1 || block[j]>block[worst])
                    worst=j;
            }
        }
        if(worst!=-1){
            allocation[i]=worst;
            used[worst]=1;
        }
    }
    printf("\n\n \t\t WORST FIT \n");
    printResult(process,n,allocation);
}

int main(){
    int block[20],process[20],m,n;
    printf("Enter number of memory blocks: ");
    scanf("%d",&m);
    printf("Enter size of each memory block:\n");
    for(int i=0;i<m;i++){
        printf("Block %d: ",i+1);
        scanf("%d",&block[i]);
    }
    printf("\nEnter number of processes: ");
    scanf("%d",&n);
    printf("Enter size of each process:\n");
    for(int i=0;i<n;i++){
        printf("Process %d: ",i+1);
        scanf("%d",&process[i]);
    }
    firstFit(block,m,process,n);
    bestFit(block,m,process,n);
    worstFit(block,m,process,n);
    return 0;
}
