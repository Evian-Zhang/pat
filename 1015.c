#include <stdio.h>
#include <math.h>

int isPrime(int n) {
    if (n == 0 || n == 1) { return 0; }
    if (n == 2) { return 1; }
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int getReverse(int n, int radix) {
    int approx = 1;
    int length = 1;
    while (n >= approx * radix) {
        approx *= radix;
        length++;
    }
    int reverse = 0;
    int pow = 1;
    for (int i = 0; i < length; i++) {
        reverse += n / approx * pow;
        pow *= radix;
        n %= approx;
        approx /= radix;
    }
    return reverse;
}

int main() {
    while (1) {
        int n;
        scanf("%d", &n);
        if (n < 0) {
            break;
        }

        int d;
        scanf("%d", &d);

        if (isPrime(n) && isPrime(getReverse(n, d))) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}