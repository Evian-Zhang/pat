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
        int isVIP;
        scanf("%d", &isVIP);
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
        isVIPTable[vipTable] = 1;
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

        if (finishTime[earliestTable] > 13 * 3600) {
            break;
        }

        struct Pair pair;
        if (isVIPTable[earliestTable]) {
            pair.arrive = -1;
            while (!vipWaitings.empty()) {
                pair = vipWaitings.top();
                vipWaitings.pop();
                if (finishTime[earliestTable] < pair.arrive + 2 * 3600) {
                    break;
                }
                pair.arrive = -1;
            }
            if (pair.arrive < 0) {
                while (!normalWaitings.empty()) {
                    pair = normalWaitings.top();
                    normalWaitings.pop();
                    if (finishTime[earliestTable] < pair.arrive + 2 * 3600) {
                        break;
                    }
                    pair.arrive = -1;
                }
            }
            if (pair.arrive < 0) {
                break;
            }
        } else {
            struct Pair firstNormal, firstVIP;
            firstNormal.arrive = -1;
            firstVIP.arrive = -1;
            while (!normalWaitings.empty()) {
                firstNormal = normalWaitings.top();
                if (finishTime[earliestTable] < firstNormal.arrive + 2 * 3600) {
                    break;
                }
                normalWaitings.pop();
                firstNormal.arrive = -1;
            }
            while (!vipWaitings.empty()) {
                firstVIP = vipWaitings.top();
                if (finishTime[earliestTable] < firstVIP.arrive + 2 * 3600) {
                    break;
                }
                vipWaitings.pop();
                firstVIP.arrive = -1;
            }
            if (firstNormal.arrive >= 0 && firstVIP.arrive >= 0) {
                if (firstNormal.arrive < firstVIP.arrive) {
                    pair = firstNormal;
                    normalWaitings.pop();
                } else {
                    pair = firstVIP;
                    vipWaitings.pop();
                }
            } else if (firstNormal.arrive >= 0) {
                pair = firstNormal;
                normalWaitings.pop();
            } else if (firstVIP.arrive >= 0) {
                pair = firstVIP;
                vipWaitings.pop();
            } else {
                break;
            }
        }

        int playTime;
        int waiting;
        if (finishTime[earliestTable] < pair.arrive) {
            playTime = pair.arrive;
            waiting = 0;
            finishTime[earliestTable] = pair.arrive + pair.play * 60;
        } else {
            playTime = finishTime[earliestTable];
            waiting = finishTime[earliestTable] - pair.arrive;
            finishTime[earliestTable] += pair.play * 60;
        }

        printf("%02d:%02d:%02d", pair.arrive / 3600 + 8, (pair.arrive / 60) % 60, pair.arrive % 60);
        printf(" %02d:%02d:%02d", playTime / 3600 + 8, (playTime / 60) % 60, playTime % 60);

        printf(" %d\n", (waiting + 30) / 60);
        serve[earliestTable]++;
    }
    printf("%d", serve[0]);
    for (int i = 1; i < tableCount; i++) {
        printf(" %d", serve[i]);
    }

    return 0;
}