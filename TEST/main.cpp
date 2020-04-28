#include <iostream>
#include "QInt.h"

using namespace std;


int main()
{
	// overflow example
	// 2^127-1 = 170141183460469231731687303715884105727  
	// min = -2^127 = -170141183460469231731687303715884105728
	QInt max;
	max.ScanDecString("170141183460469231731687303715884105728");
	cout << max.GetBinString() << endl;
	cout << max.GetDecString() << endl << endl;
	

	QInt q;
	q.ScanDecString("874238130414891884104938493930401344");
	cout << q.GetBinString() << endl;
	cout << q.GetDecString() << endl;
	q << 1;
	cout << q.GetBinString() << endl;
	cout << q.GetDecString() << endl;
}