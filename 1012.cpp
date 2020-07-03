#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

struct Student {
    char id[7];
    int c;
    int m;
    int e;
    int a;
    int rank;
    char ch;
};

bool compareA(struct Student a, struct Student b) {
    return a.a > b.a;
}

bool compareC(struct Student a, struct Student b) {
    return a.c > b.c;
}

bool compareM(struct Student a, struct Student b) {
    return a.m > b.m;
}

bool compareE(struct Student a, struct Student b) {
    return a.e > b.e;
}

int main() {
    int n, m;
    scanf("%d", &n);
    struct Student *students = (struct Student *)malloc(n * sizeof(struct Student));
    scanf("%d", &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", students[i].id);
        scanf("%d", &(students[i].c));
        scanf("%d", &(students[i].m));
        scanf("%d", &(students[i].e));
        students[i].a = (students[i].c + students[i].m + students[i].e) / 3;
    }

    sort(students, students + n, compareA);
    for (int i = 0; i < n; i++) {
        int j = i - 1;
        while (j >= 0) {
            if (students[j].a > students[i].a) {
                break;
            }
            j--;
        }
        students[i].rank = j + 2;
        students[i].ch = 'A';
    }

    sort(students, students + n, compareC);
    for (int i = 0; i < n; i++) {
        int j = i - 1;
        while (j >= 0) {
            if (students[j].c > students[i].c) {
                break;
            }
            j--;
        }
        if (j + 2 < students[i].rank) {
            students[i].rank = j + 2;
            students[i].ch = 'C';
        }
    }

    sort(students, students + n, compareM);
    for (int i = 0; i < n; i++) {
        int j = i - 1;
        while (j >= 0) {
            if (students[j].m > students[i].m) {
                break;
            }
            j--;
        }
        if (j + 2 < students[i].rank) {
            students[i].rank = j + 2;
            students[i].ch = 'M';
        }
    }

    sort(students, students + n, compareE);
    for (int i = 0; i < n; i++) {
        int j = i - 1;
        while (j >= 0) {
            if (students[j].e > students[i].e) {
                break;
            }
            j--;
        }
        if (j + 2 < students[i].rank) {
            students[i].rank = j + 2;
            students[i].ch = 'E';
        }
    }

    for (int i = 0; i < m; i++) {
        char id[7];
        scanf("%s", id);
        bool isIn = false;
        for (int j = 0; j < n; j++) {
            if (strcmp(students[j].id, id) == 0) {
                printf("%d %c\n", students[j].rank, students[j].ch);
                isIn = true;
                break;
            }
        }
        if (!isIn) {
            printf("N/A\n");
        }
    }

    return 0;
}