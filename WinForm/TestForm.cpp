#define _CRT_SECURE_NO_WARNINGS
#include "TestForm.h"

using namespace System;
using namespace System::Windows::Forms;

QInt arithmeticQInt(std::string base, std::string x, char o, std::string y)
{
	QInt a, b;

	a.ScanQInt(x, base);
	b.ScanQInt(y, base);

	switch (o)
	{
	case '+':
		return (a + b);
	case '-':
		return (a - b);
	case '*':
		return (a * b);
	case '/':
		return (a / b);
	case '%':
		return (a % b);
	default:
		return a;
	}
}

QInt logicQInt(std::string base, std::string x, char o, std::string y)
{
	QInt a, b;

	a.ScanQInt(x, base);

	if (y != "") b.ScanQInt(y, base);

	switch (o)
	{
	case '~':
		return (~a);
	case '&':
		return (a & b);
	case '|':
		return (a | b);
	case '^':
		return (a ^ b);
	default:
		return a;
	}
}

QInt shiftQInt(std::string base, std::string x, std::string o, int k)
{
	QInt a;

	a.ScanQInt(x, base);

	if (o == ">>") return (a >> k);
	if (o == "<<") return (a << k);

	return a;
}

bool compareQInt(std::string base, std::string x, std::string o, std::string y)
{
	QInt a, b;

	a.ScanQInt(x, base);
	b.ScanQInt(y, base);

	if (o == ">") return (a > b);
	if (o == "<") return (a < b);
	if (o == "<=") return (a <= b);
	if (o == ">=") return (a >= b);
	if (o == "==") return (a == b);

	return 0;
}

std::string convertQInt(std::string a, std::string b, std::string x)
{
	QInt Q;

	Q.ScanQInt(x, a);

	return Q.GetQInt(b);
}

std::string processQInt(std::string inputString)
{
	QInt ans;

	std::string a, b, c, d; int k;

	std::stringstream ss(inputString);

	ss >> a >> b >> c;

	if (c == "+" || c == "-" || c == "*" || c == "/" || c == "%")
	{
		ss >> d;
		return arithmeticQInt(a, b, c[0], d).GetQInt(a);
	}
	else if (c == "&" || c == "|" || c == "^")
	{
		ss >> d;
		return logicQInt(a, b, c[0], d).GetQInt(a);
	}
	else if (b == "~")
	{
		return logicQInt(a, c, b[0], "").GetQInt(a);
	}
	else if (c == "<<" || c == ">>")
	{
		ss >> k;
		return shiftQInt(a, b, c, k).GetQInt(a);
	}
	else if (c == "<" || c == ">" || c == "<=" || c == ">=" || c == "==")
	{
		ss >> k;
		return compareQInt(a, b, c, d) ? "True" : "False";
	}
	else return convertQInt(a, b, c);

}


void proStream(StreamReader^ input, StreamWriter^ output)
{
	while (1)
	{
		String^ inStream = input->ReadLine();
		if (inStream == nullptr) return;

		marshal_context context;
		std::string inString = context.marshal_as<std::string>(inStream);

		std::string ans = processQInt(inString);

		String^ outStream = gcnew String(ans.c_str());

		output->WriteLine(outStream);
	}
}

[STAThreadAttribute]
void Main(array<String^>^ args) 
{
	if (args->Length == 0)
	{
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		WinForm::TestForm form;
		Application::Run(% form);
	}
	else
	{
		StreamReader^ input = gcnew StreamReader(args[0]);
		StreamWriter^ output = gcnew StreamWriter(args[1]);
		
		proStream(input, output);

		output->Close();
		input->Close();
	}	
}