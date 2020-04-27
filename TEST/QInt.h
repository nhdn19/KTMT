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
	QInt() { OffBit(); } // ban dau thi bit toan 0

	void OffBit();
	void SetBit(int i);
	bool GetBit(int i);

	bool DivideByTwo(string& s);
	void MultiplyByTwo(string& s);
	void StringSum(string& s, string a);

	void ScanBinString(string);
	void ScanDecString(string);
	
	//void ScanHexString(string) // duong

	string GetBinString();
	string GetDecString(); // print dec string

	//string GetHexString(); // dat

	QInt operator+ (const QInt& a); // duong
	QInt operator- (const QInt& a); // duong
	QInt operator* (const QInt& a); // moi nguoi tu viet
	QInt operator/ (const QInt& a); // nhdung
	QInt operator= (const QInt& a); 

	QInt operator& (const QInt& a); // duong
	QInt operator| (const QInt& a); // duong
	QInt operator^ (const QInt& a); // duong
	QInt operator~ (); // duong

	QInt operator>> (int a); // dat
	QInt operator<< (int a); // dat

	QInt rol(int a); // nhdung
	QInt ror(int a); // nhdung

	bool operator< (const QInt& a); // dat
	bool operator> (const QInt& a); // dat
	bool operator<= (const QInt& a); // dat
	bool operator>= (const QInt& a);
	bool operator== (const QInt& a);

};

#endif // !__QINT_H__