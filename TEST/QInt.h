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
	void StringSum(string& s);

	void ScanBinString(string);
	void ScanDecString(string);
	//void ScanHexString(string);

	string GetBinString();
	string GetDecString();

};

#endif // !__QINT_H__