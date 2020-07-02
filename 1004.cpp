#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <vector>
using namespace std;

int n;
int m;
vector<int> *nodes;
int *leafCount;
int totalHeight = 0;

void DFS(int node, int height) {
    if (height > totalHeight - 1) {
        totalHeight = height + 1;
    }
    if (nodes[node].empty()) {
        leafCount[height]++;
    } else {
        for (auto child : nodes[node]) {
            DFS(child, height + 1);
        }
    }
}

int main() {
    scanf("%d", &n);
    if (n == 0) {
        return 0;
    }
    scanf("%d", &m);

    nodes = new vector<int>[n];
    leafCount = (int *)malloc(n * sizeof(int));
    memset(leafCount, 0, n * sizeof(int));

    for (int node = 0; node < m; node++) {
        int index;
        scanf("%d", &index);
        int children;
        scanf("%d", &children);
        for (int child = 0; child < children; child++) {
            int childIndex;
            scanf("%d", &childIndex);
            nodes[index - 1].push_back(childIndex - 1);
        }
    }

    DFS(0, 0);
    for (int i = 0; i < totalHeight - 1; i++) {
        printf("%d ", leafCount[i]);
    }
    printf("%d", leafCount[totalHeight - 1]);

    return 0;
}