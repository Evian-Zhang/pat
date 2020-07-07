#include <stdio.h>
#include <stdlib.h>

struct Node {
    int next;
    int isVisited;
};

int main() {
    int start1, start2, n;
    scanf("%d %d %d", &start1, &start2, &n);
    struct Node nodes[100000];
    for (int i = 0; i < n; i++) {
        int addr, next;
        char ch;
        scanf("%d %c %d", &addr, &ch, &next);

        nodes[addr] = (struct Node){
            .next = next,
            .isVisited = 0
        };
    }

    int current = start1;
    while (current != -1) {
        nodes[current].isVisited = 1;
        current = nodes[current].next;
    }
    current = start2;
    while (current != -1) {
        struct Node node = nodes[current];
        if (node.isVisited) {
            printf("%05d", current);
            return 0;
        }
        current = node.next;
    }

    printf("-1");

    return 0;
}