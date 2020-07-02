#include <stdio.h>

char *spell[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main() {
    int sum = 0;
    char ch;
    while (scanf("%c", &ch) != EOF && ch >= '0' && ch <= '9') {
        sum += ch - '0';
    }
    int approx = 1;
    while (sum >= approx * 10) {
        approx *= 10;
    }
    while (approx != 1) {
        printf("%s ", spell[sum / approx]);
        sum %= approx;
        approx /= 10;
    }
    printf("%s", spell[sum / approx]);

    return 0;
}