#include "bigInt.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;
const double PI = acos(-1.0);




//check if a string is a valid number
//remove extra 0
bool check(string& s)
{
	int l = s.length();
	int st = l;
	for(int i = l-1;i >= 0;i --)
	{
		if(s[i] < '0' || s[i] > '9')
		{
			cerr << "Input invalid!" << endl;
			return false;
		}
		if(s[i] != '0') 
			st = i;
	}
	if(st == l) s = "0";
	else s = s.substr(st);
	return true;
}


bigInt::bigInt(){}

bigInt::bigInt(string s)
{
	if(check(s))
		num = s;
	else
		num = "0";
}


//get number of bigInt
string bigInt::getnum() const
{
	return num;
}


//set number of bigInt, if invalid set "0"
bool bigInt::setnum(string s)
{
	if(check(s))
	{
		num = s;
		return true;
	}
	num = "0";
	return false;
}


//print number
void bigInt::print() const
{
	cout << num << endl;
}


//used to implement multiply
int revv(int x, int bits)
{
    int ret = 0;
    for (int i = 0; i < bits; i++)
    {
        ret <<= 1;
        ret |= x & 1;
        x >>= 1;
    }
    return ret;
}

//used to implement multiply
void fft(double* a, double* b, int n, bool rev)
{
    int bits = 0;
    while ((1 << bits) < n) bits++;
    for (int i = 0; i < n; i++)
    {
        int j = revv(i, bits);
        if (i < j)
		{
            swap(a[i], a[j]);
			swap(b[i], b[j]);
		}
    }
    for (int len = 2; len <= n; len <<= 1)
    {
        int half = len >> 1;
        double wmx = cos(2 * PI / len), wmy = sin(2 * PI / len);
        if(rev) wmy = -wmy;
        for (int i = 0; i < n; i += len)
        {
            double wx = 1, wy = 0;
            for (int j = 0; j < half; j++)
            {
                double cx = a[i + j], cy = b[i + j];
                double dx = a[i + j + half], dy = b[i + j + half];
                double ex = dx * wx - dy * wy, ey = dx * wy + dy * wx;
                a[i + j] = cx + ex, b[i + j] = cy + ey;
                a[i + j + half] = cx - ex, b[i + j + half] = cy - ey;
                double wnx = wx * wmx - wy * wmy, wny = wx * wmy + wy * wmx;
                wx = wnx, wy = wny;
            }
        }
    }
    if (rev)
    {
        for (int i = 0; i < n; i++)
            a[i] /= n, b[i] /= n;
    }
}

//multiply 2 strings
string mult(string num, string s)
{
	int la = num.length();
	int lb = s.length();
	int len = max(la,lb);
	int l = 0;
	while((1 << l) < len) l ++;
	len = 1 << (l+1);
	double* ax = new double[len];
	double* bx = new double[len];
	double* ay = new double[len];
	double* by = new double[len];
	int* ans = new int[len];
	for(int i = 0;i < len;i ++)
	{
		if(i >= la)
			ax[i] = 0;
		else
			ax[i] = num[la-i-1]-'0';
		ay[i] = 0;
	}
	for(int i = 0;i < len;i ++)
	{
		if(i >= lb)
			bx[i] = 0;
		else
			bx[i] = s[lb-i-1]-'0';
		by[i] = 0;
	}

	fft(ax, ay, len, 0);
	fft(bx, by, len, 0);
	for (int i = 0; i < len; i++)
    {
        double cx = ax[i] * bx[i] - ay[i] * by[i];
        double cy = ax[i] * by[i] + ay[i] * bx[i];
        ax[i] = cx, ay[i] = cy;
    }

    fft(ax, ay, len, 1);
	for (int i = 0; i < len; i++)
        ans[i] = (int)(ax[i] + 0.5);
	
	for(int i = 0;i < len-1;i ++)
	{
		ans[i+1] += ans[i]/10;
		ans[i] %= 10;
	}
	int st = len;
	while(st >= 1)
	{
		if(ans[st-1] != 0) break;
		else st--;
	}
	if(st == 0) return "0";
	string res(st,0);
	for(int i = st-1;i >= 0;i --)
		res[st-i-1] = ans[i] + '0';
	delete[] ax;
	delete[] ay;
	delete[] bx;
	delete[] by;
	return res;
}

//add 2 strngs
string addition(string num, string s)
{
	int la = num.length();
	int lb = s.length();
	int l = max(la, lb);
	int carry = 0;
	string res(l,0);
	for(int i = 0;i < l;i ++)
	{
		int a,add;
		if(i < la) 
			a = num[la-1-i] - '0';
		else
			a = 0;
		if(i < lb) 
			add = carry + a + s[lb-1-i] - '0';
		else
			add = carry + a;
		res[l-1-i] = add % 10 + '0';
		carry = add / 10;
	}
	if(carry > 0) 
		res = "1" + res;
	return res;
}

