#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int sum = 0;
    int previous = 0;
    int target;
    while (n--) {
        scanf("%d", &target);
        if (target < previous) {
            sum += 4 * (previous - target);
        } else {
            sum += 6 * (target - previous);
        }
        sum += 5;
        previous = target;
    }
    printf("%d", sum);

    return 0;
}