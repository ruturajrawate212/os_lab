#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, r;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &r);

    int alloc[n][r], maxm[n][r], need[n][r], avail[r];
    bool finish[n];

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);
    }

    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < r; j++)
            scanf("%d", &maxm[i][j]);
    }

    printf("\nEnter Available Resources: ");
    for (int j = 0; j < r; j++)
        scanf("%d", &avail[j]);

    // Calculate need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = maxm[i][j] - alloc[i][j];

    for (int i = 0; i < n; i++)
        finish[i] = false;

    int safe_seq[n];
    int count = 0;

    while (count < n) {
        bool allocated = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool possible = true;

                for (int j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {
                    // allocate
                    for (int j = 0; j < r; j++)
                        avail[j] += alloc[i][j];

                    safe_seq[count++] = i;
                    finish[i] = true;
                    allocated = true;
                }
            }
        }

        if (!allocated)
            break;
    }

    // Result
    if (count == n) {
        printf("\nSystem is in a SAFE state\n");
        printf("Safe Sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d%s", safe_seq[i], (i == n - 1 ? "" : " -> "));
        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE state\n");
    }

    return 0;
}
