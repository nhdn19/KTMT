	#ifndef _QFLOAT_H__
#define _QFLOAT_H__
//2^-16494 -> (1 - 2^-112)2^-16382		2^-16382 -> 2^16383(2 - 2^-112)
//			range 1								range 2
#include <iostream>
#include "QInt.h"
using namespace std;

class Qfloat
{
private:
	int data[4];
	int size = 128;
public:
	Qfloat() { data[0] = data[1] = data[2] = data[3] = 0; }

	void ZeroBits(); // for reuse QInt
	void OffBit(int i); // bit_i = 0
	void SetBit(int i); // bit_i = 1
	bool GetBit(int i);

	void ScanDecString(string dec);
	void ScanBinString(string bin);
	string GetDecString();
	string GetBinString();

	Qfloat operator+(Qfloat);//just on positive number
	Qfloat operator-(Qfloat);

	//extra
	string getSign();//print sign
	string getExponent();//print exponent
	string getSignificand();
};

#endif