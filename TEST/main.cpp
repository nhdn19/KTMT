#include <iostream>
#include "QInt.h"

using namespace std;

string DecToBin(QInt x)
{
	x.GetBinString();
}

QInt BinToDec(string x)
{
	QInt q;

	q.ScanBinString(x);



	return q;
}


int main()
{
	QInt Q;

	string s = "101111110001011011100011010011";

	string z = "801487059";

	Q.ScanBinString(s);

	cout << Q.GetBinString() << endl;

	cout << Q.GetDecString() << endl;
	
}