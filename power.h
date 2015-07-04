#ifndef POWER_H
#define POWER_H

#include "bigInt.h"
#include <string>

using namespace std;


bool isodd(bigInt b)
{
	string s = b.getnum();
	return s[s.length()-1]%2;
}
//a^b % m
bigInt power(bigInt a, bigInt b, bigInt m)
{
	if(b == bigInt("0")) return bigInt("1");
	if(b == bigInt("1")) return a % m;
	bigInt hb = half(b);
	bigInt phb = power(a, hb, m);
	bigInt res = (phb * phb) % m;
	if(isodd(b))
		res = (a * res) % m;
	return res;
}

#endif