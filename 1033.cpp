#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Station {
    int distance;
    double price;

    bool operator<(const struct Station &station) {
        return this->distance < station.distance;
    }
};

int main() {

    int cmax, d, n;
    double davg;
    scanf("%d %d %lf %d", &cmax, &d, &davg, &n);
    struct Station *stations = (struct Station *)malloc((n + 1) * sizeof(struct Station));
    stations[n] = (struct Station){
        .distance = d,
        .price = 0.0
    };

    for (int i = 0; i < n; i++) {
        int distance;
        double price;
        scanf("%lf %d", &price, &distance);

        stations[i] = (struct Station){
            .distance = distance,
            .price = price
        };
    }

    sort(stations, stations + n + 1);

    if (stations[0].distance != 0) {
        printf("The maximum travel distance = 0.00");
        return 0;
    }

    int current = 0;
    double total = 0.0;
    double tank = 0.0;
    while (current < n) {
        struct Station station = stations[current];
        current++;
        double maxCanDrive = davg * cmax;
        struct Station nextStation;
        while (current < n + 1) {
            nextStation = stations[current];
            if (nextStation.distance > station.distance + maxCanDrive) {
                current--;
                nextStation = stations[current];
                if (nextStation.distance == station.distance) {
                    printf("The maximum travel distance = %.2lf", station.distance + maxCanDrive);
                    return 0;
                } else {
                    total += (cmax - tank) * station.price;
                    tank = cmax - (nextStation.distance - station.distance) / davg;
                }
                break;
            }
            if (nextStation.price < station.price) {
                double nextDrive = nextStation.distance - station.distance;
                double needGas = nextDrive / davg - tank;
                if (needGas < 0) {
                    needGas = 0;
                }
                total += needGas * station.price;
                tank -= nextDrive / davg;
                if (tank < 0) {
                    tank = 0;
                }
                break;
            }
            current++;
        }
    }

    printf("%.2lf", total);

    return 0;
}
