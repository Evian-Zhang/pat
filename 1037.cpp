#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    vector<long int> positiveCoupons;
    vector<long int> negativeCoupons;
    int n1;
    scanf("%d", &n1);
    while (n1--) {
        long int coupon;
        scanf("%ld", &coupon);
        if (coupon >= 0) {
            positiveCoupons.push_back(coupon);
        } else {
            negativeCoupons.push_back(-coupon);
        }
    }
    sort(positiveCoupons.begin(), positiveCoupons.end());
    sort(negativeCoupons.begin(), negativeCoupons.end());

    vector<long int> positiveProducts;
    vector<long int> negativeProducts;
    int n2;
    scanf("%d", &n2);
    while (n2--) {
        long int product;
        scanf("%ld", &product);
        if (product >= 0) {
            positiveProducts.push_back(product);
        } else {
            negativeProducts.push_back(-product);
        }
    }
    sort(positiveProducts.begin(), positiveProducts.end());
    sort(negativeProducts.begin(), negativeProducts.end());

    int positiveCouponPos = 0;
    int negativeCouponPos = 0;
    int positiveProductPos = 0;
    int negativeProductPos = 0;

    long int sum = 0;
    while (positiveCouponPos < positiveCoupons.size() && positiveProductPos < positiveProducts.size()) {
        sum += positiveCoupons[positiveCouponPos++] * positiveProducts[positiveProductPos++];
    }
    while (negativeCouponPos < negativeCoupons.size() && negativeProductPos < negativeProducts.size()) {
        sum += negativeCoupons[negativeCouponPos++] * negativeProducts[negativeProductPos++];
    }

    int negativeProductPos2 = negativeProducts.size() - 1;
    while (positiveCouponPos < positiveCoupons.size() && negativeProductPos2 >= negativeProductPos) {
        sum -= positiveCoupons[positiveCouponPos++] * negativeProducts[negativeProductPos2--];
    }
    int positiveProductPos2 = positiveProducts.size() - 1;
    while (negativeCouponPos < negativeCoupons.size() && positiveProductPos2 >= positiveProductPos) {
        sum -= negativeCoupons[negativeCouponPos++] * positiveProducts[positiveProductPos2--];
    }

    printf("%ld", sum);

    return 0;
}