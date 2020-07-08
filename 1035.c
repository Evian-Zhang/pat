#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    char name[11];
    char password[11];
};

int main() {
    int n;
    scanf("%d", &n);
    struct User *modifiedUsers = (struct User *)malloc(n * sizeof(struct User));
    int m = 0;
    for (int i = 0; i < n; i++) {
        char name[11];
        char password[11];
        scanf("%s %s", name, password);
        int needModify = 0;
        for (int j = 0; j < strlen(password); j++) {
            needModify = 1;
            switch (password[j]) {
                case '1': password[j] = '@'; break;
                case '0': password[j] = '%'; break;
                case 'l': password[j] = 'L'; break;
                case 'O': password[j] = 'o'; break;
                default: needModify = 0;
            }
        }
        if (needModify) {
            struct User user;
            strcpy(user.name, name);
            strcpy(user.password, password);
            modifiedUsers[m] = user;
            m++;
        }
    }

    if (m == 0) {
        if (n == 1) {
            printf("There is 1 account and no account is modified");
        } else {
            printf("There are %d accounts and no account is modified", n);
        }
    } else {
        printf("%d", m);
        for (int i = 0; i < m; i++) {
            printf("\n%s %s", modifiedUsers[i].name, modifiedUsers[i].password);
        }
    }

    return 0;
}