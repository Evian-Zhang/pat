#include <stdio.h>

int main() {
    char word[128];
    char ch;
    int length = 0;
    while (scanf("%c", &ch) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\r') {
            break;
        }
        word[length] = ch;
        length++;
    }

    int n1 = (length + 2) / 3;
    int n2 = length + 2 - 2 * n1;
    for (int i = 0; i < n1 - 1; i++) {
        printf("%c", word[i]);
        for (int j = 0; j < n2 - 2; j++) {
            printf(" ");
        }
        printf("%c\n", word[length - i - 1]);
    }
    for (int i = 0; i < n2; i++) {
        printf("%c", word[n1 + i - 1]);
    }

    return 0;
}
