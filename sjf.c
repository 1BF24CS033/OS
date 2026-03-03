#include <stdio.h>
#include <limits.h>

typedef struct Process {
    int name;
    int at;  // Arrival Time
    int bt;  // Burst Time
    int rt;  // Remaining Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
} Process;

void sjf_nonpreemptive(struct Process p[], int n) {
    int complete = 0, time = 0;
    int visited[n];
    for(int i = 0; i < n; i++) visited[i] = 0;

    while(complete < n) {
        int min = INT_MAX, index = -1;
        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && !visited[i]) {
                if(p[i].bt < min) {
                    min = p[i].bt;
                    index = i;
                }
            }
        }

        if(index != -1) {
            time += p[index].bt;
            p[index].ct = time;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
            visited[index] = 1;
            complete++;
        } else {
            time++;
        }
        printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
        float tS = 0, wS = 0;
        for(int i = 0; i < n; i++) {
            printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].name, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
            tS += p[i].tat; wS += p[i].wt;
        }
        printf("\nAverage Turn Around Time: %.2f\n", (tS/n));
        printf("Average Waiting Time: %.2f\n", (wS/n));

    }

    // Printing logic is shared, but we call it here for simplicity
    printf("\nNon-Preemptive SJF Results:");
}

void sjf_preemptive(struct Process p[], int n) {
    int complete = 0, time = 0;
    double tatSum = 0, wtSum = 0;

    while(complete < n) {
        int min = INT_MAX, index = -1;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].rt > 0) {
                if(p[i].rt < min) {
                    min = p[i].rt;
                    index = i;
                }
                // Tie-breaker: If remaining time is same, pick earlier arrival
                else if(p[i].rt == min) {
                    if(p[i].at < p[index].at) {
                        index = i;
                    }
                }
            }
        }

        if(index != -1) {
            p[index].rt--;
            time++;
            if(p[index].rt == 0) {
                complete++;
                p[index].ct = time;
                p[index].tat = p[index].ct - p[index].at;
                p[index].wt = p[index].tat - p[index].bt;
                tatSum += p[index].tat;
                wtSum += p[index].wt;
            }
        } else {
            time++;
        }
    }

    printf("\nPreemptive SJF (SRTF) Results:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].name, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Turn Around Time: %.2f\n", (tatSum / n));
    printf("Average Waiting Time: %.2f\n", (wtSum / n));
}

int main() {
    int choice;
    int pid[] = {1, 2, 3, 4, 5};
    int at[] = {1, 3, 5, 7, 9};
    int bt[] = {3, 7, 1, 5, 6};
    int n = sizeof(pid) / sizeof(pid[0]);
    Process p[n];

    for(int i = 0; i < n; i++) {
        p[i].name = pid[i];
        p[i].at = at[i];
        p[i].bt = bt[i];
        p[i].rt = bt[i]; // Crucial: Initialize remaining time
    }

    printf("Choose 1 for non-preemptive and 2 for preemptive: ");
    if(scanf("%d", &choice) != 1) return 1;

    switch(choice) {
        case 1:
            sjf_nonpreemptive(p, n);
            break;
        case 2:
            sjf_preemptive(p, n);
            break;
        default:
            printf("Invalid input\n");
    }

    return 0;
}