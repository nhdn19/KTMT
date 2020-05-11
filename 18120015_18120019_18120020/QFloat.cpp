#include "QFloat.h"


//check if a string contain all 0
bool isFull0(std::string str)
{
	for (int i = 0; i < str.length(); i++)
		if (str[i] != '0') return false;

	return true;
}

//get the 2s complement of a binary string
std::string get2sComplement(std::string str)
{
	for (int i = 0; i < str.length(); i++)
		str[i] = '1' - str[i] + '0';
	add1ToString(str);
	return str;
}

//shift left 2 strings
void shiftLeft(std::string& str1, std::string& str2)
{
	if (str1[0] == '1')
		str1 = str1 + str2[0];
	else
		str1 = str1.substr(1) + str2[0];
	str2 = str2.substr(1) + '0';
}

void QFloat::ZeroBits()
{
	data[0] = data[1] = data[2] = data[3] = 0;
}

void QFloat::OffBit(int i)
{
	if (i < 0 || i > size - 1) return;

	int& block = data[3 - i / 32];
	int index = i % 32;
	block = block & ~(1 << index);
}

void QFloat::SetBit(int i)
{
	if (i < 0 || i > size - 1) return;

	int& block = data[3 - i / 32];
	int index = i % 32;
	block = block | (1 << index);
}

bool QFloat::GetBit(int i)
{
	if (i < 0 || i > size - 1) return 0;

	int block = data[3 - i / 32];
	int index = i % 32;
	int bit = 1 & (block >> index);
	return bit;
}

//store a string of decimal real number into QFloat
void QFloat::ScanDecString(std::string dec)
{
	ZeroBits();

	// = 0
	if (isFull0(dec)) return;

	// is negative then set signal bit first
	if (dec[0] == '-')
	{
		SetBit(size - 1);
		dec = dec.substr(1);
	}

	//seperate whole and fractional part
	int pointIndex = (int)dec.find('.');
	std::string whole = "";
	std::string fractional = "";


	if (pointIndex == std::string::npos)
		whole = dec;
	else
	{
		whole = dec.substr(0, pointIndex);
		fractional = dec.substr(size_t(pointIndex) + 1);
	}


	//whole part to binary
	std::string wholeBin = "";
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
		for (int i = 126; i >= 112; i--) SetBit(i);

		return;
	}

	//fractional part to binary
	int limit = 0; //number of bits need to take from fractional part
	int first1 = -len1; //the first bit 1 found in fractional part, < 0 if it's already in whole part, > 0 if in fractional part, = 0 if unknown

	std::string fractionalBin = "";

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
			std::string tempstr = fractional;
			int counter = 0;
			do
			{
				counter = counter + 1;
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
				else fractionalBin += '0';

				if (counter >= limit) break;

			} while (!isFull0(tempstr));
		}
	}


	int exp = 0; //exponent
	int start = 0; //position from tempBin to start set bit to significand
	std::string tempBin = wholeBin + fractionalBin;

	if (first1 < 0)
	{
		exp = len1 - 1;
		start = 1;
	}
	else if (first1 > 0)
	{
		if (first1 > 16382)
		{
			start = 16382 + len1;
		}
		else
		{
			exp = -first1;
			start = first1 + len1;
		}
	}
	else return; // -> 0


	//set exponent bits
	exp = exp + 16383;
	if (exp != 0)
	{
		int pos = 112;
		while (exp != 0)
		{
			if (exp % 2 == 1) SetBit(pos);

			exp = exp / 2;
			pos = pos + 1;
		}
	}


	//set significand bits
	int i = 111;
	int len = tempBin.length();

	while (start < len && i >= 0)
	{
		if (tempBin[start] == '1') SetBit(i);

		start = start + 1;
		i = i - 1;
	}
}

