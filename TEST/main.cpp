#include <iostream>
using namespace std;

//take bits from left -> right
// change master
int divBy2(string& s)
{
	int r = 0;
	string q = "";

	for (int i = 0; i < s.length(); i++)
	{
		r = r * 10 + s[i] - '0';

		char c = r / 2 + '0';

		q = q + c;

		r = r % 2;
	}

	s = q;

	return r;
}

int main()
{
	cout << "Init Project" << endl;

	string s = "1287579";

	int r = divBy2(s);

	cout << r << ' ' << s << endl;
}