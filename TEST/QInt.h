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
	QInt() { OffBit(); } // bitset 0 at first

	void OffBit();
	void SetBit(int i);
	bool GetBit(int i);

	void ScanBinString(string);
	void ScanDecString(string);
	void ScanHexString(string); // duong done, not tested

	string GetBinString(); // tested work on both negative 
	string GetDecString(); // tested work on both nagative

	//string GetHexString(); // dat

	QInt operator+ (QInt& a); // duong done, not tested
	QInt operator- (QInt& a); // duong done, not tested
	QInt operator* (QInt& a); // nhdung
	QInt operator/ (const QInt& a); // nhdung
	QInt operator= (const QInt& a); 

	//QInt operator= (const string,const int type); 

	QInt operator& (QInt& a); // duong tested, done
	QInt operator| (QInt& a); // duong tested, done
	QInt operator^ (QInt& a); // duong tested, done
	QInt operator~ (); // duong tested, done

	QInt operator>> (int a); // dat
	QInt operator<< (int a); // dat

	QInt rol(int a); // nhdung
	QInt ror(int a); // nhdung

	bool operator< (QInt a); // dat
	bool operator> (QInt a); // dat
	bool operator<= (QInt a); // dat
	bool operator>= (QInt a);
	bool operator== (QInt a);


	//extra
	void printData();
};

#endif