//get a string of decimal value of QFloat
std::string QFloat::GetDecString()
{
	bool isSignificandFull0 = true; //check if all bits in significand are 0

	for (int i = 111; i >= 0; i--)
		if (GetBit(i)) isSignificandFull0 = false;

	int last1 = 128; //find the last bit 1 of significand
	if (!isSignificandFull0)
		for (last1 = 0; last1 <= 111; last1++)
			if (GetBit(last1)) break;


	//calculate exponent
	int exp = this->GetExponentDec(); //exponent

	if (exp == 32767) //if all bits in exponent are 1
	{
		if (!isSignificandFull0) return "NaN";

		if (GetBit(127)) return "-Inf";

		return "Inf";
	}

	//find binary string of whole and fractional part
	std::string fractionalBin = ""; //fractional part in binary
	std::string wholeBin = ""; // whole part in binary


	if (exp == 0) //if all bits in exponent are 0
	{
		//0
		if (isSignificandFull0) return "0";

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
				if (exp == 0) break;

				if (j < 0)
					wholeBin += '0';
				else
					wholeBin += char(GetBit(j) + '0');

				exp = exp - 1;
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

			exp = exp + 1;

			for (int i = 0; i < -exp; i++)
				fractionalBin = '0' + fractionalBin;

			wholeBin = "0";
		}
	}

	//calculate whole and fractional part

	//whole part
	std::string whole = "0";

	for (int i = 0; i < wholeBin.length(); i++)
	{
		multiplyBy2(whole);
		if (wholeBin[i] == '1') add1ToString(whole);
	}


	//fractional part
	std::string fractional = "";

	for (int i = fractionalBin.length() - 1; i >= 0; i--)
	{
		bool check = false;
		int l = fractional.length();

		if (fractionalBin[i] == '1')
		{
			fractional = '1' + fractional;
		}
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
	std::string res;

	if (fractional != "")
		res = whole + '.' + fractional;
	else
		res = whole;

	if (GetBit(127)) res = '-' + res;


	res = roundbyGroup(res);

	return res;
}

std::string QFloat::GetBinString()// rename Print to getBinString
{
	std::string ans = "";

	for (int i = 127; i >= 0; i--)
		ans = ans + std::to_string(GetBit(i));

	return ans;
}

///////////////////////////////////////

void QFloat::ScanBinString(std::string s)
{
	ZeroBits();

	int k = 0;

	for (int i = s.size() - 1; i >= 0; i--)
	{
		if (s[i] == '1') SetBit(k);
		k = k + 1;
	}
}


