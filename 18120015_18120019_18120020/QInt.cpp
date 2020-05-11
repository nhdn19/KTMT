#include "QInt.h"

// divide decimal string by 2, return remainder
int divideBy2(std::string& str) 
{
	if (str == "0") return 0;

	int remainder = 0;

	std::string quotient = "";

	for (int i = 0; i < str.length(); i++)
	{
		remainder = remainder * 10 + str[i] - '0';
		quotient = quotient + char(remainder / 2 + '0');
		if (quotient == "0") quotient = "";
		remainder = remainder % 2;
	}

	if (quotient == "") quotient = "0";

	str = quotient;

	return remainder;
}

// mulitply decimal string by 2
void multiplyBy2(std::string& str) 
{
	int carry = 0;
	std::string product = "";

	for (int i = str.length() - 1; i >= 0; i--)
	{
		int temp = (str[i] - '0') * 2 + carry;
		carry = temp / 10;
		product = char(temp % 10 + '0') + product;
		if (i == 0 && carry != 0)
			product = char(carry + '0') + product;
	}

	str = product;
}

// add 1 to decimal string
void add1ToString(std::string& str) 
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
			str[i] = str[i] + 1;
			break;
		}
	}
}

std::string DecToBin(QInt Q)
{
	return Q.GetBinString();
}

std::string DecToHex(QInt Q)
{
	return Q.GetHexString();
}

QInt BinToDec(std::string x)
{
	QInt Q;
	Q.ScanBinString(x);
	return Q;
}

std::string BinToHex(std::string x)
{
	QInt Q;
	Q.ScanBinString(x);
	return Q.GetHexString();
}

QInt::QInt()
{
	data[0] = data[1] = data[2] = data[3] = 0;
}

void QInt::ZeroBits()
{
	data[0] = data[1] = data[2] = data[3] = 0;
}

void QInt::OffBit(int i)
{
	if (i < 0 || i > size - 1) return;

	int& block = data[3 - i / 32];
	int index = i % 32;
	block = block & ~(1 << index);
}

void QInt::SetBit(int i)
{
	if (i < 0 || i > size - 1) return;

	int& block = data[3 - i / 32];
	int index = i % 32;
	block = block | (1 << index);
}

bool QInt::GetBit(int i)
{
	if (i < 0 || i > size - 1) return 0;

	int block = data[3 - i / 32];
	int index = i % 32;
	int bit = 1 & (block >> index);
	return bit;
}

void QInt::ScanBinString(std::string s)
{
	ZeroBits();

	int k = 0;

	for (int i = s.size() - 1; i >= 0; i--)
	{
		if (s[i] == '1') SetBit(k);
		k = k + 1;
	}
}

std::string QInt::GetBinString()
{
	std::string s = "";

	for (int i = 0; i < size; i++)
	{
		bool bit = GetBit(i);

		bit ? s = '1' + s : s = '0' + s;
	}

	return s;
}

//store a string of decimal number into QInt
void QInt::ScanDecString(std::string s)
{
	ZeroBits();
	//check if negative
	bool isNegative = false;

	if (s[0] == '-')
	{
		isNegative = true;
		s = s.substr(1, s.length() - 1);
	}

	std::string res = ""; // result

	for (int i = 0; i < size; i++)
	{
		int r = divideBy2(s);
		if (r) SetBit(i);
	}

	if (isNegative) *this = ++(~(*this));
}

//get a string of decimal value of QInt
std::string QInt::GetDecString()
{
	bool isNegative = false;

	QInt ans = *this;

	if (GetBit(size - 1))
	{
		isNegative = true;
		ans = ++(~(*this));
	}

	std::string res = "0"; // result

	int i = size - 1; // loop from msb

	while (ans.GetBit(i) == 0 && i >= 0) i--; //find the first bit 1 from msb

	//x2 result every loop, if bit 1 then +1 to result
	for (i; i >= 0; i--)
	{
		multiplyBy2(res);
		if (ans.GetBit(i)) add1ToString(res);
	}

	if (isNegative) res = '-' + res;

	return res;
}

