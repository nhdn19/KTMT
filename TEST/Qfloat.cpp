#include "Qfloat.h"
#include "QInt.h"



bool isFull0(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (str[i] != '0')
			return false;
	return true;
}

void Qfloat::ZeroBits()
{
	data[0] = data[1] = data[2] = data[3] = 0;
}

void Qfloat::OffBit(int i)
{
	if (i < 0 || i > size - 1) return;

	int& block = data[3 - i / 32];
	int index = i % 32;
	block = block & ~(1 << index);
}

void Qfloat::SetBit(int i)
{
	if (i < 0 || i > size - 1) return;

	int& block = data[3 - i / 32];
	int index = i % 32;
	block = block | (1 << index);
}

bool Qfloat::GetBit(int i)
{
	if (i < 0 || i > size - 1) return 0;

	int block = data[3 - i / 32];
	int index = i % 32;
	int bit = 1 & (block >> index);
	return bit;
}

void Qfloat::ScanDecString(string dec)
{
	ZeroBits();
	// = 0
	if (isFull0(dec))
		return;
	// is negative then set signal bit first
	if (dec[0] == '-')
	{
		SetBit(size - 1);
		dec = dec.substr(1);
	}

	//seperate whole and fractional part
	int pointIndex = (int)dec.find('.');
	string whole = ""; //whole part
	string fractional = ""; //fractional part
	if (pointIndex == string::npos)
		whole = dec;
	else
	{
		whole = dec.substr(0, pointIndex);
		fractional = dec.substr(size_t(pointIndex) + 1);
	}

	//whole part to binary
	string wholeBin = "";
	int r = 0;
	do
	{
		r = divideBy2(whole);
		wholeBin = char(r + '0') + wholeBin;
	} while (whole != "0");
	int len1 = wholeBin.length();
	//infinity
	if (len1 > 16384)
	{
		for (int i = 126; i >= 112; i--)
			SetBit(i);
		return;
	}

	//fractional part to binary
	int limit = 0; //number of bits need to take from fractional part
	int first1 = -len1; //the first bit 1 found in fractional part, < 0 if it's already in whole part, > 0 if in fractional part, = 0 if unknown
	string fractionalBin = "";
	if (fractional != "")
	{
		if (wholeBin != "0")
		{
			limit = 112 - len1 + 1;
		}
		else
		{
			limit = 16494;
			first1 = 0;
		}
		if (limit > 0)
		{
			string tempstr = fractional;
			int counter = 0;
			do
			{
				counter++;
				multiplyBy2(tempstr);
				if (tempstr.length() != fractional.length())
				{
					if (first1 == 0)
					{
						first1 = counter;
						if (first1 <= 16382)
							limit = first1 + 112;
					}
					fractionalBin += '1';
					tempstr = tempstr.substr(1);
				}
				else
					fractionalBin += '0';
				if (counter >= limit)
					break;
			} while (!isFull0(tempstr));
		}
	}


	int exp = 0; //exponent
	string tempBin = wholeBin + fractionalBin;
	int start = 0; //position from tempBin to start set bit to significand
	if (first1 < 0)
	{
		exp = len1 - 1;
		start = 1;
	}
	else if (first1 > 0)
	{
		if (first1 > 16382)
			start = 16382 + len1;
		else
		{
			exp = -first1;
			start = first1 + len1;
		}
	}
	else
	{
		// -> 0
		return;
	}
	//set exp bit
	if (exp != 0)
	{
		exp += 16383;
		int pos = 112;
		while (exp != 0)
		{
			if (exp % 2 == 1)
				SetBit(pos);
			exp /= 2;
			pos++;
		}
	}
	//set significand bit
	int i = 111;
	int len = tempBin.length();
	while (start < len && i >= 0)
	{
		if (tempBin[start] == '1')
			SetBit(i);
		start++;
		i--;
	}
}

