#include "Qfloat.h"
#include "QInt.h"


//check if str contain all 0
bool isFull0(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (str[i] != '0')
			return false;
	return true;
}

string get2sComplement(string str)
{
	for (int i = 0; i < str.length(); i++)
		str[i] = '1' - str[i] + '0';
	add1ToString(str);
	return str;
}

void shiftLeft(string& str1, string& str2)
{
	if (str1[0] == '1')
		str1 = str1 + str2[0];
	else
		str1 = str1.substr(1) + str2[0];
	str2 = str2.substr(1) + '0';
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
				int flen = fractional.length();
				if (tempstr.length() != flen)
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
	exp += 16383;
	if (exp != 0)
	{
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

	int last1 = 128; //find the last bit 1 of significand
	if (!isSignificandFull0)
		for (last1 = 0; last1 <= 111; last1++)
			if (GetBit(last1))
				break;

	//calculate exponent
	int exp = this->GetExponentDec(); //exponent

	if (exp == 32767) //if all bits in exponent are 1
	{
		if (!isSignificandFull0)
			return "NaN";
		if (GetBit(127))
			return "-Inf";
		return "Inf";
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
			if (j >= last1)
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
		bool check = false;
		int l = fractional.length();
		if (fractionalBin[i] == '1')
			fractional = '1' + fractional;
		else
		{
			if (fractional[0] == '1' || fractional[0] == '0')
				check = true;
		}
		fractional += '0';
		divideBy2(fractional);
		if (check)
		{
			while (fractional.length() < l + 1)
				fractional = '0' + fractional;
		}
	}
	//get result
	string res; //result
	if (fractional != "")
		res = whole + '.' + fractional;
	else
		res = whole;
	if (GetBit(127))
		res = '-' + res;

	//round by group 9,0
	res = roundbyGroup(res);

	return res;

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
			return *this;
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
	QInt zero;
	zero.ScanDecString("0");
	if ((zS > zero && xS < zero && yS < zero) || (zS<zero && xS>zero && yS > zero)) {//significand is overflow
		zS = (zS >> 1);
		++xE;
		if (xE > bias) {
			for (int i = 126; i > 111; i--)
				z.SetBit(i);
			return z;//inf
		}
	}

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

Qfloat Qfloat::operator*(Qfloat y) {
	if (this->GetDecString() == "0")
		return *this;
	if (y.GetDecString() == "0")
		return y;

	//exponent handler 
	QInt xE, yE, zE;//E is Exponents
	QInt bias,negbias;
	Qfloat z;
	bias.ScanDecString("16383");
	negbias.ScanDecString("-16384");
	xE.ScanBinString(this->getExponent());
	yE.ScanBinString(y.getExponent());

	zE = xE + yE - bias - bias;
	//overflow and underflow

	if (zE > bias) {//overflow
		for (int i = 126; i > 111; i--)
			z.SetBit(i);
		return z; //infinity
	}
	else if (zE < negbias) {
		return z; //0
	}

	zE = zE + bias;
	//significand handler
	QInt xS, yS, zS;
	string xS_str, yS_str;
	xS_str = this->getSignificand();
	int p = xS_str.size() - 1;
	for (int i = p; i >= 0; i--)
		if (xS_str[i] == '0') xS_str.pop_back();
		else break;
	p = xS_str.size();

	yS_str = y.getSignificand();
	int q = yS_str.size() - 1;
	for (int i = q; i >= 0; i--)
		if (yS_str[i] == '0') yS_str.pop_back();
		else break;
	q = yS_str.size();

	xS_str = "1" + xS_str; yS_str = "1" + yS_str;

	xS.ScanBinString(xS_str);
	yS.ScanBinString(yS_str);

	//multi 2 significand string function
	//zS = xS * yS;

	string zS_str = multi2String(xS_str, yS_str);
	//string zS_str = zS.GetBinString();

	//t handler
	while (zS_str[0] == '0')
		zS_str.erase(zS_str.begin());

	if (zS_str.size() > 0) zS_str.erase(zS_str.begin());

	int t = zS_str.size();

	int newexponent = t - p - q;
	QInt temp_exponent;
	temp_exponent.ScanDecString(to_string(newexponent));
	zE = zE + temp_exponent;

	while (zS_str.size() > 112)
		zS_str.pop_back();


	//ans

	string ans;
	for (int i = 14; i >= 0; i--)
		ans = ans + to_string(zE.GetBit(i));
	ans += zS_str;

	//is Negative 
	bool isNeg = false;
	if ((this->GetBit(127) == 1 && y.GetBit(127) == 0) || (this->GetBit(127) == 0 && y.GetBit(127) == 1))
		isNeg = true;
	if (isNeg) ans = "1" + ans; else ans = "0" + ans;

	while (ans.size() < 128)
		ans += "0";
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

Qfloat Qfloat::operator/(Qfloat y)
{
	//x = 0 -> return 0
	if (this->GetDecString() == "0")
		return Qfloat();
	//y = 0
	if (y.GetDecString() == "0")
	{
		//return NaN
		Qfloat temp;
		for (int i = 126; i >= 111; i--)
			temp.SetBit(i);
		return temp;
	}

	bool isNegative = true;
	if (this->GetBit(127) == y.GetBit(127))
		isNegative = false;

	Qfloat z; //result
	if (isNegative)
		z.SetBit(127);

	string xSig = "", ySig = ""; //significand of x and y
	int xExp = this->GetExponentDec(); //exponent of x
	int yExp = y.GetExponentDec(); //exponent of y
	for (int i = 111; i >= 0; i--)
	{
		xSig += char(this->GetBit(i) + '0');
		ySig += char(y.GetBit(i) + '0');
	}
	if (xExp == 0)
		xExp = 1;
	else
		xSig = '1' + xSig;
	if (yExp == 0)
		yExp = 1;
	else
		ySig = '1' + ySig;

	while (ySig.back() == '0')
	{
		ySig.pop_back();
		yExp++;
	}
	int lenYSig = ySig.length();
	int lenXSig = xSig.length();
	while (lenXSig < lenYSig + 113)
	{
		xSig += '0';
		lenXSig++;
		xExp--;
	}

	string zSigBin = divide2String(xSig, ySig);
	int zExp = xExp - yExp;
	while (zSigBin[0] == '0')
		zSigBin = zSigBin.substr(1);
	if (zSigBin != "")
	{
		int len = zSigBin.length();
		zExp = zExp + (len - 1);
		if (zExp > 16383) //overflow
		{
			for (int i = 126; i > 111; i--)
				z.SetBit(i);
			return z; //infinity
		}
		else if (zExp < -16494 || (zExp == -16494 && zSigBin != "1")) //underflow
			return z; // -> 0
		else if (zExp < -16382 || (zExp == -16494 && zSigBin == "1")) //denormalized
		{
			int t = -16382 - zExp;
			while (t > 0)
			{
				zSigBin = '0' + zSigBin;
				t--;
			}
			zExp = 0;
		}
		else
		{
			zExp += 16383;
			zSigBin = zSigBin.substr(1);
		}
	}
	else
		return Qfloat();
	if (zExp > 0)
	{
		QInt exp;
		exp.ScanDecString(to_string(zExp));
		for (int i = 0; i < 15; i++)
			if (exp.GetBit(i))
				z.SetBit(i + 112);
	}
	if (!zSigBin.empty())
	{
		int k = 0, i = 111;
		while (k < zSigBin.length() && i >= 0)
		{
			if (zSigBin[k] == '1')
				z.SetBit(i);
			k++; i--;
		}
	}
	return z;
}

//extra

Qfloat Qfloat::operator = (const Qfloat& T)
{
	for (int i = 0; i < 4; i++)
		this->data[i] = T.data[i];

	return *this;
}

string Qfloat::getBitBetween(int j, int i) {//j<=i
	string ans;
	for (int k = j; k <= i; k++)
		ans = to_string(this->GetBit(i)) + ans;
	return ans;
}

string Qfloat::multi2String(string str, string str1) {
	int n = str.size(); int m = str1.size();
	string ans = "";
	for (int i = 0; i < n; i++)
		ans += "0";


	for (int i = m - 1; i >= 0; i--) {
		if (str1[i] == '1') {
			ans = sum2String(ans, str);
		}
		str = str + "0";
	}

	return ans;

}

string Qfloat::sum2String(string str, string str1) {

	string ans;

	while (str.size() < str1.size())
		str = "0" + str;
	while (str.size() > str1.size())
		str1 = '0' + str1;

	bool du = 0;
	for (int i = str.size() - 1; i >= 0; i--) {
		char ch = str[i], ck = str1[i];
		if (du == 0) {
			if ((ch == '0') && (ck == '0'))
				ans = "0" + ans;
			else if ((ch == '1') && (ck == '0') || (ch == '0') && (ck == '1'))
				ans = "1" + ans;
			else {
				ans = "0" + ans;
				du = 1;
			}
		}
		else {
			if ((ch == '0') && (ck == '0')) {
				ans = "1" + ans;
				du = 0;
			}
			else if ((ch == '1') && (ck == '0') || (ch == '0') && (ck == '1')) {
				ans = "0" + ans;
			}
			else
				ans = "1" + ans;
		}
	}
	if (du == 1) ans = "1" + ans;
	return ans;
}

string Qfloat::divide2String(string str1, string str2)
{
	string a = "";
	while (a.length() < str2.length())
		a += '0';
	int n = str1.length();
	string m = get2sComplement('0' + str2);
	int l = m.length();
	for (n; n > 0; n--)
	{
		shiftLeft(a, str1);
		string temp = sum2String(a, m);
		if (temp.length() > l)
			temp = temp.substr(1);
		if (temp[0] == '0')
		{
			str1[str1.length() - 1] = '1';
			a = temp.substr(1);
		}
	}
	return str1;
}


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

int Qfloat::GetExponentDec()
{
	int res = 0;
	for (int i = 126; i > 111; i--)
	{
		res *= 2;
		if (GetBit(i))
			res++;
	}
	return res;
}

std::string Qfloat::roundbyGroup(std::string str) {
	str.resize(100);
	int cnt9 = 0, cnt0 = 0, index = 0, round = 10;
	bool take = 0;
	std::string bDot = "";
	for (int i = 0; i < str.size(); i++) {
		if (take == 1) {
			if (str[i] == '9') {
				if (cnt9 == 0) index = i;
				cnt9++;
			}
			else
				cnt9 = 0;
			if (str[i] == '0') {
				if (cnt0 == 0)index = i;
				cnt0++;
			}
			else cnt0 = 0;

		}
		if (str[i] == '.') take = 1;
		if (take == 0) bDot = bDot + str[i];
		if (cnt9 == round || cnt0 == round) break;
	}

	if (cnt9 == round || cnt0 == round) {
		if (str[index - 1] == '.') {
			long long temp = stoi(bDot);
			if (str[index] == '9')
				temp++;
			return std::to_string(temp);
		}
		else {
			if (str[index] == '9')
				str[index - 1] = char(str[index - 1] + 1);
			str.erase(str.begin() + index, str.end());
			return str;
		}
	}
	return str;
}