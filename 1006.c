#include <stdio.h>
#include <string.h>

struct Time {
    int hh;
    int mm;
    int ss;
};

int timestamp(struct Time *time) {
    return time->hh * 3600  + time->mm * 60 + time->ss;
}

int g(struct Time *a, struct Time *b) {
    return timestamp(a) > timestamp(b);
}

int main() {
    int m;
    scanf("%d", &m);

    char unlocker[64];
    char locker[64];
    struct Time earliest;
    int isEarliestSet = 0;
    struct Time latest;
    int isLatestSet = 0;

    char person[64];
    int hh, mm, ss;

    for (int i = 0; i < m; i++) {
        scanf("%s", person);
        scanf("%d:%d:%d", &hh, &mm, &ss);
        struct Time time = (struct Time){
            .hh = hh,
            .mm = mm,
            .ss = ss
        };
        if (isEarliestSet) {
            if (g(&earliest, &time)) {
                earliest = time;
                strcpy(unlocker, person);
            }
        } else {
            earliest = time;
            isEarliestSet = 1;
            strcpy(unlocker, person);
        }
        scanf("%d:%d:%d", &hh, &mm, &ss);
        time = (struct Time){
            .hh = hh,
            .mm = mm,
            .ss = ss
        };
        if (isLatestSet) {
            if (g(&time, &latest)) {
                latest = time;
                strcpy(locker, person);
            }
        } else {
            latest = time;
            isLatestSet = 1;
            strcpy(locker, person);
        }
    }

    printf("%s %s", unlocker, locker);

    return 0;
}