//substract 2 strings, assert num >- s, or else return "-1"
string substract(string num, string s)
{
	int la = num.length();
	int lb = s.length();
	if(la < lb) return "-1";
	if(la == lb && num < s) return "-1";
	if(num == s) return "0";
	int carry = 0;
	for(int i = 0;i < lb;i ++)
	{
		num[la-1-i] = num[la-1-i] - s[lb-1-i] - carry + '0';
		if(num[la-1-i] < '0')
		{
			num[la-1-i] += 10;
			carry = 1;
		}
		else 
			carry = 0;
	}
	if(carry)
	{
		for(int i = lb;i < la;i ++)
		{
			if(num[la-1-i] == '0')
				num[la-1-i] = '9';
			else
			{
				num[la-1-i] -= 1;
				break;
			}
		}
	}
	int st = 0;
	while(st < la)
	{
		if(num[st] != '0') break;
		st ++;
	}
	num = num.substr(st);
	return num;
}
//divide 2 string, return if divide successfully
bool div(string num, string s, string& q, string& r)
{
	if(s == "0")
	{
		cerr << "Divisor cannot be zero!" << endl;
		return false;
	}
	int la = num.length();
	int lb = s.length();
	if((la < lb) || (la == lb && num < s))
	{
		q = "0";
		r = num;
		return true;
	}
	int l = la - lb + 1;
	string quotient(l, '0');
	string last = num.substr(0,lb-1);
	string stmp;
	for(int i = 0;i < l;i ++)
	{	
		stmp = last + num[lb+i-1];
		last = stmp;
		while((stmp = substract(stmp, s)) != "-1")
		{
			quotient[i] += 1;
			last = stmp;
			if(last == "0") last = "";
		}
	}
	q = (quotient[0] == '0' ? quotient.substr(1) : quotient);
	r = (last == "" ? "0":last);
	return true;
}

bigInt bigInt::operator * (const bigInt &b) const
{
	return bigInt(mult(num, b.getnum()));
}

bigInt bigInt::operator + (const bigInt &b) const
{
	return bigInt(addition(num, b.getnum()));
}

bigInt bigInt::operator - (const bigInt &b) const
{
	string s = substract(num, b.getnum());
	if(s == "-1") return bigInt("0");	
	return bigInt(s);
}

bigInt bigInt::operator / (const bigInt &b) const
{
	string q,r;
	if(div(num, b.getnum(), q, r))
		return bigInt(q);
	else
		return bigInt("0");
}

bigInt bigInt::operator % (const bigInt &b) const
{
	string q,r;
	if(div(num, b.getnum(), q, r))
		return bigInt(r);
	else
		return bigInt("0");
}

bool bigInt::operator == (const bigInt &b) const
{
	return num == b.getnum();
}

bool bigInt::operator > (const bigInt &b) const
{
	string s = b.getnum();
	return((num.length() > s.length()) || (num.length() == s.length() && num > s));
}

bool bigInt::operator < (const bigInt &b) const
{
	string s = b.getnum();
	return((num.length() < s.length()) || (num.length() == s.length() && num < s));
}

bool bigInt::operator >= (const bigInt &b) const
{
	string s = b.getnum();
	return((num.length() > s.length()) || (num.length() == s.length() && num >= s));
}

bool bigInt::operator <= (const bigInt &b) const
{
	string s = b.getnum();
	return((num.length() < s.length()) || (num.length() == s.length() && num <= s));
}

ostream& operator << (ostream& o, const bigInt& f)
{
	o << f.getnum();
	return o;
}
istream& operator >> (istream& i, bigInt& f)
{
	string s;
	i >> s;
	if(check(s))
		f.num = s;
	else
		f.num = "0";
	return i;
}

bigInt& bigInt::operator = (const bigInt &b) {
    this->num = b.num;
    return *this;
}
bigInt::bigInt(const bigInt &b) {
    this->num = b.num;
}

char tochar(string s)
{
	if((s.length()) == 1)
		return s[0];
	else
		return s[1] - '0' + 'a';
	
}

//convert a string in Dec to Hex
string toHex(string s)
{	
	if(check(s))
	{
		return "";
	}
	int l = s.length();
	string res = "";
	string q,r;
	div(s, "16", q, r);
	while(true)
	{
		res = string(1,tochar(r)) + res;
		if(q == "0") break;
		else
			div(q, "16", q, r);
	}
	return res;
}

string tostring(char c)
{
	string res = "10";
	if(c >= '0' && c <= '9')
		return (string(1, c));
	if(c >= 'a' && c <= 'f')
	{
		res[1] += (c -'a');
		return res;
	}
	if(c >= 'A' && c <= 'F')
	{
		res[1] += (c -'A');
		return res;
	}
	else return "0";
}

//convert a string in Hex to Dec
string toDec(string s)
{
	int l = s.length();
	string res = "0";
	for(int i = 0;i < l;i ++)
		res = addition(mult(res,"16"), tostring(s[i]));
	return res;
}
// return b/2
bigInt half(bigInt b)
{
	if(b < bigInt("2")) return bigInt("0");
	string n = b.getnum();
	int l = n.length();
	int remain = 0;
	for(int i = 0;i < l;i ++)
	{
		char c = n[i];
		n[i] = (remain * 10 + c-'0') / 2 + '0';
		remain = (remain * 10 + c-'0') % 2;
	}
	return bigInt(n[0] == '0' ? n.substr(1):n);
}

