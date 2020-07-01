#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

struct Entry {
    int exp;
    double coeff;
};

int ak;
struct Entry *a;
int bk;
struct Entry *b;

int ck = 0;
int clen;
double *c;

void computeSum() {
    clen = (a[0].exp > b[0].exp ? a[0].exp : b[0].exp) + 1;
    c = (double *)malloc(clen * sizeof(double));
    memset(c, 0, clen * sizeof(double));
    int apos = 0;
    int bpos = 0;
    while (apos < ak || bpos < bk) {
        int aexp = -1;
        int bexp = -1;
        if (apos < ak) {
            aexp = a[apos].exp;
        }
        if (bpos < bk) {
            bexp = b[bpos].exp;
        }

        if (aexp > bexp) {
            c[clen - aexp - 1] = a[apos].coeff;
            apos++;
        } else if (aexp == bexp) {
            double res = a[apos].coeff + b[bpos].coeff;
            c[clen - aexp - 1] = res;
            if (res == 0) {
                ck--;
            }
            apos++;
            bpos++;
        } else {
            c[clen - bexp - 1] = b[bpos].coeff;
            bpos++;
        }
        ck++;
    }
}

int main() {
    scanf("%d", &ak);
    a = (struct Entry *)malloc(ak * sizeof(struct Entry));
    for (int i = 0; i < ak; i++) {
        int exp;
        double coeff;
        scanf("%d %lf", &exp, &coeff);
        a[i] = (struct Entry){
            .exp = exp,
            .coeff = coeff
        };
    }
    scanf("%d", &bk);
    b = (struct Entry *)malloc(bk * sizeof(struct Entry));
    for (int i = 0; i < bk; i++) {
        int exp;
        double coeff;
        scanf("%d %lf", &exp, &coeff);
        b[i] = (struct Entry){
            .exp = exp,
            .coeff = coeff
        };
    }

    computeSum();

    printf("%d", ck);
    for (int i = 0; i < clen; i++) {
        if (c[i] != 0.0) {
            printf(" %d %.1lf", clen - i - 1, c[i]);
        }
    }
    return 0;
}