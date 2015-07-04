#ifndef BIGINT_H
#define BIGINT_H
#include <string>
#include <iostream>

class bigInt
{
private:
	std::string num;
public:
	std::string getnum() const;
	bool setnum(std::string s);
	void print() const;
	bigInt operator * (const bigInt&) const;
	bigInt operator / (const bigInt&) const;
	bigInt operator % (const bigInt&) const;
	bigInt operator + (const bigInt&) const;
	bigInt operator - (const bigInt&) const;
	bool operator == (const bigInt&) const;
	bool operator > (const bigInt&) const;
	bool operator < (const bigInt&) const;
	bool operator >=  (const bigInt&) const;
	bool operator <= (const bigInt&) const;
    bigInt& operator = (const bigInt&);
	friend std::ostream& operator << (std::ostream&, const bigInt&);
    friend std::istream& operator >> (std::istream&, bigInt&);
	bigInt(std::string);
	bigInt(const bigInt &);
    bigInt();
};

std::string toHex(std::string);
std::string toDec(std::string);
bigInt half(bigInt b);

#endif
