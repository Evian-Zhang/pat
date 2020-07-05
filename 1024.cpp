#include <cstdio>
#include <deque>
using namespace std;

void getDoub(deque<int> &number, deque<int> &doubNumber) {
    int carry = 0;
    int length = number.size();
    for (int i = 0; i < length; i++) {
        int res = number[i] + number[length - i - 1] + carry;
        carry = res / 10;
        res %= 10;
        doubNumber.push_front(res);
    }
    if (carry > 0) {
        doubNumber.push_front(carry);
    }
}

bool isPalindromic(deque<int> &number) {
    int length = number.size();
    for (int i = 0; i < length; i++) {
        if (number[i] != number[length - i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    deque<int> number;
    char ch;
    while (scanf("%c", &ch) != EOF) {
        if (ch >= '0' && ch <= '9') {
            number.push_back(ch - '0');
        } else {
            break;
        }
    }
    int maxCount;
    scanf("%d", &maxCount);
    deque<int> doubNumber;
    int count = 0;
    while (!isPalindromic(number) && count < maxCount) {
        count++;
        doubNumber.clear();
        getDoub(number, doubNumber);
        number = doubNumber;
    }
    for (int digit : number) {
        printf("%d", digit);
    }
    printf("\n%d", count);

    return 0;
}