#include <stdio.h>
#include <stdlib.h>

int k;
int *N;

int main() {
    scanf("%d", &k);
    N = (int *)malloc(k * sizeof(int));
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

    int sum = N[0];
    int front = 0;
    int tail = 0;

    for (int start = 0; start < k; start++) {
        for (int end = start; end < k; end++) {
            int tmp = 0;
            for (int i = start; i <= end; i++) {
                tmp += N[i];
            }
            if (tmp > sum ||
                (tmp == sum && (
                    (end - start > tail - front) ||
                        (end - start == tail - front && start < front)
                    )
                )
            ) {
                sum = tmp;
                front = start;
                tail = end;
            }
        }
    }
    printf("%d %d %d", sum, N[front], N[tail]);

    return 0;
}