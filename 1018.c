#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int cmax;
int n;
int sp;
int *c;
int **graph;
int *visited;
int *shortest;
int *bikeCost;
int *bikeGet;
int *previous;

void dijkstra() {
    visited = (int *)malloc((n + 1) * sizeof(int));
    memset(visited, 0, (n + 1) * sizeof(int));
    // visited[0] = 1;
    shortest = (int *)malloc((n + 1) * sizeof(int));
    memset(shortest, 0x3f, (n + 1) * sizeof(int));
    shortest[0] = 0;
    bikeCost = (int *)malloc((n + 1) * sizeof(int));
    memset(bikeCost, 0x3f, (n + 1) * sizeof(int));
    bikeCost[0] = 0;
    bikeGet = (int *)malloc((n + 1) * sizeof(int));
    bikeGet[0] = 0;
    previous = (int *)malloc((n + 1) * sizeof(int));
    memset(previous, 0, (n + 1) * sizeof(int));
    for (int i = 0; i < n + 1; i++) {
        int v = -1;
        for (int u = 0; u < n + 1; u++) {
            if (!visited[u] && (v < 0 || shortest[u] < shortest[v])) {
                v = u;
            }
        }
        visited[v] = 1;
        for (int u = 0; u < n + 1; u++) {
            if (u == v) { continue; }
            if (shortest[u] > shortest[v] + graph[v][u]) {
                shortest[u] = shortest[v] + graph[v][u];
                if (u != 0) {
                    bikeGet[u] = bikeGet[v] - (cmax / 2 - c[u]);
                    if (bikeGet[u] < 0) {
                        bikeCost[u] = bikeCost[v] - bikeGet[u];
                        bikeGet[u] = 0;
                    } else {
                        bikeCost[u] = bikeCost[v];
                    }
                    previous[u] = v;
                }
            } else if (shortest[u] == shortest[v] + graph[v][u]) {
                if (u != 0) {
                    int tmpGet = bikeGet[v] - (cmax / 2 - c[u]);
                    int tmpCost = bikeCost[v];
                    if (tmpGet < 0) {
                        tmpCost = bikeCost[v] - tmpGet;
                        tmpGet = 0;
                    }
                    if (tmpCost < bikeCost[u]) {
                        bikeCost[u] = tmpCost;
                        bikeGet[u] = tmpGet;
                        previous[u] = v;
                    }
                }
            }
        }
    }
}

int main() {
    int m;
    scanf("%d %d %d %d", &cmax, &n, &sp, &m);
    c = (int *)malloc((n + 1) * sizeof(int));
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

    if (bikeCost[sp] > 0) {
        printf("%d ", bikeCost[sp]);
    } else {
        printf("0 ");
    }

    int *route = (int *)malloc((n + 1) * sizeof(int));
    memset(route, 0, (n + 1) * sizeof(int));
    int index = 0;
    int current = sp;
    while (current != 0) {
        route[index] = current;
        current = previous[current];
        index++;
    }
    printf("0");
    for (int i = 0; i < index; i++) {
        printf("->%d", route[index - i - 1]);
    }
    if (bikeCost[sp] < 0) {
        printf(" %d", -bikeCost[sp]);
    } else {
        printf(" 0");
    }

    return 0;
}