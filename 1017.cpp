#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <queue>

int k;
int n;
int *latest;
int sum = 0;

void findEarliest(int &window, int &time) {
    window = 0;
    time = latest[window];
    for (int i = 0; i < k; i++) {
        if (latest[i] < time) {
            window = i;
            time = latest[i];
        }
    }
}

struct Person {
    int arriveTime;
    int lasting;

    bool operator<(const Person& a) const
    {
        return this->arriveTime > a.arriveTime;
    }
};

void updateSum(struct Person person) {
    int window, time;
    findEarliest(window, time);
    int arriveTime = person.arriveTime;
    int finishTime;
    int waitingTime;
    if (arriveTime < time) {
        finishTime = time + person.lasting * 60;
        waitingTime = time - arriveTime;
    } else {
        finishTime = arriveTime + person.lasting * 60;
        waitingTime = 0;
    }
    sum += waitingTime;
    latest[window] = finishTime;
}

int main() {
    scanf("%d", &n);
    scanf("%d", &k);

    latest = (int *)malloc(n * sizeof(int));
    memset(latest, 0, n * sizeof(int));

    std::priority_queue<Person> persons;
    int trueCount = 0;

    for (int person = 0; person < n; person++) {
        int h, m, s, t;
        scanf("%d:%d:%d %d", &h, &m, &s, &t);
        if (h > 17 || (h == 17 && (m > 0 || (m == 0 && t > 1)))) {

        } else {
            trueCount++;
            int arriveTime = (h - 8) * 3600 + m * 60 + s;
            Person person = (Person) {
                .arriveTime = arriveTime,
                .lasting = t
            };
            persons.push(person);
        }
    }

    while (!persons.empty()) {
        updateSum(persons.top());
        persons.pop();
    }
    printf("%.1lf", (double)sum / (60 * trueCount));
    return 0;
}