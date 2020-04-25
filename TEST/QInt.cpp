#include "QInt.h"

QInt::QInt()
{
	data[0] = data[1] = data[2] = data[3] = 0;
}

QInt::~QInt()
{

}

/*
QInt& QInt::operator = (const string& x)
{
	return 
}*/

int QInt::divBy2(string &s)
{
	int r = 0;
	int q = 0;

	for (int i = 0; i < s.size(); i++)
	{
		int d = s[i] - '0';

		if (d < 2)
		{
			r = r + d * 10;
		}
		else
		{
			r = r + d;
			r = r % 2;
			q = q * 10 + r / 2;
		}
	}

	s = q;

	return r;
}

istream& operator >> (istream& input, QInt& x)
{
	string s;

	input >> s;

	// x = s;

	return input;
}