QFloat QFloat::operator + (QFloat y)
{
	QFloat z;

	QInt xE, yE, xS, yS, zS, zE; //E is Exponents, S is Signficand

	if (this->GetDecString() == "0") return y;

	if (y.GetDecString() == "0") return *this;


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
	while (xE < yE)
	{
		++xE;
		xS = (xS >> 1);
		if (xS.GetDecString() == "0")
			return y;
	}

	while (xE > yE)
	{
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
	{
		zS = xS + yS;
	}
	else
	{
		if (xS > yS)
			zS = xS - yS;
		else
			zS = yS - xS;
	}

	//significand = 0
	if (zS.GetDecString() == "0")
	{
		z.ScanDecString("0");
		return z;
	}

	//significand overflow?

	//while until significant's form : 01.....
	std::string str = "";

	for (int i = 113; i >= 0; i--)
		str = str + std::to_string(zS.GetBit(i));

	if (str[0] == '1')
	{
		str = "0" + str;
		str.pop_back();
		++xE;
	}

	while (str[1] != '1')
	{
		str = str + '0';
		str.erase(str.begin());
		QInt temp;
		temp.ScanDecString("1");
		xE = xE - temp;
	}

	while (str.size() > 112) str.erase(str.begin());

	xE = xE + bias;

	std::string exponent = "";

	for (int i = 14; i >= 0; i--)
		exponent = exponent + std::to_string(xE.GetBit(i));

	std::string ans = exponent + str;

	if (isNeg) ans = "1" + ans; else ans = "0" + ans;

	z.ScanBinString(ans);

	return z;
}

QFloat QFloat::operator - (QFloat y)
{
	if (y.GetBit(127))
		y.OffBit(127);
	else
		y.SetBit(127);

	return *this + y;
}

QFloat QFloat::operator * (QFloat y)
{
	if (this->GetDecString() == "0") return *this;

	if (y.GetDecString() == "0") return y;

	//exponent handler 
	//E is Exponents
	QInt xE, yE, zE;
	QInt bias;

	bias.ScanDecString("16383");
	xE.ScanBinString(this->getExponent());
	yE.ScanBinString(y.getExponent());

	zE = xE + yE - bias;

	//significand handler
	QInt xS, yS, zS;
	std::string xS_str, yS_str;

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

	std::string zS_str = multi2String(xS_str, yS_str);
	//string zS_str = zS.GetBinString();

	//t handler
	while (zS_str[0] == '0') zS_str.erase(zS_str.begin());

	if (zS_str.size() > 0) zS_str.erase(zS_str.begin());

	int t = zS_str.size();

	int newexponent = t - p - q;

	QInt temp_exponent;
	temp_exponent.ScanDecString(std::to_string(newexponent));

	zE = zE + temp_exponent;

	while (zS_str.size() > 112) zS_str.pop_back();

	//ans

	std::string ans;

	for (int i = 14; i >= 0; i--)
		ans = ans + std::to_string(zE.GetBit(i));

	ans += zS_str;

	//is Negative 
	bool isNeg = false;

	if ((this->GetBit(127) == 1 && y.GetBit(127) == 0) || (this->GetBit(127) == 0 && y.GetBit(127) == 1))
		isNeg = true;

	if (isNeg) ans = "1" + ans; else ans = "0" + ans;

	while (ans.size() < 128) ans += "0";


	QFloat z;
	z.ScanBinString(ans);
	return z;
}

//arithmetic operator /
QFloat QFloat::operator / (QFloat y)
{
	//x = 0 -> return 0
	if (this->GetDecString() == "0")
		return QFloat();

	//y = 0
	if (y.GetDecString() == "0")
	{
		//return NaN
		QFloat temp;
		for (int i = 126; i >= 111; i--)
			temp.SetBit(i);
		return temp;
	}

	bool isNegative = true;
	if (this->GetBit(127) == y.GetBit(127))
		isNegative = false;

	QFloat z; //result
	if (isNegative)
		z.SetBit(127);

	std::string xSig = "", ySig = ""; //significand of x and y
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

	std::string zSigBin = divide2String(xSig, ySig); //divide two significands
	int zExp = xExp - yExp; //substract two exponents
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
		return QFloat();

	//set bits to result
	if (zExp > 0)
	{
		QInt exp;
		exp.ScanDecString(std::to_string(zExp));
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

QFloat QFloat::operator = (const QFloat& T)
{
	for (int i = 0; i < 4; i++)
		this->data[i] = T.data[i];

	return *this;
}

std::string QFloat::getBitBetween(int j, int i) // j <= i
{
	std::string ans;

	for (int k = j; k <= i; k++)
		ans = std::to_string(this->GetBit(i)) + ans;

	return ans;
}

std::string QFloat::multi2String(std::string str, std::string str1)
{
	int n = str.size();
	int m = str1.size();

	std::string ans = "";

	for (int i = 0; i < n; i++) ans += "0";

	for (int i = m - 1; i >= 0; i--)
	{
		if (str1[i] == '1')
		{
			ans = sum2String(ans, str);
		}
		str = str + "0";
	}

	return ans;
}

std::string QFloat::sum2String(std::string str, std::string str1)
{

	std::string ans;

	while (str.size() < str1.size())
		str = "0" + str;

	while (str.size() > str1.size())
		str1 = '0' + str1;

	bool du = 0;

	for (int i = str.size() - 1; i >= 0; i--)
	{
		char ch = str[i];
		char ck = str1[i];

		if (du == 0)
		{
			if ((ch == '0') && (ck == '0'))
			{
				ans = "0" + ans;
			}
			else if ((ch == '1') && (ck == '0') || (ch == '0') && (ck == '1'))
			{
				ans = "1" + ans;
			}
			else
			{
				ans = "0" + ans;
				du = 1;
			}
		}
		else
		{
			if ((ch == '0') && (ck == '0'))
			{
				ans = "1" + ans;
				du = 0;
			}
			else if ((ch == '1') && (ck == '0') || (ch == '0') && (ck == '1'))
			{
				ans = "0" + ans;
			}
			else ans = "1" + ans;
		}
	}


	if (du == 1) ans = "1" + ans;


	return ans;
}

std::string QFloat::getSign()
{

	return GetBit(127) ? "1" : "0";
}

std::string QFloat::getExponent()
{
	std::string s = "";

	for (int i = 126; i >= 112; i--)
	{
		GetBit(i) ? s += "1" : s += "0";
	}

	return s;
}

std::string QFloat::getSignificand()
{
	std::string s = "";

	for (int i = 111; i >= 0; i--)
	{
		GetBit(i) ? s += "1" : s += "0";
	}

	return s;
}

//get decimal value of exponent part
int QFloat::GetExponentDec()
{
	int res = 0;

	for (int i = 126; i > 111; i--)
	{
		res = res * 2;

		if (GetBit(i)) res += 1;
	}
	return res;
}


void QFloat::ScanQFloat(std::string T, std::string base)
{
	if (base == "2")
		this->ScanBinString(T);

	if (base == "10")
		this->ScanDecString(T);

}

std::string QFloat::GetQFloat(std::string base)
{
	if (base == "2")
		return this->GetBinString();

	if (base == "10")
		return this->GetDecString();

	return "";
}

std::string QFloat::roundbyGroup(std::string str) 
{
	str.resize(30);
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

bool QFloat::operator == (QFloat T)
{
	for (int i = 127; i >= 0; i--)
	{
		if (GetBit(i) != T.GetBit(i))
			return false;
	}

	return true;
}

//divide 2 binary strings
std::string QFloat::divide2String(std::string str1, std::string str2)
{
	std::string a = "";

	while (a.length() < str2.length())
		a += '0';

	int n = str1.length();

	std::string m = get2sComplement('0' + str2);
	int l = m.length();

	for (n; n > 0; n--)
	{
		shiftLeft(a, str1);
		std::string temp = sum2String(a, m);

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