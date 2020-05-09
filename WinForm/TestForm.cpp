#define _CRT_SECURE_NO_WARNINGS
#include "TestForm.h"

using namespace System;
using namespace System::Windows::Forms;

// function to interact with QInt

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


// function to interact with Qfloat

Qfloat arithmeticQfloat(std::string base, std::string x, char o, std::string y)
{
	Qfloat a, b;

	a.ScanQfloat(x, base);
	b.ScanQfloat(y, base);

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
	default:
		return a;
	}
}

std::string convertQfloat(std::string a, std::string b, std::string x)
{
	Qfloat Q;

	Q.ScanQfloat(x, a);

	return Q.GetQfloat(b);
}

std::string processQfloat(std::string inputString)
{
	Qfloat ans;

	std::string a, b, c, d;

	std::stringstream ss(inputString);

	ss >> a >> b >> c;

	if (c == "+" || c == "-" || c == "*" || c == "/")
	{
		ss >> d;
		return arithmeticQfloat(a, b, c[0], d).GetQfloat(a);
	}
	else return convertQfloat(a, b, c);
}


void proStream(StreamReader^ input, StreamWriter^ output, std::string (*processQ)(std::string))
{
	while (1)
	{
		String^ inStream = input->ReadLine();
		if (inStream == nullptr) return;

		marshal_context context;
		std::string inString = context.marshal_as<std::string>(inStream);

		std::string ans = processQ(inString);

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
		
		if (args[2] == "1") proStream(input, output, processQInt);
		if (args[2] == "2") proStream(input, output, processQfloat);

		output->Close();
		input->Close();
	}	

	//Qfloat a;
	//////37.5 23.1
	//a.ScanDecString("1000.999999999999999999999999999999");

	//std::string z = a.GetDecString();
}