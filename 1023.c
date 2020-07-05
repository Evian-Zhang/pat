#include <stdio.h>
#include <stdlib.h>

int main() {
    int n[20];
    int digit[10] = { 0 };
    char ch;
    int index = 0;
    while (scanf("%c", &ch) != EOF) {
        if (ch >= '0' && ch <= '9') {
            n[index] = ch - '0';
            digit[ch - '0'] = 1;
            index++;
        } else {
            break;
        }
    }
    int doub[20];
    int carry = 0;
    int isYes = 1;
    for (int i = index - 1; i >= 0; i--) {
        int res = n[i] * 2 + carry;
        carry = res / 10;
        res %= 10;
        doub[i] = res;
        if (digit[res] == 0) {
            isYes = 0;
        } else {
            digit[res]++;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (digit[i] == 1) {
            isYes = 0;
        }
    }
    if (isYes) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    if (carry > 0) {
        printf("%d", carry);
    }
    for (int i = 0; i < index; i++) {
        printf("%d", doub[i]);
    }

    return 0;
}