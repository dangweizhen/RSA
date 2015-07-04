#include "bigInt.h"

bigInt gcd(bigInt a, bigInt b) {
    if (a > b) return gcd(b, a);
    if (a == bigInt("0")) return b;
    return gcd(b % a, a);
}

void extendedEuclidean(bigInt a, bigInt b, bigInt &x, bigInt &y, const bigInt& m) {
    if (a == bigInt("0")) {
        x = bigInt("0"), y = bigInt("1");
        return;
    }
    bigInt c = b / a, d = b % a;
    extendedEuclidean(d, a, y, x, m);
    x = (x + m - (c * y) % m) % m;  //to prevent an sub overflow
}

bigInt inv(bigInt a, bigInt mod) {
    if (!(gcd(a, mod) == bigInt("1"))) return bigInt("0");
    bigInt x, y;
    a = a % mod;
    extendedEuclidean(a, mod, x, y, mod);
    return x;
}

