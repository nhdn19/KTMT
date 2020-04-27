#include <iostream>
#include "QInt.h"

using namespace std;

//string DecToBin(QInt x)
//{
//	x.GetBinString();
//	return "";
//}
//
//QInt BinToDec(string x)
//{
//	QInt q;
//
//	q.ScanBinString(x);
//
//	return q;
//}


int main()
{
	//2^127-1 = 170141183460469231731687303715884105727  
	//min = -2^127 = -170141183460469231731687303715884105728
	QInt max;
	max.ScanDecString("170141183460469231731687303715884105728");//input overflow
	cout << max.GetBinString() << endl;
	cout << max.GetDecString() << endl;
	QInt d1, d2, d3;
	d1.ScanDecString("3123");
	d2.ScanDecString("3123");
	d3 = d1 + d2;
	cout << d3.GetDecString() << endl;
	//cout << d1.GetBinString() << endl;
	//cout << d2.GetBinString() << endl;
	//cout << d3.GetBinString() << endl;
}