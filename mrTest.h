#ifndef MRTEST_H
#define MRTEST_H
#include "bigInt.h"
#include "power.h"
#include "random.h"

string primes[24] = {"3","5","7","11","13","17","19","23","29","31","37","41","43","47","53","59","61","67","71","73","79","83","89","97"};

string randb[10] = {"5","9","21","1227","1357","47","67","89","97","111"};


bool mrTest(bigInt b)
{
	if(b == bigInt("2")) return true;
	if(!isodd(b)) return false;
	int j = 0;
	for(int i = 0;i < 24;i ++)
		if(b % bigInt(primes[i]) == bigInt("0"))
			return false;
	bigInt m = b - bigInt("1");
	while(!isodd(m))
	{
		j ++;
		m = half(m);
	}
	//cout << m << " " << j << endl;
	for(int i = 0;i < 5;i ++)
	{
		//cout << "No." << i << " testing..." << endl;
		bigInt k(randb[i]);
		bigInt v = power(k,m,b);
		if(v == bigInt("1")) continue;
		bigInt testnum = b-bigInt("1");
		int n = 1;
		while(true)
		{
			//cout << n << endl;
			if(v == testnum) break;
			if(n == j) return false;
			v = (v*v) % b;
			n ++;
		}
		
	}
	return true;
}

bigInt createprime()
{
	bigInt max("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084096");
	while(true)
	{
		bigInt b = random(512);
		//cout << b << endl;
		for(;b < max;b = b + bigInt("2"))
		{
			if(mrTest(b)) return b;
		}
	}
}


#endif