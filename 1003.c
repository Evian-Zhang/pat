#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int n;
int m;
int c1, c2;
int *rescue;
int **d;

int *visited;
int *shortest;
int *totalPaths;
int *maxRescue;

void dijkstra() {
    visited = (int *)malloc(n * sizeof(int));
    memset(visited, 0, n * sizeof(int));
    shortest = (int *)malloc(n * sizeof(int));
    memset(shortest, 0x3f, n * sizeof(int));
    shortest[c1] = 0;
    totalPaths = (int *)malloc(n * sizeof(int));
    memset(totalPaths, 0, n * sizeof(int));
    totalPaths[c1] = 1;
    maxRescue = (int *)malloc(n * sizeof(int));
    memset(maxRescue, 0, n * sizeof(int));
    maxRescue[c1] = rescue[c1];

    for (int v = 0; v < n; v++) {
        int v0 = -1;
        for (int u = 0; u < n; u++) {
            if (!visited[u] && (v0 == -1 || shortest[u] < shortest[v0])) {
                v0 = u;
            }
        }
        visited[v0] = 1;
        for (int u = 0; u < n; u++) {
            if (u == v0) continue;
            if (shortest[u] == shortest[v0] + d[v0][u]) {
                totalPaths[u] += totalPaths[v0];
                maxRescue[u] = 
                    maxRescue[u] > maxRescue[v0] + rescue[u]
                        ? maxRescue[u]
                            : maxRescue[v0] + rescue[u];
            } else if (shortest[u] > shortest[v0] + d[v0][u]) {
                shortest[u] = shortest[v0] + d[v0][u];
                totalPaths[u] = totalPaths[v0];
                maxRescue[u] = maxRescue[v0] + rescue[u];
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &c1, &c2);
    rescue = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", rescue + i);
    }
    d = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        d[i] = (int *)malloc(n * sizeof(int));
        memset(d[i], 0x3f, n * sizeof(int));
        d[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int src, dst, len;
        scanf("%d %d %d", &src, &dst, &len);
        d[src][dst] = len;
        d[dst][src] = len;
    }

    dijkstra();

    printf("%d %d", totalPaths[c2], maxRescue[c2]);

    return 0;
}