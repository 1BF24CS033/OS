#include <stdio.h>
#include <stdbool.h>

int n, m;
int alloc[20][20], max[20][20], need[20][20], avail[20];

bool safetyCheck() {
    bool finish[20];
    int work[20], safeSeq[20];

    for (int i = 0; i < n; i++)
        finish[i] = false;

    for (int j = 0; j < m; j++)
        work[j] = avail[j];

    int count = 0;
    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool possible = true;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found)
            return false;
    }
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);

    printf("\n");
    return true;
}

void resourceRequest(int process, int request[]) {
    for (int j = 0; j < m; j++) {
        if (request[j] > need[process][j]) {
            printf("Error: request exceeds need\n");
            return;
        }
    }

    for (int j = 0; j < m; j++) {
        if (request[j] > avail[j]) {
            printf("Resources not available, process must wait\n");
            return;
        }
    }

    for (int j = 0; j < m; j++) {
        avail[j] -= request[j];
        alloc[process][j] += request[j];
        need[process][j] -= request[j];
    }

    if (safetyCheck()) {
        printf("Request granted\n");
    } else {
        for (int j = 0; j < m; j++) {
            avail[j] += request[j];
            alloc[process][j] -= request[j];
            need[process][j] += request[j];
        }
        printf("Request denied, unsafe state\n");
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter maximum matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter available resources:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    if (!safetyCheck()) {
        printf("System is not in a safe state.\n");
        return 0;
    }

    int process;
    printf("Enter process number: ");
    scanf("%d", &process);

    int request[20];
    printf("Enter request vector:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &request[j]);

    resourceRequest(process, request);

    return 0;
}
