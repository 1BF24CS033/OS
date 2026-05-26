#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_PROCESSES 10
#define MAX_TIME 30

typedef struct {
    int pid;
    int burst;
    int period;
    int remaining_time;
    int next_arrival;
    int ct;
    int wt;
    int tat;
    int completed_first;
} Process;

void rate_monotonic_scheduling(Process p[], int n) {
    int time = 0, executed;
    int gantt_chart[MAX_TIME];
    double utilization = 0;

    for (int i = 0; i < n; i++) utilization += (double)p[i].burst / p[i].period;
    double bound = n * (pow(2.0, 1.0 / n) - 1);

    printf("\n--- Scheduling Analysis ---\n");
    printf("Total Utilization (U): %.4f\n", utilization);
    printf("RMS Bound: %.4f\n", bound);

    if (utilization > 1.0) {
        printf("WARNING: U > 1. System is NOT schedulable.\n");
    } else if (utilization <= bound) {
        printf("Result: System IS schedulable.\n");
    } else {
        printf("Result: Schedulability is unknown\n");
    }

    while (time < MAX_TIME) {
        executed = -1;
        int min_period = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].next_arrival <= time && p[i].remaining_time > 0) {
                if (p[i].period < min_period) {
                    min_period = p[i].period;
                    executed = i;
                }
            }
        }

        if (executed != -1) {
            gantt_chart[time] = p[executed].pid;
            p[executed].remaining_time--;

            if (p[executed].remaining_time == 0) {
                if (!p[executed].completed_first) {
                    p[executed].ct = time + 1;
                    p[executed].tat = p[executed].ct - 0;
                    p[executed].wt = p[executed].tat - p[executed].burst;
                    p[executed].completed_first = 1;
                }
                p[executed].next_arrival += p[executed].period;
                p[executed].remaining_time = p[executed].burst;
            }
        } else {
            gantt_chart[time] = -1; // Idle
        }
        time++;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].period > p[j+1].period) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");
    printf("%-5s %-5s %-8s %-5s %-5s %-5s\n", "ID", "BT", "Period", "CT", "WT", "TAT");
    for (int i = 0; i < n; i++) {
        if (p[i].completed_first) {
            printf("%-5d %-5d %-8d %-5d %-5d %-5d\n",
                   p[i].pid, p[i].burst, p[i].period, p[i].ct, p[i].wt, p[i].tat);
        } else {
            printf("%-5d %-5d %-8d %-5s %-5s %-5s\n",
                   p[i].pid, p[i].burst, p[i].period, "--", "--", "--");
        }
    }

    printf("\n--- Gantt Chart ---\n|");
    for (int i = 0; i < MAX_TIME; i++) {
        if (gantt_chart[i] == -1) printf("  |");
        else printf("P%d|", gantt_chart[i]);
    }
    printf("\n");
    for (int i = 0; i <= MAX_TIME; i++) printf("%-3d", i);
    printf("\n");
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter PID, Burst, and Period for Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].pid, &processes[i].burst, &processes[i].period);
        processes[i].remaining_time = processes[i].burst;
        processes[i].next_arrival = 0;
        processes[i].completed_first = 0;
    }

    rate_monotonic_scheduling(processes, n);
    return 0;
}
