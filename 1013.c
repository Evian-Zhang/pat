#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int n;
int **remaining;
int *visited;

void DFS(int node, int lost) {
    visited[node] = 1;
    for (int i = 0; i < n; i++) {
        if (remaining[node][i] && !visited[i] && i != lost) {
            DFS(i, lost);
        }
    }
}

int connectedGraphs(int lost) {
    int sum = 0;
    memset(visited, 0, n * sizeof(int));
    for (int node = 0; node < n; node++) {
        if (node == lost) {
            continue;
        }
        if (!visited[node]) {
            sum++;
            DFS(node, lost);
        }
    }
    return sum;
}

int main() {
    int m, k;
    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &k);
    remaining = (int **)malloc(n * sizeof(int *));
    visited = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        remaining[i] = (int *)malloc(n * sizeof(int));
        memset(remaining[i], 0, n * sizeof(int));
    }
    for (int line = 0; line < m; line++) {
        int i, j;
        scanf("%d %d", &i, &j);
        remaining[i - 1][j - 1] = 1;
        remaining[j - 1][i - 1] = 1;
    }

    for (int line = 0; line < k; line++) {
        int lost;
        scanf("%d", &lost);
        printf("%d\n", connectedGraphs(lost - 1) - 1);
    }

    return 0;
}