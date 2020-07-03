#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <queue>
using namespace std;

struct Wait {
    int finish;
    int window;

    bool operator<(const struct Wait &it) const {
        return this->finish > it.finish || (this->finish == it.finish && this->window > it.window);
    }
};

int main() {
    int n, m, k, q;
    scanf("%d %d %d %d", &n, &m, &k, &q);
    int *finish = (int *)malloc(k * sizeof(int));
    int *current = (int *)malloc(n * sizeof(int));
    memset(current, 0, n * sizeof(int));

    priority_queue<struct Wait> customers;

    for (int i = 0; i < k; i++) {
        int process;
        scanf("%d", &process);
        if (i < n * m) {
            // Test point 4: Someone is too long who in the first NM people
            if (current[i % n] >= 540) {
                finish[i] = -1;
                continue;
            }
            current[i % n] += process;
            finish[i] = current[i % n];
            customers.push((struct Wait){
                .finish = finish[i],
                .window = i % n
            });
        } else {
            if (customers.empty()) {
                finish[i] = -1;
                continue;
            }
            struct Wait wait = customers.top();
            customers.pop();
            if (current[wait.window] >= 540) {
                finish[i] = -1;
            } else {
                current[wait.window] += process;
                finish[i] = current[wait.window];
                customers.push((struct Wait){
                    .finish = finish[i],
                    .window = wait.window
                });
            }
        }
    }

    for (int i = 0; i < q; i++) {
        int custom;
        scanf("%d", &custom);
        int finishTime = finish[custom - 1];
        if (finishTime >= 0) {
            printf("%02d:%02d\n", finishTime / 60 + 8, finishTime % 60);
        } else {
            printf("Sorry\n");
        }
    }

    return 0;
}