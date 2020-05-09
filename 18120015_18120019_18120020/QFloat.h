#ifndef _QFLOAT_H__
#define _QFLOAT_H__

#include "QInt.h"

//2^-16494 -> (1 - 2^-112)2^-16382		2^-16382 -> 2^16383(2 - 2^-112)
//			range 1								range 2

class QFloat
{
private:
	int data[4];
	int size = 128;
public:
	QFloat() { ZeroBits(); }

	void ZeroBits(); // for reuse QInt
	void OffBit(int i); // bit_i = 0
	void SetBit(int i); // bit_i = 1
	bool GetBit(int i);

	void ScanDecString(std::string dec);
	void ScanBinString(std::string bin);
	void ScanQFloat(std::string, std::string);

	std::string GetDecString();
	std::string GetBinString();
	std::string GetQFloat(std::string);

	QFloat operator + (QFloat);
	QFloat operator - (QFloat);
	QFloat operator * (QFloat);
	QFloat operator / (QFloat);
	bool operator == (QFloat);

	//extra
	QFloat operator = (const QFloat&);
	std::string getBitBetween(int i, int j); //i>=j;
	std::string getSign();//print sign
	std::string getExponent();//print exponent
	std::string getSignificand();
	int GetExponentDec();

	std::string multi2String(std::string, std::string);
	static std::string sum2String(std::string, std::string);
	static std::string divide2String(std::string, std::string);
	std::string roundbyGroup(std::string);
};

#endif