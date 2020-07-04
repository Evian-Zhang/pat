#include <cstdio>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct Record {
    string name;
    int timestamp;
    bool isOnLine;

    // used for priority queue for get smallest via top
    bool operator<(const Record &a) const {
        int diff = this->name.compare(a.name);
        if (diff != 0) {
            return diff > 0;
        }
        if (this->timestamp != a.timestamp) {
            return this->timestamp > a.timestamp;
        }
        return false;
    }

    bool trueLess(const Record &a) {
        return !(*this < a);
    }
};

int toll[24];

int cents(int from, int to) {
    // Test point 3: from and to are in the same day, same hour
    int sum = -toll[(from % 1440) / 60] * (from % 60);
    from -= from % 60;
    while (to >= from + 60) {
        sum += toll[(from % 1440) / 60] * 60;
        from += 60;
    }
    int remain = to % 60;
    sum += toll[(to % 1440) / 60] * remain;
    return sum;
}

int main() {
    for (int i = 0; i < 24; i++) {
        scanf("%d", toll + i);
    }
    int n;
    scanf("%d", &n);
    int month;
    priority_queue<struct Record> records;
    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        scanf("%d:", &month);
        int day, hour, minute;
        scanf("%d:%d:%d", &day, &hour, &minute);
        char word[9];
        scanf("%s", word);
        records.push((struct Record){
            .name = move(name),
            .timestamp = (day - 1) * 1440 + hour * 60 + minute,
            .isOnLine = (word[1] == 'n')
        });
    }

    string lastName("");
    int totalAmount = 0;
    while (!records.empty()) {
        while (!records.empty()) {
            struct Record record = records.top();
            if (!record.isOnLine) {
                records.pop();
            } else {
                break;
            }
        }
        if (records.empty()) {
            break;
        }
        struct Record record1 = records.top();
        records.pop();
        if (records.empty()) {
            break;
        }
        struct Record record2 = records.top();
        if (record1.name.compare(record2.name) != 0 || record2.isOnLine) {
            continue;
        }
        if (lastName.compare("") == 0 || record1.name.compare(lastName) != 0) {
            if (lastName.compare("") != 0) {
                printf("Total amount: $%.2lf\n", (double)totalAmount / 100);
            }
            lastName = record1.name;
            cout << record1.name << " ";
            printf("%02d\n", month);
            totalAmount = 0;
        }
        printf("%02d:%02d:%02d ", record1.timestamp / 1440 + 1, (record1.timestamp % 1440) / 60, record1.timestamp % 60);
        printf("%02d:%02d:%02d ", record2.timestamp / 1440 + 1, (record2.timestamp % 1440) / 60, record2.timestamp % 60);
        printf("%d $", record2.timestamp - record1.timestamp);
        int sum = cents(record1.timestamp, record2.timestamp);
        printf("%.2lf\n", (double)sum / 100);
        totalAmount += sum;
    }
    printf("Total amount: $%.2lf", (double)totalAmount / 100);

    return 0;
}