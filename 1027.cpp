#include <iostream>
#include <iomanip>
using namespace std;

char radix[13] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C'};

int main() {
    int color[3];
    for (int i = 0; i < 3; i++) {
        cin >> color[i];
    }

    cout << "#";
    for (int i = 0; i < 3; i++) {
        cout << radix[color[i] / 13] << radix[color[i] % 13];
    }

    return 0;
}