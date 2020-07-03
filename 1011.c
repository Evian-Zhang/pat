#include <stdio.h>

struct Game {
    double W;
    double T;
    double L;
};

void bestOfGame(struct Game *game, char *ch, double *odd) {
    *ch = 'W';
    *odd = game->W;
    if (game->T > *odd) {
        *ch = 'T';
        *odd = game->T;
    }
    if (game->L > *odd) {
        *ch = 'L';
        *odd = game->L;
    }
}

int main() {
    double W, T, L;
    struct Game game;
    double sum = 1.0;
    for (int i = 0; i < 3; i++) {
        scanf("%lf %lf %lf", &W, &T, &L);
        game = (struct Game){
            .W = W,
            .T = T,
            .L = L
        };
        char ch;
        double odd;
        bestOfGame(&game, &ch, &odd);
        printf("%c ", ch);
        sum *= odd;
    }
    sum *= 0.65;
    printf("%.2lf", (sum - 1) * 2);

    return 0;
}