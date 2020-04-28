#include <iostream>
#include "QInt.h"

using namespace std;


int main()
{
	// overflow example
	// 2^127-1 = 170141183460469231731687303715884105727  
	// min = -2^127 = -170141183460469231731687303715884105728
	// QInt max;
	// max.ScanDecString("170141183460469231731687303715884105728");
	// cout << max.GetBinString() << endl;
	// cout << max.GetDecString() << endl << endl;
	

	QInt x, y, z;
	x.ScanDecString("-7");
	cout << x.GetBinString() << endl;
	y.ScanDecString("-3");
	cout << y.GetBinString() << endl;
	z = x / y;
	
	cout << x.GetDecString() << endl; // quotient
	cout << z.GetDecString() << endl; // remainder
	cout << endl;

	// compare with c++ overflow
	// int a = -2147483649;
	// int b = -2147483646;
	// cout << a + b << endl;
}