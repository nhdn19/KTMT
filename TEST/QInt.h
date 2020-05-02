#ifndef __QINT_H__
#define __QINT_H__

#include <iostream>
#include <string>

using namespace std;



class QInt
{
private:

	int size = 128; // number of bits
	int data[4]; // block of 32 bits

public:
	QInt();

	void ZeroBits(); // for reuse QInt
	void OffBit(int i); // bit_i = 0
	void SetBit(int i); // bit_i = 1
	bool GetBit(int i);

	void ScanBinString(string);
	void ScanDecString(string);
	void ScanHexString(string); // duong done, all tested
	void ScanQInt(string, string);

	string GetBinString(); // tested work on both negative 
	string GetDecString(); // tested work on both nagative
	string GetHexString(); // dat
	string GetQInt(string);

	QInt operator ++ (); // dung done
	QInt operator + (QInt); // duong done, dung tested
	QInt operator - (QInt); // duong done, dung tested
	QInt operator * (QInt); // nhdung, slight tested
	QInt operator / (QInt); // nhdung, tested with 7/3
	QInt operator % (QInt);
	QInt operator = (const QInt&); 
	QInt operator = (const string); // for only decimal 

	QInt operator & (QInt&); // duong tested, done
	QInt operator | (QInt&); // duong tested, done
	QInt operator ^ (QInt&); // duong tested, done
	QInt operator ~ (); // duong tested, done

	QInt operator>> (int); // dat
	QInt operator<< (int); // dat

	QInt rol(int); // nhdung
	QInt ror(int); // nhdung

	bool operator < (QInt); // dat
	bool operator > (QInt); // dat
	bool operator <= (QInt); // dat
	bool operator >= (QInt);
	bool operator == (QInt);


	//extra
	void printData();
};

#endif