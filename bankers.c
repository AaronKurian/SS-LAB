#include <stdio.h>

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);
    
    int need[n][m], max[n][m], allocation[n][m];
    int available[m], finish[n], work[m], safeseq[n]; 

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the max matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available array:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
        work[i] = available[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        finish[i] = -1;
    }

    int count = 0;
    while (count < n) {
        int found = 0;
        
        for (int i = 0; i < n; i++) {
            if (finish[i] == -1) { 
                int canFinish = 1;
                
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = 0;
                        break;
                    }
                }


                if (canFinish) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = 1; 
                    safeseq[count++] = i;
                    found = 1;
                }
            }
        }
        
        if (found == 0) { 
            printf("System is in deadlock.\n");
            return 0;
        }
    }

    printf("Need Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    printf("Safe Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d", safeseq[i]);
        if (i < n - 1) printf(" -> ");
    }
    printf("\n");

    return 0;
}

