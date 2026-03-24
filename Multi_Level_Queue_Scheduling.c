#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
    char type[10];
};

struct Node {
    struct Process data;
    struct Node* next;
};

struct Queue {
    struct Node* front;
    struct Node* rear;
};

void enqueue(struct Queue* q, struct Process p) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = p;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

struct Process dequeue(struct Queue* q) {
    struct Node* temp = q->front;
    struct Process p = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return p;
}

int isEmpty(struct Queue* q) {
    return q->front == NULL;
}
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Arrival time of P%d: ", i + 1);
        scanf("%d", &p[i].arrival);
        printf("Burst time of P%d: ", i + 1);
        scanf("%d", &p[i].burst);
        printf("Type of P%d (system/user): ", i + 1);
        scanf("%s", p[i].type);
        p[i].remaining = p[i].burst;
        p[i].completion = 0;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    struct Queue systemQ = {NULL, NULL};
    struct Queue userQ = {NULL, NULL};

    int time = 0, completed = 0, i = 0;
    struct Process* current = NULL;

    int start[1000], end[1000], proc[1000];
    int index = 0;

    while (completed < n) {
        while (i < n && p[i].arrival <= time) {
            if (strcmp(p[i].type, "system") == 0)
                enqueue(&systemQ, p[i]);
            else
                enqueue(&userQ, p[i]);
            i++;
        }
        if (current != NULL) {
            if (strcmp(current->type, "user") == 0 && !isEmpty(&systemQ)) {
                enqueue(&userQ, *current);
                current = NULL;
            }
        }
        if (current == NULL) {
            if (!isEmpty(&systemQ)) {
                struct Process temp = dequeue(&systemQ);
                current = (struct Process*)malloc(sizeof(struct Process));
                *current = temp;
            } else if (!isEmpty(&userQ)) {
                struct Process temp = dequeue(&userQ);
                current = (struct Process*)malloc(sizeof(struct Process));
                *current = temp;
            } else {
                start[index] = time;
                proc[index] = -1;
                time++;
                end[index] = time;
                index++;
                continue;
            }
        }
        start[index] = time;
        proc[index] = current->pid;
        time++;
        current->remaining--;
        end[index] = time;
        index++;
        if (current->remaining == 0) {
            current->completion = time;
            for (int k = 0; k < n; k++) {
                if (p[k].pid == current->pid) {
                    p[k].completion = current->completion;
                    p[k].turnaround = p[k].completion - p[k].arrival;
                    p[k].waiting = p[k].turnaround - p[k].burst;
                }
            }
            completed++;
            free(current);
            current = NULL;
        }
    }
    printf("\nGantt Chart:\n");
    for (int i = 0; i < index; i++) {
        if (proc[i] == -1)
            printf("| Idle ");
        else
            printf("| P%d ", proc[i]);
    }
    printf("|\n");
    for (int i = 0; i < index; i++) {
        printf("%d\t", start[i]);
    }
    printf("%d\n", end[index - 1]);
    float totalWT = 0, totalTAT = 0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tType\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%s\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround,
               p[i].waiting, p[i].type);
        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }
    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}
