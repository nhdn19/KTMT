#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "QInt.h"
#include "Qfloat.h"

using namespace std;

// function to interact with QInt

string DecToBin(QInt Q)
{
	return Q.GetBinString();
}

string DecToHex(QInt Q)
{
	return Q.GetHexString();
}

QInt BinToDec(string x)
{
	QInt Q;
	Q.ScanBinString(x);
	return Q;
}

string BinToHex(string x)
{
	QInt Q;
	Q.ScanBinString(x);
	return Q.GetHexString();
}

QInt arithmeticQInt(string base, string x, char o, string y)
{
	QInt a, b;

	a.ScanQInt(x, base);
	b.ScanQInt(y, base);

	switch (o)
	{
	case '+':
		return (a + b);
	case '-':
		return (a - b);
	case '*':
		return (a * b);
	case '/':
		return (a / b);
	case '%':
		return (a % b);
	default:
		return a;
	}
}

QInt logicQInt(string base, string x, char o, string y)
{
	QInt a, b;

	a.ScanQInt(x, base);

	if (y != "") b.ScanQInt(y, base);

	switch (o)
	{
	case '~':
		return (~a);
	case '&':
		return (a & b);
	case '|':
		return (a | b);
	case '^':
		return (a ^ b);
	default:
		return a;
	}
}

QInt shiftQInt(string base, string x, string o, int k)
{
	QInt a;

	a.ScanQInt(x, base);

	if (o == ">>") return (a >> k);
	if (o == "<<") return (a << k);

	return a;
}

bool compareQInt(string base, string x, string o, string y)
{
	QInt a, b;

	a.ScanQInt(x, base);
	b.ScanQInt(y, base);

	if (o == ">") return (a > b);
	if (o == "<") return (a < b);
	if (o == "<=") return (a <= b);
	if (o == ">=") return (a >= b);
	if (o == "==") return (a == b);

	return 0;
}

string convertQInt(string a, string b, string x)
{
	QInt Q;

	Q.ScanQInt(x, a);

	return Q.GetQInt(b);
}

void processQInt()
{
	QInt ans;

	string a, b, c, d; int k;

	cin >> a >> b >> c;

	if (c == "+" || c == "-" || c == "*" || c == "/" || c == "%")
	{
		cin >> d;
		cout << arithmeticQInt(a, b, c[0], d).GetQInt(a) << endl;
	}
	else if (c == "&" || c == "|" || c == "^")
	{
		cin >> d;
		cout << logicQInt(a, b, c[0], d).GetQInt(a) << endl;
	}
	else if (b == "~")
	{
		cout << logicQInt(a, c, b[0], "").GetQInt(a) << endl;
	}
	else if (c == "<<" || c == ">>")
	{
		cin >> k;
		cout << shiftQInt(a, b, c, k).GetQInt(a) << endl;
	}
	else if (c == "<" || c == ">" || c == "<=" || c == ">=" || c == "==")
	{
		cin >> d;
		cout << boolalpha << compareQInt(a, b, c, d) << endl;
	}
	else cout << convertQInt(a, b, c) << endl;

}


int main(int argc, char* argv[])
{
	// overflow example
	// max =  2^127 - 1 =  170141183460469231731687303715884105727  
	// min = -2^127 + 0 = -170141183460469231731687303715884105728
	// QInt max;
	// max.ScanDecString("170141183460469231731687303715884105728");
	// cout << max.GetDecString() << endl;

	// compare with c++ overflow
	// int a = -2147483649;
	// int b = -2147483646;
	// cout << a + b << endl;
	/*
	if (argc == 3)
	{
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);

		if (argv[3][0] == '1')
			while (!cin.eof()) processQInt();
	}
	*/
	//Qfloat pos, neg;
	//pos.ScanDecString("5.75");
	//neg.ScanDecString("-5.75");
	//cout << pos.GetBinString() << endl << neg.GetBinString() << endl;
	Qfloat f, f1, f2;
	f1.ScanDecString("35.7");
	f2.ScanDecString("5.75");
	f = f1 - f2;
	cout << f.GetDecString();
	return 0;
}