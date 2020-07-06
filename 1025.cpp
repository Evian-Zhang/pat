#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <string>
#include <queue>
using namespace std;

struct Record {
    string id;
    int ranklist;
    int score;

    bool operator<(const struct Record &record) const {
        return this->score < record.score || (this->score == record.score && this->id.compare(record.id) > 0);
    }
};

int main() {
    priority_queue<struct Record> records;
    int listCount;
    scanf("%d", &listCount);
    for (int ranklist = 0; ranklist < listCount; ranklist++) {
        int n;
        scanf("%d", &n);
        char id[14];
        for (int i = 0; i < n; i++) {
            scanf("%s", id);
            int score;
            scanf("%d", &score);
            records.push((struct Record){
                .id = string(id),
                .ranklist = ranklist,
                .score = score
            });
        }
    }

    int *currentCount = (int *)malloc((listCount + 1) * sizeof(int));
    memset(currentCount, 0, (listCount + 1) * sizeof(int));
    int *previousScore = (int *)malloc((listCount + 1) * sizeof(int));
    memset(previousScore, 0, (listCount + 1) * sizeof(int));
    int *previousRank = (int *)malloc((listCount + 1) * sizeof(int));
    memset(previousRank, 0, (listCount + 1) * sizeof(int));

    printf("%d", records.size());
    while (!records.empty()) {
        struct Record record = records.top();
        records.pop();
        printf("\n%s ", record.id.c_str());

        if (record.score != previousScore[listCount]) {
            previousRank[listCount] = currentCount[listCount];
        }
        printf("%d ", previousRank[listCount] + 1);
        previousScore[listCount] = record.score;
        currentCount[listCount]++;

        printf("%d ", record.ranklist + 1);

        if (record.score != previousScore[record.ranklist]) {
            previousRank[record.ranklist] = currentCount[record.ranklist];
        }
        printf("%d", previousRank[record.ranklist] + 1);
        previousScore[record.ranklist] = record.score;
        currentCount[record.ranklist]++;
    }

    return 0;
}