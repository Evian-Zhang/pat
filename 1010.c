#include <stdio.h>

void getDigits(int *d, int *n) {
    char ch;
    while (scanf("%c", &ch) != EOF) {
        if (ch >= '0' && ch <= '9') {
            d[*n] = ch - '0';
            (*n)++;
        } else if (ch >= 'a' && ch <= 'z') {
            d[*n] = ch - 'a' + 10;
            (*n)++;
        } else {
            break;
        }
    }
}

unsigned long long value(int *d, int n, unsigned long long radix) {
    unsigned long long value = 0;
    unsigned long long pow = 1;
    while (n >= 1) {
        n--;
        value += d[n] * pow;
        pow *= radix;
    }
    return value;
}

int main() {
    int d1[10];
    int n1 = 0;
    int d2[10];
    int n2 = 0;
    getDigits(d1, &n1);
    getDigits(d2, &n2);
    int tag;
    scanf("%d", &tag);
    int radix;
    scanf("%d", &radix);

    int *d3;
    int n3;
    int *d4;
    int n4;
    if (tag == 1) {
        d3 = d1;
        n3 = n1;
        d4 = d2;
        n4 = n2;
    } else {
        d3 = d2;
        n3 = n2;
        d4 = d1;
        n4 = n1;
    }

    unsigned long long radix2 = 0;
    for (int i = 0; i < n4; i++) {
        if (radix2 < d4[i]) {
            radix2 = d4[i];
        }
    }
    radix2++;
    unsigned long long value1 = value(d3, n3, radix);
    unsigned long long upperBound = value1;
    unsigned long long mid;
    unsigned long long value2;
    while (radix2 <= upperBound) {
        mid = (radix2 + upperBound) / 2;
        value2 = value(d4, n4, mid);
        if (value2 == value1) {
            printf("%llu", mid);
            return 0;
        } else if (value2 < value1) {
            radix2 = mid + 1;
        } else if (value2 > value1) {
            upperBound = mid - 1;
        }
    }
    printf("Impossible");

    return 0;
}