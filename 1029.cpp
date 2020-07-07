#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main() {
    vector<long int> sequence;
    int n1, n2;
    scanf("%d", &n1);
    for (int i = 0; i < n1; i++) {
        long int number;
        scanf("%ld", &number);
        sequence.push_back(number);
    }
    scanf("%d", &n2);
    for (int i = 0; i < n2; i++) {
        long int number;
        scanf("%ld", &number);
        sequence.push_back(number);
    }

    int length = sequence.size() - 1;
    sort(sequence.begin(), sequence.end());
    printf("%lu", sequence[length / 2]);

    return 0;
}
