#include <stdio.h>
#include <stdlib.h>

int main() {
    int k;
    scanf("%d", &k);
    int *N = (int *)malloc(k * sizeof(int));
    int isAllNegative = 1;
    for (int i = 0; i < k; i++) {
        scanf("%d", N + i);
        if (N[i] >= 0) {
            isAllNegative = 0;
        }
    }

    if (isAllNegative) {
        printf("0 %d %d", N[0], N[k - 1]);
        return 0;
    }

    int *dp = (int *)malloc(k * sizeof(int));
    dp[0] = N[0];
    int *front = (int *)malloc(k * sizeof(int));
    front[0] = 0;
    int max = N[0];
    int maxFront = 0;
    int maxTail = 0;
    for (int i = 1; i < k; i++) {
        if (dp[i - 1] < 0) {
            dp[i] = N[i];
            front[i] = i;
        } else {
            dp[i] = dp[i - 1] + N[i];
            front[i] = front[i - 1];
        }
        if (dp[i] > max) {
            max = dp[i];
            maxFront = front[i];
            maxTail = i;
        } else if (dp[i] == max && front[i] < maxFront) {
            maxFront = front[i];
            maxTail = i;
        }
    }
    printf("%d %d %d", max, N[maxFront], N[maxTail]);

    return 0;
}