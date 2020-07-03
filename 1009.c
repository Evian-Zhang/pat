#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main() {
    int k1;
    scanf("%d", &k1);
    int *N1 = (int *)malloc(k1 * sizeof(int));
    double *a1 = (double *)malloc(k1 * sizeof(double));
    for (int i = 0; i < k1; i++) {
        scanf("%d", N1 + i);
        scanf("%lf", a1 + i);
    }
    int k2;
    scanf("%d", &k2);
    int *N2 = (int *)malloc(k2 * sizeof(int));
    double *a2 = (double *)malloc(k2 * sizeof(double));
    for (int i = 0; i < k2; i++) {
        scanf("%d", N2 + i);
        scanf("%lf", a2 + i);
    }

    int maxExp = N1[0] + N2[0];

    double *a = (double *)malloc((maxExp + 1) * sizeof(double));
    memset(a, 0, (maxExp + 1) * sizeof(double));

    for (int i1 = 0; i1 < k1; i1++) {
        for (int i2 = 0; i2< k2; i2++) {
            a[maxExp - N1[i1] - N2[i2]] += a1[i1] * a2[i2];
        }
    }
    
    int N = 0;
    for (int i = 0; i < maxExp + 1; i++) {
        if (a[i] != 0) {
            N++;
        }
    }
    printf("%d", N);
    for (int i = 0; i < maxExp + 1; i++) {
        if (a[i] != 0) {
            printf(" %d %.1lf", maxExp - i, a[i]);
        }
    }

    return 0;
}