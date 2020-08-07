#include "Calculator.h"

using namespace System;
using namespace System::Windows::Forms;


// function to interact with QInt


// handle arithmetic operation of QInt
std::string arithmeticQInt(std::string base, std::string x, char o, std::string y)
{
	QInt a, b, c;

	a.ScanQInt(x, base);
	b.ScanQInt(y, base);

	if (o == '/' && b == c) return "Math Error";

	switch (o)
	{
	case '+':
		return (a + b).GetQInt(base);
	case '-':
		return (a - b).GetQInt(base);
	case '*':
		return (a * b).GetQInt(base);
	case '/':
		return (a / b).GetQInt(base);
	case '%':
		return (a % b).GetQInt(base);
	default:
		return a.GetQInt(base);
	}
}

// handle logical operation of QInt
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

// handle shift operation of QInt
QInt shiftQInt(std::string base, std::string x, std::string o, int k)
{
	QInt a;

	a.ScanQInt(x, base);

	if (o == ">>") return (a >> k);
	if (o == "<<") return (a << k);
	if (o == "rol") return (a.rol(k));
	if (o == "ror") return (a.ror(k));

	return a;
}

// handle comparison operation of QInt
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

// convert QInt form type a to type b
std::string convertQInt(std::string a, std::string b, std::string x)
{
	QInt Q;

	Q.ScanQInt(x, a);

	return Q.GetQInt(b);
}

// map each case of input string to specific function
std::string processQInt(std::string inputString)
{
	QInt ans;

	std::string a, b, c, d; int k;

	std::stringstream ss(inputString);

	ss >> a >> b >> c;

	if (c == "+" || c == "-" || c == "*" || c == "/" || c == "%")
	{
		ss >> d;
		return arithmeticQInt(a, b, c[0], d);
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
	else if (c == "<<" || c == ">>" || c == "ror" || c == "rol")
	{
		ss >> k;
		return shiftQInt(a, b, c, k).GetQInt(a);
	}
	else if (c == "<" || c == ">" || c == "<=" || c == ">=" || c == "==")
	{
		ss >> d;
		return compareQInt(a, b, c, d) ? "true" : "false";
	}
	else return convertQInt(a, b, c);

}


// function to interact with QFloat


// handle arithmetic operation of QFloat
QFloat arithmeticQFloat(std::string base, std::string x, char o, std::string y)
{
	QFloat a, b;

	a.ScanQFloat(x, base);
	b.ScanQFloat(y, base);

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

// convert QFloat from type a to type b
std::string convertQFloat(std::string a, std::string b, std::string x)
{
	QFloat Q;

	Q.ScanQFloat(x, a);

	return Q.GetQFloat(b);
}

// map each case of input string to specific function
std::string processQFloat(std::string inputString)
{
	QFloat ans;

	std::string a, b, c, d;

	std::stringstream ss(inputString);

	ss >> a >> b >> c;

	if (c == "+" || c == "-" || c == "*" || c == "/")
	{
		ss >> d;
		return arithmeticQFloat(a, b, c[0], d).GetQFloat(a);
	}
	else return convertQFloat(a, b, c);
}

// convert from system input stream to std string for process and then reconvert
void proStream(StreamReader^ input, StreamWriter^ output, std::string(*processQ)(std::string))
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
		_18120015_18120019_18120020::Calculator form;
		Application::Run(% form);
	}
	else
	{
		StreamReader^ input = gcnew StreamReader(args[0]); // read file name of input file
		StreamWriter^ output = gcnew StreamWriter(args[1]); // read file name of output file

		if (args[2] == "1") proStream(input, output, processQInt);
		if (args[2] == "2") proStream(input, output, processQFloat);

		output->Close();
		input->Close();
	}
}