#define _CRT_SECURE_NO_WARNINGS
#include "TestForm.h"

using namespace System;
using namespace System::Windows::Forms;

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
		output->WriteLine(input->ReadLine());
		
		for (int i = 0; i < args->Length; i++)
			output->WriteLine(args[i]);

		output->Close();
		input->Close();
	}	
}