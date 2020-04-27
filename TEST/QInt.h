#ifndef __QINT_H__
#define __QINT_H__

#include <iostream>
#include <string>

using namespace std;



class QInt
{
private:
	int data[4];

public:

	void OffBit();
	void SetBit(int i);
	bool GetBit(int i);

	bool DivideByTwo(string& s);
	void MultiplyByTwo(string& s);
	void StringSum(string& s, string a);

	void ScanBinString(string);
	void ScanDecString(string);
	
	//void ScanHexString(string);

	string GetBinString();
	string GetDecString(); // print dec string

	//string GetHexString();

	QInt operator+ (const QInt& a);
	QInt operator- (const QInt& a);
	QInt operator* (const QInt& a);
	QInt operator/ (const QInt& a);
	QInt operator= (const QInt& a);

	QInt operator& (const QInt& a);
	QInt operator| (const QInt& a);
	QInt operator^ (const QInt& a);
	QInt operator~ ();

	QInt operator>> (int a);
	QInt operator<< (int a);

	QInt rol(int a);
	QInt ror(int a);

	bool operator< (const QInt& a);
	bool operator> (const QInt& a);
	bool operator<= (const QInt& a);
	bool operator>= (const QInt& a);
	bool operator== (const QInt& a);

};

#endif // !__QINT_H__