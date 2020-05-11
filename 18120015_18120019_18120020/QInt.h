#ifndef __QINT_H__
#define __QINT_H__

#include <iostream>
#include <string>

class QInt
{
private:

	int size = 128; // number of bits
	int data[4]; // block of 32 bits

public:
	QInt();
	QInt(std::string str) { ScanDecString(str); }

	void ZeroBits(); // for reuse QInt
	void OffBit(int i); // bit_i = 0
	void SetBit(int i); // bit_i = 1
	bool GetBit(int i);

	void ScanBinString(std::string);
	void ScanDecString(std::string);
	void ScanHexString(std::string);
	void ScanQInt(std::string, std::string);

	std::string GetBinString();
	std::string GetDecString(); 
	std::string GetHexString(); 
	std::string GetQInt(std::string);

	QInt operator ++ (); 
	QInt operator + (QInt); 
	QInt operator - (QInt); 
	QInt operator * (QInt); 
	QInt operator / (QInt); 
	QInt operator % (QInt);
	QInt operator = (const QInt&);
	QInt operator = (const std::string); 

	QInt operator & (QInt&); 
	QInt operator | (QInt&); 
	QInt operator ^ (QInt&); 
	QInt operator ~ (); 

	QInt operator>> (int); 
	QInt operator<< (int); 

	QInt rol(int); 
	QInt ror(int); 

	bool operator < (QInt); 
	bool operator > (QInt); 
	bool operator <= (QInt); 
	bool operator >= (QInt);
	bool operator == (QInt);
};

int divideBy2(std::string& str);
void multiplyBy2(std::string& str);
void add1ToString(std::string& str);

#endif