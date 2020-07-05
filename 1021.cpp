#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> *edges;
int n;

int maxHeight = 0;
vector<int> maxRoots;
int *visited;

void DFS(int root, int height, int &totalHeight) {
    visited[root] = 1;
    bool isEnd = true;
    for (auto next : edges[root]) {
        if (!visited[next]) {
            DFS(next, height + 1, totalHeight);
            isEnd = false;
        }
    }
    if (isEnd) {
        if (height > totalHeight) {
            totalHeight = height;
        }
    }
}

int components() {
    int component = 0;
    int totalHeight;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            component++;
            totalHeight = 0;
            DFS(i, 0, totalHeight);
        }
    }
    if (component == 1) {
        maxHeight = totalHeight;
        maxRoots.push_back(0);
        for (int root = 1; root < n; root++) {
            memset(visited, 0, n * sizeof(int));
            totalHeight = 0;
            DFS(root, 0, totalHeight);
            if (totalHeight > maxHeight) {
                maxHeight = totalHeight;
                maxRoots.clear();
                maxRoots.push_back(root);
            } else if (totalHeight == maxHeight) {
                maxRoots.push_back(root);
            }
        }
    }
    return component;
}

int main() {
    scanf("%d", &n);
    visited = (int *)malloc(n * sizeof(int));
    memset(visited, 0, n * sizeof(int));
    edges = new vector<int>[n];
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        edges[a - 1].push_back(b - 1);
        edges[b - 1].push_back(a - 1);
    }
    int component = components();
    if (component != 1) {
        printf("Error: %d components", component);
    } else {
        sort(maxRoots.begin(), maxRoots.end());
        printf("%d", maxRoots[0] + 1);
        for (int i = 1; i < maxRoots.size(); i++) {
            printf("\n%d", maxRoots[i] + 1);
        }
    }

    return 0;
}