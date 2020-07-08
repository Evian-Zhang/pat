#include <stdio.h>
#include <string.h>

struct Student {
    int score;
    char name[11];
    char id[11];
};

int main() {
    struct Student lowestMale, highestFemale;
    lowestMale.score = -1;
    highestFemale.score = -1;

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char name[11];
        char id[11];
        char gender;
        int score;
        scanf("%s %c %s %d", name, &gender, id, &score);
        switch (gender) {
            case 'M': {
                if (lowestMale.score < 0 || score < lowestMale.score) {
                    lowestMale.score = score;
                    strcpy(lowestMale.name, name);
                    strcpy(lowestMale.id, id);
                }
                break;
            };
            case 'F': {
                if (highestFemale.score < 0 || score > highestFemale.score) {
                    highestFemale.score = score;
                    strcpy(highestFemale.name, name);
                    strcpy(highestFemale.id, id);
                }
                break;
            }
        }
    }

    int isAbsent = 0;
    if (highestFemale.score < 0) {
        isAbsent = 1;
        printf("Absent\n");
    } else {
        printf("%s %s\n", highestFemale.name, highestFemale.id);
    }
    if (lowestMale.score < 0) {
        isAbsent = 1;
        printf("Absent\n");
    } else {
        printf("%s %s\n", lowestMale.name, lowestMale.id);
    }

    if (isAbsent) {
        printf("NA");
    } else {
        printf("%d", highestFemale.score - lowestMale.score);
    }

    return 0;
}