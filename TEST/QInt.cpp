#include "QInt.h"
//by Dat
void add1ToBin(string& str) // + 1 vao chuoi nhi phan
{
	for (int i = str.length() - 1; i >= 0; i--)
	{
		if (str[i] == '1')
			str[i] = '0';
		else
		{
			str[i] = '1';
			break;
		}
	}
}

void reverseBits(string& str) // dao chuoi nhi phan
{
	for (int i = 0; i < str.length(); i++)
		str[i] = '1' - str[i] + '0';
}

int divideBy2(string& str) // chia mot chuoi so thap phan lon, thay doi chuoi va tra ra so du
{
	if (str == "1")
	{
		str = "0";
		return 1;
	}
	int rem = 0;
	string newstr = "";
	for (int i = 0; i < str.length(); i++)
	{
		rem = rem * 10 + str[i] - '0';
		newstr = newstr + char(rem / 2 + '0');
		if (newstr == "0")
			newstr = "";
		rem %= 2;
	}
	str = newstr;
	return rem;
}

void multiplyBy2(string& str) // nhan 2 vao chuoi so thap phan
{
	int carry = 0;
	string newstr = "";
	for (int i = str.length() - 1; i >= 0; i--)
	{
		int temp = (str[i] - '0') * 2 + carry;
		carry = temp / 10;
		newstr = char(temp % 10 + '0') + newstr;
		if (i == 0 && carry != 0)
			newstr = char(carry + '0') + newstr;
	}
	str = newstr;
}

void add1ToString(string& str) // + 1 vao chuoi so thap phan
{
	for (int i = str.length() - 1; i >= 0; i--)
	{
		if (str[i] == '9')
		{
			str[i] = '0';
			if (i == 0)
				str = '1' + str;
		}
		else
		{
			str[i] += 1;
			break;
		}
	}
}

string stringDecToStringBin(string dec) // chuyen mot chuoi so thap lon sang chuoi nhi phan tuong ung (chi xu li so duong)
{
	if (dec == "0")
		return dec;
	string str = dec;
	string res = ""; // ket qua
	while (str != "0")
	{
		int r = divideBy2(str);
		res = char(r + '0') + res;
	}
	return res;
} 

string stringBinToStringDec(string bin) // chuyen mot chuoi nhi phan lon sang chuoi so thap phan (chi so duong)
{
	string res = "0"; //ket qua
	int i = 0; //bo cac so 0 o dau chuoi nhi phan
	while (bin[i] == '0')
		i++;
	for (i; i < bin.length(); i++)
	{
		multiplyBy2(res);
		if (bin[i] == '1')
			add1ToString(res);
	}
	return res;
}




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

//edited by Dat
void QInt::ScanDecString(string s)
{
	string str = s;
	bool isNeg = false;
	if (str[0] == '-')
	{
		isNeg = true;
		str = str.substr(1, str.length() - 1);
	}
	string bin = stringDecToStringBin(str);
	if (isNeg)
	{
		while (bin.length() != 128)
		{
			bin = '0' + bin;
		}
		reverseBits(bin);
		add1ToBin(bin);
	}
	for (int i = 0; i < bin.length(); i++)
	{
		if (bin[i] == '1')
			SetBit(bin.length() - 1 - i);
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

void QInt::StringSum(string& s, string a)
{
	string z = "";

	int c = 0;

	while (a.size() < s.size()) a = '0' + a;

	while (s.size() < a.size()) s = '0' + s;

	for (int i = s.size() - 1; i >= 0; i--)
	{
		int t = c + (s[i] - '0') + (a[i] - '0');

		char d = t % 10 + '0';

		c = t / 10;

		z = d + z;
	}

	if (c != 0)
	{
		char d = c + '0';
		z = d + z;
	}

	s = z;
}

//edited by Dat
string QInt::GetDecString()
{
	string str = GetBinString();
	bool isNeg = false;
	if (str[0] == '1')
	{
		isNeg = true;
		reverseBits(str);
		add1ToBin(str);
	}
	string res = stringBinToStringDec(str);
	if (isNeg)
		res = '-' + res;
	return res;
}

string QInt::GetBinString()
{
	string s = "";

	for (int i = 0; i < 128; i++)
	{
		bool bit = GetBit(i);

		//if (i % 4 == 0) s = ' ' + s;

		bit ? s = '1' + s : s = '0' + s;
	}

	return s;
}