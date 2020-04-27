#include "QInt.h"

void QInt::OffBit()
{
	data[0] = data[1] = data[2] = data[3] = 0;
}

void QInt::SetBit(int i)
{
	int &block = data[3 - i / 32];
	int index = i % 32;
	block = block | (1 << index);
}

bool QInt::GetBit(int i)
{
	int block = data[3 - i / 32];
	int index = i % 32;
	int bit = 1 & (block >> index);
	return bit;
}

void QInt::ScanBinString(string s)
{
	OffBit();

	int k = 0;

	for (int i = s.size() - 1; i >= 0; i--)
	{
		if (s[i] == '1') SetBit(k);
		k = k + 1;
	}
}

void QInt::ScanDecString(string s)
{
	int k = 0;

	while (s != "")
	{
		bool bit = DivideByTwo(s);
		if (bit) SetBit(k);
	}
}

bool QInt::DivideByTwo(string& s)
{
	int r = 0;

	string q = "";

	for (int i = 0; i < s.length(); i++)
	{
		r = r * 10 + s[i] - '0';

		char c = r / 2 + '0';

		if (q != "" || c != '0') 
			q = q + c;

		r = r % 2;
	}

	s = q;

	return r;
}

void QInt::MultiplyByTwo(string& s)
{
	int c = 0;

	string p = "";

	for (int i = s.size() - 1; i >= 0; i--)
	{
		int t = 2 * (s[i] - '0');

		char d = c + t % 10 + '0';

		c = t / 10;

		p = d + p;
	}

	if (c != 0)
	{
		char d = c + '0';
		p = d + p;
	}

	if (p == "") p = "1";

	s = p;
}

void QInt::StringSum(string& s)
{
	string a = s;

	string z = "";

	int c = 0;

	MultiplyByTwo(s);

	while (a.size() < s.size()) a = '0' + a;

	for (int i = s.size() - 1; i >= 0; i--)
	{
		int t = (s[i] - '0') + (a[i] - '0');

		char d = c + t % 10 + '0';

		c = t / 10;

		z = d + z;
	}

	s = z;
}

string QInt::GetDecString()
{
	string s = "";

	for (int i = 0; i < 128; i++)
	{
		bool bit = GetBit(i);

		bit ? StringSum(s) : MultiplyByTwo(s);
	}

	return s;
}

string QInt::GetBinString()
{
	string s = "";

	for (int i = 0; i < 128; i++)
	{
		bool bit = GetBit(i);

		bit ? s = '1' + s : s = '0' + s;
	}

	return s;
}