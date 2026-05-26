/*

#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m];
    int need[n][m];

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("Enter Maximum Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter Available Resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    bool finish[n];
    for (int i = 0; i < n; i++) finish[i] = false;
    int safeSeq[n];
    int work[m];
    for (int i = 0; i < m; i++) work[i] = avail[i];
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
                    for (int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("\nSystem is not in a safe state.\n");
            return 0;
        }
    }
    printf("\nSystem is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");
    return 0;
}
*/




#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m];
    int need[n][m];

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("Enter Maximum Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter Available Resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    bool finish[n];
    for (int i = 0; i < n; i++) finish[i] = false;
    int safeSeq[n];
    int work[m];
    for (int i = 0; i < m; i++) work[i] = avail[i];
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
                    for (int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("\nSystem is not in a safe state.\n");
            return 0;
        }
    }
    printf("\nSystem is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    int reqProcess;
    printf("\nEnter process number making request: ");
    scanf("%d", &reqProcess);

    int request[m];
    printf("Enter request vector:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &request[j]);
    }

    for (int j = 0; j < m; j++) {
        if (request[j] > need[reqProcess][j]) {
            printf("Error: Process exceeded its maximum claim.\n");
            return 0;
        }
    }

    for (int j = 0; j < m; j++) {
        if (request[j] > avail[j]) {
            printf("Resources not available. Process must wait.\n");
            return 0;
        }
    }

    for (int j = 0; j < m; j++) {
        avail[j] -= request[j];
        alloc[reqProcess][j] += request[j];
        need[reqProcess][j] -= request[j];
    }

    for (int i = 0; i < n; i++) finish[i] = false;
    for (int i = 0; i < m; i++) work[i] = avail[i];
    count = 0;

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
                    for (int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            for (int j = 0; j < m; j++) {
                avail[j] += request[j];
                alloc[reqProcess][j] -= request[j];
                need[reqProcess][j] += request[j];
            }
            printf("Request cannot be granted (unsafe state). Rolling back.\n");
            return 0;
        }
    }

    printf("Request granted. System remains in safe state.\n");
    printf("New safe sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");
    return 0;
}
