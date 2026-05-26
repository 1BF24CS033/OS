#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;
    int alloc[20][20], request[20][20], avail[20];
    int work[20], finish[20], safeSeq[20];
    int i, j, count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        printf("P%d: ", i);
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++) {
        printf("P%d: ", i);
        for(j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    for(j = 0; j < m; j++) {
        work[j] = avail[j];
    }

    for(i = 0; i < n; i++) {
        int allocated = 0;

        for(j = 0; j < m; j++) {
            if(alloc[i][j] != 0) {
                allocated = 1;
                break;
            }
        }

        if(allocated == 0) {
            finish[i] = 1;
        } else {
            finish[i] = 0;
        }
    }

    while(count < n) {
        int found = 0;

        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int canExecute = 1;

                for(j = 0; j < m; j++) {
                    if(request[i][j] > work[j]) {
                        canExecute = 0;
                        break;
                    }
                }

                if(canExecute == 1) {
                    for(j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }

                    safeSeq[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            break;
        }
    }

    printf("\nProcess\t\tAllocation\tRequest\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t\t", i);

        for(j = 0; j < m; j++) {
            printf("%d ", alloc[i][j]);
        }

        printf("\t\t");

        for(j = 0; j < m; j++) {
            printf("%d ", request[i][j]);
        }

        printf("\n");
    }

    printf("\nAvailable Resources: ");
    for(j = 0; j < m; j++) {
        printf("%d ", avail[j]);
    }

    int deadlock = 0;

    for(i = 0; i < n; i++) {
        if(finish[i] == 0) {
            deadlock = 1;
            break;
        }
    }

    if(deadlock == 0) {
        printf("\n\nNo deadlock detected.");
        printf("\nSafe Sequence: ");

        for(i = 0; i < count; i++) {
            printf("P%d", safeSeq[i]);

            if(i != count - 1) {
                printf(" -> ");
            }
        }

        printf("\n");
    } else {
        printf("\n\nDeadlock detected.");
        printf("\nProcesses causing deadlock: ");

        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                printf("P%d ", i);
            }
        }

        printf("\n");
    }

    return 0;
}
