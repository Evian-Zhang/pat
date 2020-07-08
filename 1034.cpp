#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

int n = 0;
int k;

int weights[20000][20000] = { 0 };
bool visited[20000] = { 0 };
bool inNet[20000] = { 0 };

int DFS(int node, int &lead, int &max, int &peopleCount) {
    peopleCount++;
    visited[node] = true;
    int sum = 0;
    int leadWeight = 0;
    for (int i = 0; i < 20000; i++) {
        if (inNet[i]) {
            leadWeight += weights[node][i];
            if (!visited[i] && weights[node][i] > 0) {
                sum += weights[node][i];
            }
        }
    }
    for (int i = 0; i < 20000; i++) {
        if (inNet[i]) {
            if (!visited[i] && weights[node][i] > 0) {
                sum += DFS(i, lead, max, peopleCount);
            }
        }
    }
    if (leadWeight > max) {
        max = leadWeight;
        lead = node;
    }
    return sum;
}

struct Leader {
    int pos;
    int peopleCount;

    bool operator<(const struct Leader &leader) const {
        return this->pos > leader.pos;
    }
};

int main() {
    int lines;
    scanf("%d %d", &lines, &k);
    for (int i = 0; i < lines; i++) {
        char tmp[4];
        scanf("%s", tmp);
        int person1 = (tmp[0] - 'A') * 26 * 26 + (tmp[1] - 'A') * 26 + (tmp[2] - 'A');
        n++;
        scanf("%s", tmp);
        int person2 = (tmp[0] - 'A') * 26 * 26 + (tmp[1] - 'A') * 26 + (tmp[2] - 'A');
        n++;
        int weight;
        scanf("%d", &weight);
        weights[person1][person2] += weight;
        weights[person2][person1] += weight;
        inNet[person1] = true;
        inNet[person2] = true;
    }

    priority_queue<struct Leader> leaders;
    for (int person = 0; person < 20000; person++) {
        if (!inNet[person] || visited[person]) { continue; }
        int lead = -1;
        int max = 0;
        int peopleCount = 0;
        int total = DFS(person, lead, max, peopleCount);
        if (peopleCount > 2 && total > k) {
            leaders.push((struct Leader){
                .pos = lead,
                .peopleCount = peopleCount
            });
        }
    }

    printf("%d", leaders.size());
    while (!leaders.empty()) {
        struct Leader leader = leaders.top();
        leaders.pop();
        char ch1 = leader.pos / (26 * 26) + 'A';
        char ch2 = (leader.pos / 26) % 26 + 'A';
        char ch3 = leader.pos % 26 + 'A';
        printf("\n%c%c%c %d", ch1, ch2, ch3, leader.peopleCount);
    }

    return 0;
}