#include <iostream>
#include "QInt.h"

using namespace std;


int main()
{
	QInt Q;

	string s = "101111110001011011100011010011";

	Q.ScanBinString(s);

	cout << Q.GetBinString();
}