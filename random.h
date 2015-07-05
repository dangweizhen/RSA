#ifndef RANDOM_H
#define RANDOM_H
#include "bigInt.h"
#include "power.h"
#include <ctime>
#include <cstdlib>

void setRandom(unsigned seed) {
    srand(seed);
}


bigInt random(int len) {
    if (len == 0) return bigInt("0");
    if (len == 1) return bigInt("1");
    bigInt x("1");
    for (int i = 1; i < len; i ++) x = x * bigInt("2");;
    string s(len, '0');
    for (int i = 0; i < s.length(); i ++) 
        s[i] += rand() % 10;
    bigInt res = bigInt(s) % x + x;
    if (res % bigInt("2") == bigInt("0")) 
        return res + bigInt("1");
    else
        return res;
}
#endif