void QInt::ScanHexString(std::string s)
{
	ZeroBits();

	std::string hex[16];

	for (int i = 0; i < 16; i++)
	{
		QInt T;
		T.ScanDecString(std::to_string(i));
		std::string bin = T.GetBinString();
		hex[i] = bin.substr(bin.size() - 4);
	}

	std::string bin = "";

	for (int i = 0; i < s.size(); i++)
	{
		char c = s[i];
		if ('A' <= c && c <= 'F')
			bin = bin + hex[(c - 'A' + 10)];
		else if ('0' <= c && c <= '9')
			bin = bin + hex[(c - '0')];
	}

	int k = 0;

	for (int i = bin.size() - 1; i >= 0; i--)
	{
		if (bin[i] == '1') SetBit(k);
		k = k + 1;
	}

}

std::string QInt::GetHexString()
{
	char hex[16];

	for (int i = 0; i < 16; i++)
	{
		if (i < 10) hex[i] = i + '0';
		else hex[i] = (i - 10) + 'A';
	}

	std::string res = ""; // result

	int i = size - 1; // loop from msb

	while (GetBit(i) == 0 && i >= 0) i--;

	for (int j = 0; j <= i; j += 4)
	{
		int v = 0;

		for (int k = 3; k >= 0; k--)
		{
			if (j + k > i) continue;
			v = v * 2;
			if (GetBit(j + k)) v = v + 1;
		}

		res = hex[v] + res;
	}

	if (res == "") return "0";

	return res;
}

void QInt::ScanQInt(std::string T, std::string base)
{
	if (base == "2")
		this->ScanBinString(T);

	if (base == "10")
		this->ScanDecString(T);

	if (base == "16")
		this->ScanHexString(T);
}

std::string QInt::GetQInt(std::string base)
{
	if (base == "2")
	{
		std::string ans = this->GetBinString();

		int i = 0;

		while (ans[i] == '0') i += 1;

		return ans.erase(0, i);
	}

	if (base == "10")
		return this->GetDecString();

	if (base == "16")
		return this->GetHexString();

	return "";
}

// arithmetic operator

QInt QInt::operator ++ ()
{
	for (int i = 0; i < size; i++)
	{
		if (!GetBit(i))
		{
			SetBit(i);
			break;
		}

		OffBit(i);
	}

	return *this;
}

QInt QInt::operator + (QInt T)
{
	int c = 0;
	int x, y;

	QInt sum;

	for (int i = 0; i < size; i++)
	{
		x = GetBit(i), y = T.GetBit(i);
		int p = x + y + c;
		if (p % 2) sum.SetBit(i);
		if (p > 1) c = 1;
		else c = 0;
	}

	// van y tuong cu cua Duong, Dung chi viet gon lai thoi

	return sum;
}

QInt QInt::operator - (QInt T)
{
	QInt revs = ++(~T);

	return (*this + revs);
}

QInt QInt::operator * (QInt M)
{
	bool T = 0; // Q_(-1) value
	bool A0 = 0;
	bool Q0 = 0;

	QInt Q = *this;
	QInt N = ++(~M); // value of -M
	QInt A;

	for (int i = 0; i < size; i++)
	{
		if (Q.GetBit(0) == 1 && T == 0) A = A + N;
		if (Q.GetBit(0) == 0 && T == 1) A = A + M;

		A0 = A.GetBit(0);
		A = A >> 1;
		Q0 = Q.GetBit(0);
		Q = Q >> 1;
		A0 ? Q.SetBit(size - 1) : Q.OffBit(size - 1);
		Q0 ? T = 1 : T = 0;
	}

	return Q;
}

QInt QInt::operator / (QInt M)
{
	QInt Q = *this;
	QInt A, B;

	bool sQ = Q.GetBit(size - 1);
	bool sM = M.GetBit(size - 1);

	if (sQ == 1) Q = ++(~Q);
	if (sM == 0) M = ++(~M);

	for (int i = 0; i < size; i++)
	{
		A = A << 1;

		if (Q.GetBit(size - 1)) A.SetBit(0);

		Q = Q << 1;

		B = A + M;

		if (B.GetBit(size - 1) == 0)
		{
			Q.SetBit(0);
			A = B;
		}
	}

	if (sQ ^ sM) Q = ++(~Q);

	return Q;
}


QInt QInt::operator % (QInt M)
{
	QInt Q = *this;
	QInt A, B;

	bool sQ = Q.GetBit(size - 1);
	bool sM = M.GetBit(size - 1);

	if (sQ == 1) Q = ++(~Q);
	if (sM == 0) M = ++(~M);

	for (int i = 0; i < size; i++)
	{
		A = A << 1;

		if (Q.GetBit(size - 1)) A.SetBit(0);

		Q = Q << 1;

		B = A + M;

		if (B.GetBit(size - 1) == 0)
		{
			Q.SetBit(0);
			A = B;
		}
	}

	if (sQ) A = ++(~A);

	return A;
}

