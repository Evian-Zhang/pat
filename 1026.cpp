#include <cstdio>
#include <cstdlib>
#include <vector>
#include <memory.h>
#include <queue>
using namespace std;

struct Pair {
    int arrive;
    int play;
    bool isVIP;

    bool operator<(const struct Pair &a) const {
        return this->arrive > a.arrive;
    }
};

int main() {
    int n;
    scanf("%d", &n);

    priority_queue<struct Pair> normalWaitings;
    priority_queue<struct Pair> vipWaitings;

    for (int i = 0; i < n; i++) {
        int hh, mm, ss;
        scanf("%d:%d:%d", &hh, &mm, &ss);
        int play;
        scanf("%d", &play);
        if (play > 120) {
            play = 120;
        }
        int isVIP;
        scanf("%d", &isVIP);
        // if (hh >= 21) {
        //     continue;
        // }
        if (isVIP) {
            vipWaitings.push((struct Pair){
                .arrive = (hh - 8) * 3600 + mm * 60 + ss,
                .play = play,
                .isVIP = (isVIP == 1)
            });
        } else {
            normalWaitings.push((struct Pair){
                .arrive = (hh - 8) * 3600 + mm * 60 + ss,
                .play = play,
                .isVIP = (isVIP == 1)
            });
        }
    }

    int tableCount, vipTableCount;
    scanf("%d %d", &tableCount, &vipTableCount);
    int *isVIPTable = (int *)malloc(tableCount * sizeof(int));
    memset(isVIPTable, 0, tableCount * sizeof(int));
    for (int i = 0; i < vipTableCount; i++) {
        int vipTable;
        scanf("%d", &vipTable);
        isVIPTable[vipTable - 1] = 1;
    }

    int *finishTime = (int *)malloc(tableCount * sizeof(int));
    memset(finishTime, 0, tableCount * sizeof(int));
    int *serve = (int *)malloc(tableCount * sizeof(int));
    memset(serve, 0, tableCount * sizeof(int));

    while (!normalWaitings.empty() || !vipWaitings.empty()) {
        int earliestTable = 0;

        for (int i = 1; i < tableCount; i++) {
            if (finishTime[i] < finishTime[earliestTable]) {
                earliestTable = i;
            }
        }

        if (finishTime[earliestTable] >= 13 * 3600) {
            break;
        }

        struct Pair pair;

        if (!normalWaitings.empty() && !vipWaitings.empty()) {
            pair = normalWaitings.top();
            if (pair.arrive > vipWaitings.top().arrive) {
                pair = vipWaitings.top();
                vipWaitings.pop();
            }
        } else if (!normalWaitings.empty()) {
            pair = normalWaitings.top();
        } else if (!vipWaitings.empty()) {
            pair = vipWaitings.top();
            vipWaitings.pop();
        } else {
            break;
        }

        int targetTable = -1;
        int smallestAvailableVIPTable = -1;
        for (int table = 0; table < tableCount; table++) {
            if (targetTable < 0 && finishTime[table] <= pair.arrive) {
                targetTable = table;
            }
            if (smallestAvailableVIPTable < 0 && finishTime[table] <= pair.arrive && isVIPTable[table]) {
                smallestAvailableVIPTable = table;
            }
        }
        if (smallestAvailableVIPTable >= 0 && pair.isVIP) {
            targetTable = smallestAvailableVIPTable;
        }
        if (targetTable < 0) {
            targetTable = earliestTable;
        }

        if (isVIPTable[targetTable] && !pair.isVIP) {
            if (!vipWaitings.empty()) {
                struct Pair tmp = vipWaitings.top();
                if (tmp.arrive <= finishTime[targetTable]) {
                    pair = tmp;
                    vipWaitings.pop();
                }
            }
        }

        if (!pair.isVIP) {
            normalWaitings.pop();
        }

        int playTime;
        int waiting;
        if (finishTime[targetTable] < pair.arrive) {
            playTime = pair.arrive;
            waiting = 0;
            finishTime[targetTable] = pair.arrive + pair.play * 60;
        } else {
            playTime = finishTime[targetTable];
            waiting = finishTime[targetTable] - pair.arrive;
            finishTime[targetTable] += pair.play * 60;
        }

        if (playTime >= 13 * 3600) {
            continue;
        }

        printf("%02d:%02d:%02d", pair.arrive / 3600 + 8, (pair.arrive / 60) % 60, pair.arrive % 60);
        printf(" %02d:%02d:%02d", playTime / 3600 + 8, (playTime / 60) % 60, playTime % 60);

        printf(" %d\n", (waiting + 30) / 60);
        serve[targetTable]++;
    }
    printf("%d", serve[0]);
    for (int i = 1; i < tableCount; i++) {
        printf(" %d", serve[i]);
    }

    return 0;
}