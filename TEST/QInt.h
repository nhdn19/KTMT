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
	QInt();
	~QInt();

	int divBy2(string &s);

	//QInt& operator = (const string&);

	friend istream& operator >> (istream&, QInt&);
};

#endif // !__QINT_H__