string Qfloat::GetDecString()
{
	bool isSignificandFull0 = true; //check if all bits in significand are 0
	for (int i = 111; i >= 0; i--)
		if (GetBit(i))
			isSignificandFull0 = false;

	int last1 = -1; //find the last bit 1 of significand
	if (!isSignificandFull0)
		for (last1 = 0; last1 <= 111; last1++)
			if (GetBit(last1))
				break;

	//calculate exponent
	int exp = 0; //exponent
	for (int i = 126; i >= 112; i--)
	{
		exp *= 2;
		if (GetBit(i))
			exp += 1;
	}

	if (exp == 32767) //if all bits in exponent are 1
	{
		if (!isSignificandFull0)
			return "NaN";
		if (GetBit(127))
			return "Inf";
		return "-Inf";
	}

	//find binary of whole and fractional part
	string fractionalBin = ""; //fractional part in binary
	string wholeBin = ""; // whole part in binary
	if (exp == 0) //if all bits in exponent are 0
	{
		//0
		if (isSignificandFull0)
			return "0";
		//denormalized
		for (int i = 0; i < 16382; i++)
			fractionalBin += '0';
		for (int i = 111; i >= last1; i--)
			fractionalBin += char(GetBit(i) + '0');
		wholeBin = "0";
	}
	else
	{
		exp -= 16383;
		if (exp >= 0)
		{
			wholeBin = "1";
			int j;
			for (j = 111;; j--)
			{
				if (exp == 0)
					break;
				if (j < 0)
					wholeBin += '0';
				else
					wholeBin += char(GetBit(j) + '0');
				exp--;
			}
			if (last1 != -1 && j >= last1)
				for (j; j >= last1; j--)
					fractionalBin += char(GetBit(j) + '0');
		}
		else
		{
			for (int i = 111; i >= last1; i--)
				fractionalBin += char(GetBit(i) + '0');
			fractionalBin = '1' + fractionalBin;
			exp++;
			for (int i = 0; i < -exp; i++)
				fractionalBin = '0' + fractionalBin;
			wholeBin = "0";
		}
	}

	//calculate whole and fractional part
		//whole part
	string whole = "0";
	for (int i = 0; i < wholeBin.length(); i++)
	{
		multiplyBy2(whole);
		if (wholeBin[i] == '1') add1ToString(whole);
	}
	//fractional part
	string fractional = "";
	for (int i = fractionalBin.length() - 1; i >= 0; i--)
	{
		if (fractionalBin[i] == '1')
			fractional = '1' + fractional;
		fractional += '0';
		divideBy2(fractional);
	}
	if (GetBit(127))
		return '-' + whole + '.' + fractional;
	else
		return whole + '.' + fractional;
}

string Qfloat::GetBinString()// rename Print to getBinString
{
	string ans = "";
	for (int i = 127; i >= 0; i--)
		ans = ans + to_string(GetBit(i));
	return ans;
}

///////////////////////////////////////

void Qfloat::ScanBinString(string s)
{
	ZeroBits();

	int k = 0;

	for (int i = s.size() - 1; i >= 0; i--)
	{
		if (s[i] == '1') SetBit(k);
		k = k + 1;
	}
}


Qfloat Qfloat::operator+(Qfloat y) {
	//this = x;

	//
	Qfloat z;
	if (this->GetDecString() == "0")
		return y;
	if (y.GetDecString() == "0")
		return *this;
	QInt xE, yE, xS, yS, zS, zE;//E is Exponents, S is Signficand

	xE.ScanBinString(this->getExponent());
	yE.ScanBinString(y.getExponent());

	xS.ScanBinString(this->getSignificand());
	yS.ScanBinString(y.getSignificand());

	//calculate accurate exponent
	QInt bias;
	bias.ScanDecString("16383");
	xE = xE - bias;
	yE = yE - bias;


	//SetBit in 112 of Significand
	xS.SetBit(112);
	yS.SetBit(112);

	//makes exponents equal
	while (xE < yE) {
		++xE;
		xS = (xS >> 1);
		if (xS.GetDecString() == "0")
			return y;
	}
	while (xE > yE) {
		++yE;
		yS = (yS >> 1);
		if (yS.GetDecString() == "0")
			return y;
	}

	//isNegative
	bool isNeg = false;
	if ((y.GetBit(127) == 1 && this->GetBit(127) == 1) || (y.GetBit(127) == 1 && (yS > xS)) || (this->GetBit(127) == 1) && (xS > yS))
		isNeg = true;

	//add signed significand
	if (y.GetBit(127) == this->GetBit(127))
		zS = xS + yS;
	else {
		if (xS > yS)
			zS = xS - yS;
		else
			zS = yS - xS;
	}

	//significand = 0
	if (zS.GetDecString() == "0") {
		z.ScanDecString("0");
		return z;
	}

	//significand overflow?

	//while until significant's form : 01.....
	string str = "";
	for (int i = 113; i >= 0; i--)
		str = str + to_string(zS.GetBit(i));
	if (str[0] == '1') {
		str = "0" + str;
		str.pop_back();
		++xE;
	}
	while (str[1] != '1') {
		str = str + '0';
		str.erase(str.begin());
		QInt temp;
		temp.ScanDecString("1");
		xE = xE - temp;
	}

	while (str.size() > 112)
		str.erase(str.begin());

	xE = xE + bias;

	string exponent = "";
	for (int i = 14; i >= 0; i--)
		exponent = exponent + to_string(xE.GetBit(i));

	string ans = exponent + str;
	if (isNeg) ans = "1" + ans;
	else ans = "0" + ans;
	z.ScanBinString(ans);

	return z;
}

Qfloat Qfloat::operator-(Qfloat y) {
	if (y.GetBit(127))
		y.OffBit(127);
	else
		y.SetBit(127);
	return *this + y;
}

//extra
string Qfloat::getSign() {
	if (GetBit(127)) return "1";
	return "0";
}

string Qfloat::getExponent() {
	string s = "";
	for (int i = 126; i >= 112; i--)
		if (GetBit(i))
			s += "1";
		else
			s += "0";
	return s;
}

string Qfloat::getSignificand() {
	string s = "";
	for (int i = 111; i >= 0; i--)
		if (GetBit(i))
			s += "1";
		else
			s += "0";
	return s;
}

