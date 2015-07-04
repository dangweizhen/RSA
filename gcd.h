#include "bigInt.h"

bigInt gcd(const bigInt& a, const bigInt& b) {
    if (a > b) return gcd(b, a);
    if (a == bigInt("0")) return b;
    return gcd(b % a, a);
}

