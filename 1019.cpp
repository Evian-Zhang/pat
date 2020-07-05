#include <cstdio>
#include <vector>
using namespace std;

int main() {
    int n, b;
    scanf("%d %d", &n, &b);
    if (n == 0) {
        printf("Yes\n0");
    }
    vector<int> digits;
    while (n >= 1) {
        digits.push_back(n % b);
        n /= b;
    }
    int length = digits.size();
    bool isPalindromic = true;
    for (int i = 0; i < length; i++) {
        if (digits[i] != digits[length - i - 1]) {
            isPalindromic = false;
        }
    }
    if (isPalindromic) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    printf("%d", digits[length - 1]);
    for (int i = 1; i < length; i++) {
        printf(" %d", digits[length - i - 1]);
    }

    return 0;
}