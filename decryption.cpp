#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "bigInt.h"
#include "gcd.h"
#include "mrTest.h"
#include "power.h"
#include "random.h"

using namespace std;

bigInt string2bigInt(string s)
{
	bigInt b("0");
	int l = s.length();
	for(int i = 0;i < l;i ++)
	{
		int n = s[i];
		string num(3,'0');
		num[2] += n%10;
		num[1] += (n/10)%10;
		num[0] += (n/100)%10;
		b = b * bigInt("128") + bigInt(num);
	}
	return b;
}

string bigInt2string(bigInt b)
{
	bigInt mod("128");
	string res = "";
	while(b > bigInt("0"))
	{
		
		string s = (b % mod).getnum();
		b = b / mod;
		char c = 0;
		int l = s.length();
		for(int i = 0;i < l;i ++)
			c = c * 10 + s[i]-'0';
		//cout << c << endl;
		string tmp(1,c);
		res = c + res;
	}
	return res;
}

int main()
{
	string s;
	cin >> s;
	bigInt c(s);
	bigInt d,n;
	ifstream i("prikey.txt");
	i >> n >> d;
	i.close();
	clock_t start, finish;
	cout << "decrypting..." << endl;
	start = clock();
	bigInt text = power(c,d,n);
	cout << "plain is:" << text << endl; 
	cout << "text is:" << bigInt2string(text) << endl;
	finish = clock();
	cout << "decryption costs " << finish-start << endl;
 	return 0;
}
