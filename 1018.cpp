#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <vector>
using namespace std;

int cmax;
int n;
int sp;
int *c;
int **graph;
vector<int> *previous;

void dijkstra() {
    int *visited = (int *)malloc((n + 1) * sizeof(int));
    memset(visited, 0, (n + 1) * sizeof(int));
    // visited[0] = 1;
    int *shortest = (int *)malloc((n + 1) * sizeof(int));
    memset(shortest, 0x3f, (n + 1) * sizeof(int));
    shortest[0] = 0;
    previous = new vector<int>[n + 1];
    for (int i = 0; i < n + 1; i++) {
        int v = -1;
        for (int u = 0; u < n + 1; u++) {
            if (!visited[u] && (v < 0 || shortest[u] < shortest[v])) {
                v = u;
            }
        }
        visited[v] = 1;
        for (int u = 0; u < n + 1; u++) {
            if (visited[u]) { continue; }
            if (shortest[u] > shortest[v] + graph[v][u]) {
                shortest[u] = shortest[v] + graph[v][u];
                previous[u].clear();
                previous[u].push_back(v);
            } else if (shortest[u] == shortest[v] + graph[v][u]) {
                previous[u].push_back(v);
            }
        }
    }
}

int minTake = 0x7f;
int minSend = 0x7f;
int *truePrevious;

bool dfs(int node, int take, int send) {
    if (node == 0) {
        if (take < minTake) {
            minTake = take;
            minSend = send;
            return true;
        } else if (take == minTake && send < minSend) {
            minSend = send;
            return true;
        }
        return false;
    }
    int cost = cmax / 2 - c[node];
    take += cost;
    if (take < 0) {
        send -= take;
        take = 0;
    }
    bool hasMin = false;
    for (auto pre : previous[node]) {
        if (dfs(pre, take, send)) {
            truePrevious[node] = pre;
            hasMin = true;
        }
    }
    return hasMin;
}

int main() {
    int m;
    scanf("%d %d %d %d", &cmax, &n, &sp, &m);
    c = (int *)malloc((n + 1) * sizeof(int));
    c[0] = 0;
    truePrevious = (int *)malloc((n + 1) * sizeof(int));
    graph = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i < n; i++) {
        scanf("%d", c + i + 1);
    }
    for (int i = 0; i < n + 1; i++) {
        graph[i] = (int *)malloc((n + 1) * sizeof(int));
        memset(graph[i], 0x3f, (n + 1) * sizeof(int));
    }
    for (int i = 0; i < m; i++) {
        int src, dst, d;
        scanf("%d %d %d", &src, &dst, &d);
        graph[src][dst] = d;
        graph[dst][src] = d;
    }

    dijkstra();
    dfs(sp, 0, 0);

    printf("%d ", minTake);

    int *route = (int *)malloc((n + 1) * sizeof(int));
    memset(route, 0, (n + 1) * sizeof(int));
    int index = 0;
    int current = sp;
    while (current != 0) {
        route[index] = current;
        current = truePrevious[current];
        index++;
    }
    printf("0");
    for (int i = 0; i < index; i++) {
        printf("->%d", route[index - i - 1]);
    }
    printf(" %d", minSend);

    return 0;
}