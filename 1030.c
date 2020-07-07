#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int n;
int s;
int d;
int **graph;
int **costs;
int *previous;

void dijkstra() {
    int *visited = (int *)malloc(n * sizeof(int));
    memset(visited, 0, n * sizeof(int));
    int *shortest = (int *)malloc(n * sizeof(int));
    memset(shortest, 0x3f, n * sizeof(int));
    shortest[s] = 0;
    int *cheapest = (int *)malloc(n * sizeof(int));
    memset(cheapest, 0x3f, n * sizeof(int));
    cheapest[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int u = 0; u < n; u++) {
            if (!visited[u] && (v < 0 || shortest[u] < shortest[v])) {
                v = u;
            }
        }
        visited[v] = 1;
        for (int u = 0; u < n; u++) {
            if (visited[u]) { continue; }
            if (shortest[u] > shortest[v] + graph[v][u]) {
                shortest[u] = shortest[v] + graph[v][u];
                cheapest[u] = cheapest[v] + costs[v][u];
                previous[u] = v;
            } else if (shortest[u] == shortest[v] + graph[v][u]) {
                if (cheapest[u] > cheapest[v] + costs[v][u]) {
                    cheapest[u] = cheapest[v] + costs[v][u];
                    previous[u] = v;
                }
            }
        }
    }
}

int main() {
    int m;
    scanf("%d %d %d %d", &n, &m, &s, &d);
    graph = (int **)malloc(n * sizeof(int *));
    costs = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        graph[i] = (int *)malloc(n * sizeof(int));
        costs[i] = (int *)malloc(n * sizeof(int));
        memset(graph[i], 0x3f, n * sizeof(int));
    }
    previous = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < m; i++) {
        int a, b, distance, cost;
        scanf("%d %d %d %d", &a, &b, &distance, &cost);
        graph[a][b] = distance;
        graph[b][a] = distance;
        costs[a][b] = cost;
        costs[b][a] = cost;
    }

    dijkstra();

    int *path = (int *)malloc(n * sizeof(int));
    int current = d;
    int index = 0;
    while (current != s) {
        path[index] = current;
        current = previous[current];
        index++;
    }

    int totalDistance = 0;
    int totalCost = 0;

    printf("%d ", s);
    int prev = s;

    for (int i = 0; i < index; i++) {
        printf("%d ", path[index - i - 1]);
        totalDistance += graph[prev][path[index - i - 1]];
        totalCost += costs[prev][path[index - i - 1]];
        prev = path[index - i - 1];
    }
    printf("%d %d", totalDistance, totalCost);

    return 0;
}