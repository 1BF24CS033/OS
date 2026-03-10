//Implement priority scheduling with preemptive and non-preemptive case

#include <stdio.h>
#include <limits.h>

struct Process {
    int at;
    int pid;
    int bt;
    int ct;
    int rt;
    int wt;
    int tat;
    int pr;
};

void preemptive(){
    struct Process p[20];
    int n, i, time = 0, completed = 0;
    int min_pr, index;
    float tatAvg, wtAvg;


    int gantt[1000], gantt_time[1000];
    int g_index = 0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        p[i].pid = i+1;

        printf("\nProcess %d\n",i+1);

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Burst Time: ");
        scanf("%d",&p[i].bt);

        printf("Priority: ");
        scanf("%d",&p[i].pr);

        p[i].rt = p[i].bt;
    }


    while(completed != n){
        min_pr = INT_MAX;
        index = -1;

        for(i=0;i<n;i++){
            if(p[i].at <= time && p[i].rt > 0 && p[i].pr < min_pr){
                min_pr = p[i].pr;
                index = i;
            }
        }

        if(index != -1){
            p[index].rt--;
            gantt[g_index] = p[index].pid;
            gantt_time[g_index] = time;
            g_index++;
            time++;

            if(p[index].rt == 0){
                completed++;
                p[index].ct = time;
                p[index].tat = p[index].ct - p[index].at;
                p[index].wt = p[index].tat - p[index].bt;
            }
        }
        else{
            gantt[g_index] = -1;
            gantt_time[g_index] = time;
            g_index++;
            time++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tWT\tTAT\tCT\n");
    for(i=0;i<n;i++){
        tatAvg=tatAvg+p[i].tat;
        wtAvg=wtAvg+p[i].wt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].pr,p[i].wt,p[i].tat,p[i].ct);
    }

    printf("\nGantt Chart:\n");

    for(i=0;i<g_index;i++){
        if(i==0 || gantt[i] != gantt[i-1]){
            if(gantt[i] == -1)
                printf("|  Idle  ");
            else
                printf("| P%d\t", gantt[i]);
        }
    }
    printf("|\n");


    for(i=0;i<g_index;i++){
        if(i==0 || gantt[i] != gantt[i-1]){
            printf("%d\t", gantt_time[i]);
        }
    }
    printf("%d\n", time);


    printf("Average Turn Around Time is: %.2f\n", tatAvg/n);
    printf("Average waiting time is: %.2f", wtAvg/n);

}


void non_preemptive(){
    int n, i, j, time = 0;
    struct Process p[20], temp;
    float tatAvg, wtAvg;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i=0;i<n;i++){
        printf("\nProcess %d\n", i+1);
        p[i].pid = i+1;

        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Enter Priority: ");
        scanf("%d", &p[i].pr);
    }

    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(p[i].at > p[j].at ||
              (p[i].at == p[j].at && p[i].pr > p[j].pr)){
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }


    time = 0;
    for(i=0;i<n;i++){
        if(time < p[i].at) {
            time = p[i].at;
        }
        p[i].wt = time - p[i].at;
        time += p[i].bt;
        p[i].ct = time;
         p[i].tat = p[i].ct - p[i].at;
    }


    printf("\nPID\tAT\tBT\tPR\tWT\tTAT\tCT\n");
    for(i=0;i<n;i++){
        tatAvg=tatAvg+p[i].tat;
        wtAvg=wtAvg+p[i].wt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid, p[i].at, p[i].bt, p[i].pr,
            p[i].wt, p[i].tat, p[i].ct);
    }


    printf("\nGantt Chart:\n");

    time = 0;
    for(i=0;i<n;i++){
        if(time < p[i].at){
            printf("|  Idle  ");
            time = p[i].at;
        }
        printf("| P%d\t", p[i].pid);
        time += p[i].bt;
    }
    printf("|\n");


    time = 0;
    printf("0");
    for(i=0;i<n;i++){
        if(time < p[i].at){
            time = p[i].at;
            printf("\t%d", time);
        }
        time += p[i].bt;
        printf("\t%d", time);
    }
    printf("\n");
    printf("Average Turn Around Time is: %f\n", tatAvg/n);
    printf("Average waiting time is: %f", wtAvg/n);
}

int main(){
    int choice;
    printf("Priority Scheduling\n1. Preemptive\n2. Non-preemptive\nEnter choice: ");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            preemptive();
            break;
        case 2:
            non_preemptive();
            break;
        default:
            printf("Error. Please enter a valid input(1 or 2)\n");
            break;
    }
    return 0;
}



