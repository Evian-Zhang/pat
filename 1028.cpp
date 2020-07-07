#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Record {
    string id;
    string name;
    int score;
};

struct IDCmp {
    bool operator()(const struct Record &a, const struct Record &b) {
        return a.id.compare(b.id) > 0;
    }
};

struct NameCmp {
    bool operator()(const struct Record &a, const struct Record &b) {
        if (a.name.compare(b.name) != 0) {
            return a.name.compare(b.name) > 0;
        } else {
            return a.id.compare(b.id) > 0;
        }
    }
};

struct ScoreCmp {
    bool operator()(const struct Record &a, const struct Record &b) {
        if (a.score != b.score) {
            return a.score > b.score;
        } else {
            return a.id.compare(b.id) > 0;
        }
    }
};

int main() {
    int n;
    scanf("%d", &n);
    int c;
    scanf("%d", &c);
    getchar();
    switch (c) {
        case 1: {
            priority_queue<struct Record, vector<struct Record>, IDCmp> records;
            for (int i = 0; i < n; i++) {
                string id, name;
                int score;
                cin >> id >> name >> score;
                records.push((struct Record){
                    .id = id,
                    .name = name,
                    .score = score
                });
            }

            struct Record record = records.top();
            records.pop();
            cout << record.id << " " << record.name << " " << record.score;
            while (!records.empty()) {
                struct Record record = records.top();
                records.pop();
                cout << "\n" << record.id << " " << record.name << " " << record.score;
            }
            break;
        };
        case 2: {
            priority_queue<struct Record, vector<struct Record>, NameCmp> records;
            for (int i = 0; i < n; i++) {
                string id, name;
                int score;
                cin >> id >> name >> score;
                records.push((struct Record){
                    .id = id,
                    .name = name,
                    .score = score
                });
            }

            struct Record record = records.top();
            records.pop();
            cout << record.id << " " << record.name << " " << record.score;
            while (!records.empty()) {
                struct Record record = records.top();
                records.pop();
                cout << "\n" << record.id << " " << record.name << " " << record.score;
            }
            break;
        };
        case 3: {
            priority_queue<struct Record, vector<struct Record>, ScoreCmp> records;
            for (int i = 0; i < n; i++) {
                string id, name;
                int score;
                cin >> id >> name >> score;
                records.push((struct Record){
                    .id = id,
                    .name = name,
                    .score = score
                });
            }

            struct Record record = records.top();
            records.pop();
            cout << record.id << " " << record.name << " " << record.score;
            while (!records.empty()) {
                struct Record record = records.top();
                records.pop();
                cout << "\n" << record.id << " " << record.name << " " << record.score;
            }
            break;
        };
    }

    return 0;
}