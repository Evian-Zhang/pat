#include <stdio.h>

int main() {
    long long a, b;
    scanf("%lld %lld", &a, &b);
    long long result = a + b;
    if (result < 0) {
        printf("-");
        result = -result;
    }
    unsigned long long max = 1;
    while (result >= max * 1000) {
        max *= 1000;
    }
    printf("%lld", result / max);
    result %= max;
    int count = 0;
    while (max != 1) {
        if (count == 0) {
            printf(",");
        }
        max /= 10;
        printf("%lld", result / max);
        result %= max;
        count = (count + 1) % 3;
    }
    return 0;
}