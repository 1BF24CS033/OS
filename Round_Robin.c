#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int waiting;
    int turnaround;
    int completion;
};

int main() {
    int n, quantum;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    struct Process p[n];

    for(int i=0;i<n;i++){
        p[i].pid=i+1;

        printf("Arrival time of P%d: ",i+1);
        scanf("%d",&p[i].arrival);

        printf("Burst time of P%d: ",i+1);
        scanf("%d",&p[i].burst);

        p[i].remaining=p[i].burst;
    }

    printf("Enter time quantum: ");
    scanf("%d",&quantum);

    int time=0, completed=0;


    int start[1000], end[1000], proc[1000];
    int index=0;

    while(completed<n){
        int executed=0;

        for(int i=0;i<n;i++){
            if(p[i].arrival<=time && p[i].remaining>0){
                executed=1;

                start[index]=time;
                proc[index]=p[i].pid;

                if(p[i].remaining>quantum){
                    time+=quantum;
                    p[i].remaining-=quantum;
                }
                else{
                    time+=p[i].remaining;
                    p[i].remaining=0;

                    p[i].completion=time;
                    p[i].turnaround=p[i].completion-p[i].arrival;
                    p[i].waiting=p[i].turnaround-p[i].burst;

                    completed++;
                }

                end[index]=time;
                index++;
            }
        }

        if(executed==0){

            start[index]=time;
            proc[index]=-1;
            time++;
            end[index]=time;
            index++;
        }
    }


    printf("\nGantt Chart:\n");
    for(int i=0;i<index;i++){
        if(proc[i]==-1)
            printf("| Idle ");
        else
            printf("| P%d ",proc[i]);
    }
    printf("|\n");


    for(int i=0;i<index;i++){
        printf(" %d   ",start[i]);
    }
    printf("%d\n",end[index-1]);


    float totalWT=0,totalTAT=0;

    printf("\nPID\tAT\tBT\tWT\tTAT\n");

    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,
        p[i].arrival,
        p[i].burst,
        p[i].waiting,
        p[i].turnaround);

        totalWT+=p[i].waiting;
        totalTAT+=p[i].turnaround;
    }

    printf("\nAverage Waiting Time = %.2f",totalWT/n);
    printf("\nAverage Turnaround Time = %.2f\n",totalTAT/n);

    return 0;
}