QInt QInt::operator = (const QInt& T)
{
	for (int i = 0; i < 4; i++)
		this->data[i] = T.data[i];

	return *this;
}


QInt QInt::operator = (const std::string T)
{
	this->ScanDecString(T);
	return *this;
}


// logic operator

QInt QInt::operator & (QInt& T)
{
	QInt ans;

	for (int i = 0; i < size; i++)
		if (GetBit(i) && T.GetBit(i))
			ans.SetBit(i);

	return ans;
}

QInt QInt::operator ^ (QInt& T)
{
	QInt ans;

	for (int i = 0; i < size; i++)
		if (GetBit(i) != T.GetBit(i))
			ans.SetBit(i);

	return ans;
}


QInt QInt::operator | (QInt& T)
{
	QInt ans;

	for (int i = 0; i < size; i++)
		if (GetBit(i) || T.GetBit(i))
			ans.SetBit(i);

	return ans;
}

QInt QInt::operator ~ ()
{
	QInt ans;

	for (int i = 0; i < size; i++)
		if (!GetBit(i)) ans.SetBit(i);

	return ans;
}

// shift operator

//shift right operator
QInt QInt::operator >> (int k)
{
	bool msb = GetBit(size - 1);

	QInt temp;

	//inedaquate k
	if (k < 1)
		return *this;
	if (k >= size)
	{
		if (msb)
			for (int i = 0; i < 127; i++)
				temp.SetBit(i);
		return temp;
	}

	//

	int i = 0;

	for (i; i < size - k; i++)
		if (GetBit(i + k)) temp.SetBit(i);

	if (msb)
	{
		while (i < size)
		{
			temp.SetBit(i++);
		}
	}

	return temp;
}

//shift left operator
QInt QInt::operator << (int k)
{
	QInt temp;

	if (k >= size) return temp;
	if (k < 1) return *this;

	for (int i = size - 1; i >= k; i--)
		if (GetBit(i - k)) temp.SetBit(i);

	return temp;
}

QInt QInt::ror(int k)
{
	QInt temp;

	k = k % size;

	if (k == 0) return *this;

	for (int i = k; i < size; i++)
		if (GetBit(i)) temp.SetBit(i - k);

	for (int i = 0; i < k; i++)
		if (GetBit(i)) temp.SetBit(size - k + i);

	return temp;
}


QInt QInt::rol(int k)
{
	QInt temp;

	k = k % size;

	if (k == 0) return *this;

	for (int i = k; i < size; i++)
		if (GetBit(i - k)) temp.SetBit(i);

	for (int i = 0; i < k; i++)
		if (GetBit(size - k + i)) temp.SetBit(i);

	return temp;
}
// comparison operator

//operator <
bool QInt::operator < (QInt T)
{
	bool msbx = GetBit(size - 1); //msb of x
	bool msby = T.GetBit(size - 1); //msb of y

	//compare 2 msb
	if (msbx > msby) return true;
	if (msbx < msby) return false;

	//find the 2 first different bits from msb then compare
	for (int i = size - 2; i >= 0; i--)
	{
		bool bitx = GetBit(i);
		bool bity = T.GetBit(i);
		if (bitx > bity) return false;
		if (bitx < bity) return true;
	}

	return false;
}

//operator >
bool QInt::operator > (QInt T)
{
	return !(*this <= T);
}

//operator <=
bool QInt::operator <= (QInt T)
{
	bool msbx = GetBit(size - 1);
	bool msby = T.GetBit(127);

	if (msbx > msby) return true;
	if (msbx < msby) return false;

	for (int i = 126; i >= 0; i--)
	{
		bool bitx = GetBit(i);
		bool bity = T.GetBit(i);
		if (bitx > bity) return false;
		if (bitx < bity) return true;
	}

	return true;
}

//operator >=
bool QInt::operator >= (QInt T)
{
	return !(*this < T);
}

//operator ==
bool QInt::operator == (QInt T)
{
	for (int i = 127; i >= 0; i--)
	{
		if (GetBit(i) != T.GetBit(i))
			return false;
	}

	return true;
}