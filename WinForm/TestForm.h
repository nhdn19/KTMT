#pragma once

#include "QInt.h"
#include <msclr\marshal_cppstd.h>

using namespace System::IO;
using namespace msclr::interop;

namespace WinForm 
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class TestForm : public System::Windows::Forms::Form
	{
	public:
		TestForm(void) { InitializeComponent(); }

	protected:
		~TestForm() { if (components) delete components; }

	private: System::Windows::Forms::TextBox^ Param1;
	private: System::Windows::Forms::TextBox^ Param2;
	private: System::Windows::Forms::Button^ Button0;
	private: System::Windows::Forms::Button^ Button1;
	private: System::Windows::Forms::Button^ Button2;
	private: System::Windows::Forms::Button^ Button3;
	private: System::Windows::Forms::Button^ Button4;
	private: System::Windows::Forms::Button^ Button5;
	private: System::Windows::Forms::Button^ Button6;
	private: System::Windows::Forms::Button^ Button7;
	private: System::Windows::Forms::Button^ Button8;
	private: System::Windows::Forms::Button^ Button9;
	private: System::Windows::Forms::TextBox^ Answer;
	private: System::Windows::Forms::Button^ AddButton;
	private: System::Windows::Forms::Button^ MultiplyButton;
	private: System::Windows::Forms::Button^ SubtractButton;
	private: System::Windows::Forms::Button^ DivideButton;
	private: System::Windows::Forms::Button^ ModButton;
	private: System::Windows::Forms::Button^ EqualButton;
	private: System::Windows::Forms::Button^ LessThanButton;
	private: System::Windows::Forms::Button^ GreaterThanButton;
	private: System::Windows::Forms::Button^ LessEqualToButton;
	private: System::Windows::Forms::Button^ GreaterEqualToButton;
	private: System::Windows::Forms::Button^ NotButton;
	private: System::Windows::Forms::Button^ XorButton;
	private: System::Windows::Forms::Button^ OrButton;
	private: System::Windows::Forms::Button^ AndButton;
	private: System::Windows::Forms::Button^ RotateLeft;
	private: System::Windows::Forms::Button^ RotateRight;
	private: System::Windows::Forms::Button^ LeftShift;
	private: System::Windows::Forms::Button^ RightShift;
	private: System::Windows::Forms::Button^ ClearButton;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->Param1 = (gcnew System::Windows::Forms::TextBox());
			this->Param2 = (gcnew System::Windows::Forms::TextBox());
			this->Button1 = (gcnew System::Windows::Forms::Button());
			this->Button2 = (gcnew System::Windows::Forms::Button());
			this->Button3 = (gcnew System::Windows::Forms::Button());
			this->Button4 = (gcnew System::Windows::Forms::Button());
			this->Button5 = (gcnew System::Windows::Forms::Button());
			this->Button6 = (gcnew System::Windows::Forms::Button());
			this->Button7 = (gcnew System::Windows::Forms::Button());
			this->Button8 = (gcnew System::Windows::Forms::Button());
			this->Button9 = (gcnew System::Windows::Forms::Button());
			this->Answer = (gcnew System::Windows::Forms::TextBox());
			this->AddButton = (gcnew System::Windows::Forms::Button());
			this->MultiplyButton = (gcnew System::Windows::Forms::Button());
			this->SubtractButton = (gcnew System::Windows::Forms::Button());
			this->DivideButton = (gcnew System::Windows::Forms::Button());
			this->ModButton = (gcnew System::Windows::Forms::Button());
			this->EqualButton = (gcnew System::Windows::Forms::Button());
			this->LessThanButton = (gcnew System::Windows::Forms::Button());
			this->GreaterThanButton = (gcnew System::Windows::Forms::Button());
			this->LessEqualToButton = (gcnew System::Windows::Forms::Button());
			this->GreaterEqualToButton = (gcnew System::Windows::Forms::Button());
			this->NotButton = (gcnew System::Windows::Forms::Button());
			this->XorButton = (gcnew System::Windows::Forms::Button());
			this->OrButton = (gcnew System::Windows::Forms::Button());
			this->AndButton = (gcnew System::Windows::Forms::Button());
			this->RotateLeft = (gcnew System::Windows::Forms::Button());
			this->RotateRight = (gcnew System::Windows::Forms::Button());
			this->LeftShift = (gcnew System::Windows::Forms::Button());
			this->RightShift = (gcnew System::Windows::Forms::Button());
			this->Button0 = (gcnew System::Windows::Forms::Button());
			this->ClearButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Param1
			// 
			this->Param1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Param1->Location = System::Drawing::Point(12, 12);
			this->Param1->Name = L"Param1";
			this->Param1->Size = System::Drawing::Size(1201, 80);
			this->Param1->TabIndex = 0;
			this->Param1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->Param1->TextChanged += gcnew System::EventHandler(this, &TestForm::Param1_TextChanged);
			// 
			// Param2
			// 
			this->Param2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Param2->Location = System::Drawing::Point(12, 98);
			this->Param2->Name = L"Param2";
			this->Param2->Size = System::Drawing::Size(1201, 80);
			this->Param2->TabIndex = 1;
			this->Param2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->Param2->TextChanged += gcnew System::EventHandler(this, &TestForm::Param2_TextChanged);
			// 
			// Button1
			// 
			this->Button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Button1->Location = System::Drawing::Point(12, 725);
			this->Button1->Name = L"Button1";
			this->Button1->Size = System::Drawing::Size(150, 100);
			this->Button1->TabIndex = 2;
			this->Button1->Text = L"1";
			this->Button1->UseVisualStyleBackColor = true;
			this->Button1->Click += gcnew System::EventHandler(this, &TestForm::Button1_Click);
			// 
			// Button2
			// 
			this->Button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Button2->Location = System::Drawing::Point(168, 725);
			this->Button2->Name = L"Button2";
			this->Button2->Size = System::Drawing::Size(150, 100);
			this->Button2->TabIndex = 3;
			this->Button2->Text = L"2";
			this->Button2->UseVisualStyleBackColor = true;
			this->Button2->Click += gcnew System::EventHandler(this, &TestForm::Button2_Click);
			// 
			// Button3
			// 
			this->Button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Button3->Location = System::Drawing::Point(324, 725);
			this->Button3->Name = L"Button3";
			this->Button3->Size = System::Drawing::Size(150, 100);
			this->Button3->TabIndex = 4;
			this->Button3->Text = L"3";
			this->Button3->UseVisualStyleBackColor = true;
			this->Button3->Click += gcnew System::EventHandler(this, &TestForm::Button3_Click);
			// 
			// Button4
			// 
			this->Button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Button4->Location = System::Drawing::Point(12, 619);
			this->Button4->Name = L"Button4";
			this->Button4->Size = System::Drawing::Size(150, 100);
			this->Button4->TabIndex = 5;
			this->Button4->Text = L"4";
			this->Button4->UseVisualStyleBackColor = true;
			this->Button4->Click += gcnew System::EventHandler(this, &TestForm::Button4_Click);
			// 
			// Button5
			// 
			this->Button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Button5->Location = System::Drawing::Point(168, 619);
			this->Button5->Name = L"Button5";
			this->Button5->Size = System::Drawing::Size(150, 100);
			this->Button5->TabIndex = 6;
			this->Button5->Text = L"5";
			this->Button5->UseVisualStyleBackColor = true;
			// 
			// Button6
			// 
			this->Button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Button6->Location = System::Drawing::Point(324, 619);
			this->Button6->Name = L"Button6";
			this->Button6->Size = System::Drawing::Size(150, 100);
			this->Button6->TabIndex = 7;
			this->Button6->Text = L"6";
			this->Button6->UseVisualStyleBackColor = true;
			this->Button6->Click += gcnew System::EventHandler(this, &TestForm::Button6_Click);
			// 
			// Button7
			// 
			this->Button7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Button7->Location = System::Drawing::Point(12, 513);
			this->Button7->Name = L"Button7";
			this->Button7->Size = System::Drawing::Size(150, 100);
			this->Button7->TabIndex = 8;
			this->Button7->Text = L"7";
			this->Button7->UseVisualStyleBackColor = true;
			this->Button7->Click += gcnew System::EventHandler(this, &TestForm::Button7_Click);
			// 
			// Button8
			// 
			this->Button8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Button8->Location = System::Drawing::Point(168, 513);
			this->Button8->Name = L"Button8";
			this->Button8->Size = System::Drawing::Size(150, 100);
			this->Button8->TabIndex = 9;
			this->Button8->Text = L"8";
			this->Button8->UseVisualStyleBackColor = true;
			this->Button8->Click += gcnew System::EventHandler(this, &TestForm::Button8_Click);
			// 
			// Button9
			// 
			this->Button9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Button9->Location = System::Drawing::Point(324, 513);
			this->Button9->Name = L"Button9";
			this->Button9->Size = System::Drawing::Size(150, 100);
			this->Button9->TabIndex = 10;
			this->Button9->Text = L"9";
			this->Button9->UseVisualStyleBackColor = true;
			this->Button9->Click += gcnew System::EventHandler(this, &TestForm::Button9_Click);
			// 
			// Answer
			// 
			this->Answer->Enabled = false;
			this->Answer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Answer->Location = System::Drawing::Point(12, 184);
			this->Answer->Name = L"Answer";
			this->Answer->Size = System::Drawing::Size(1201, 80);
			this->Answer->TabIndex = 11;
			this->Answer->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->Answer->TextChanged += gcnew System::EventHandler(this, &TestForm::Answer_TextChanged);
			// 
			// AddButton
			// 
			this->AddButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->AddButton->Location = System::Drawing::Point(529, 619);
			this->AddButton->Name = L"AddButton";
			this->AddButton->Size = System::Drawing::Size(150, 100);
			this->AddButton->TabIndex = 12;
			this->AddButton->Text = L"+";
			this->AddButton->UseVisualStyleBackColor = true;
			this->AddButton->Click += gcnew System::EventHandler(this, &TestForm::AddButton_Click);
			// 
			// MultiplyButton
			// 
			this->MultiplyButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->MultiplyButton->Location = System::Drawing::Point(529, 725);
			this->MultiplyButton->Name = L"MultiplyButton";
			this->MultiplyButton->Size = System::Drawing::Size(150, 100);
			this->MultiplyButton->TabIndex = 13;
			this->MultiplyButton->Text = L"×";
			this->MultiplyButton->UseVisualStyleBackColor = true;
			this->MultiplyButton->Click += gcnew System::EventHandler(this, &TestForm::MultiplyButton_Click);
			// 
			// SubtractButton
			// 
			this->SubtractButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->SubtractButton->Location = System::Drawing::Point(685, 619);
			this->SubtractButton->Name = L"SubtractButton";
			this->SubtractButton->Size = System::Drawing::Size(150, 100);
			this->SubtractButton->TabIndex = 14;
			this->SubtractButton->Text = L"−";
			this->SubtractButton->UseVisualStyleBackColor = true;
			this->SubtractButton->Click += gcnew System::EventHandler(this, &TestForm::SubtractButton_Click);
			// 
			// DivideButton
			// 
			this->DivideButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DivideButton->Location = System::Drawing::Point(685, 725);
			this->DivideButton->Name = L"DivideButton";
			this->DivideButton->Size = System::Drawing::Size(150, 100);
			this->DivideButton->TabIndex = 15;
			this->DivideButton->Text = L"÷";
			this->DivideButton->UseVisualStyleBackColor = true;
			this->DivideButton->Click += gcnew System::EventHandler(this, &TestForm::DivideButton_Click);
			// 
			// ModButton
			// 
			this->ModButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ModButton->Location = System::Drawing::Point(529, 831);
			this->ModButton->Name = L"ModButton";
			this->ModButton->Size = System::Drawing::Size(150, 100);
			this->ModButton->TabIndex = 16;
			this->ModButton->Text = L"⁒";
			this->ModButton->UseVisualStyleBackColor = true;
			this->ModButton->Click += gcnew System::EventHandler(this, &TestForm::ModButton_Click);
			// 
			// EqualButton
			// 
			this->EqualButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->EqualButton->Location = System::Drawing::Point(685, 831);
			this->EqualButton->Name = L"EqualButton";
			this->EqualButton->Size = System::Drawing::Size(150, 100);
			this->EqualButton->TabIndex = 17;
			this->EqualButton->Text = L"=";
			this->EqualButton->UseVisualStyleBackColor = true;
			// 
			// LessThanButton
			// 
			this->LessThanButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->LessThanButton->Location = System::Drawing::Point(685, 513);
			this->LessThanButton->Name = L"LessThanButton";
			this->LessThanButton->Size = System::Drawing::Size(150, 100);
			this->LessThanButton->TabIndex = 18;
			this->LessThanButton->Text = L"<";
			this->LessThanButton->UseVisualStyleBackColor = true;
			// 
			// GreaterThanButton
			// 
			this->GreaterThanButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->GreaterThanButton->Location = System::Drawing::Point(529, 513);
			this->GreaterThanButton->Name = L"GreaterThanButton";
			this->GreaterThanButton->Size = System::Drawing::Size(150, 100);
			this->GreaterThanButton->TabIndex = 19;
			this->GreaterThanButton->Text = L">";
			this->GreaterThanButton->UseVisualStyleBackColor = true;
			// 
			// LessEqualToButton
			// 
			this->LessEqualToButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->LessEqualToButton->Location = System::Drawing::Point(685, 407);
			this->LessEqualToButton->Name = L"LessEqualToButton";
			this->LessEqualToButton->Size = System::Drawing::Size(150, 100);
			this->LessEqualToButton->TabIndex = 20;
			this->LessEqualToButton->Text = L"≤";
			this->LessEqualToButton->UseVisualStyleBackColor = true;
			// 
			// GreaterEqualToButton
			// 
			this->GreaterEqualToButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->GreaterEqualToButton->Location = System::Drawing::Point(529, 407);
			this->GreaterEqualToButton->Name = L"GreaterEqualToButton";
			this->GreaterEqualToButton->Size = System::Drawing::Size(150, 100);
			this->GreaterEqualToButton->TabIndex = 21;
			this->GreaterEqualToButton->Text = L"≥";
			this->GreaterEqualToButton->UseVisualStyleBackColor = true;
			// 
			// NotButton
			// 
			this->NotButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NotButton->Location = System::Drawing::Point(1045, 831);
			this->NotButton->Name = L"NotButton";
			this->NotButton->Size = System::Drawing::Size(150, 100);
			this->NotButton->TabIndex = 22;
			this->NotButton->Text = L"NOT";
			this->NotButton->UseVisualStyleBackColor = true;
			// 
			// XorButton
			// 
			this->XorButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->XorButton->Location = System::Drawing::Point(889, 831);
			this->XorButton->Name = L"XorButton";
			this->XorButton->Size = System::Drawing::Size(150, 100);
			this->XorButton->TabIndex = 23;
			this->XorButton->Text = L"XOR";
			this->XorButton->UseVisualStyleBackColor = true;
			// 
			// OrButton
			// 
			this->OrButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->OrButton->Location = System::Drawing::Point(1045, 725);
			this->OrButton->Name = L"OrButton";
			this->OrButton->Size = System::Drawing::Size(150, 100);
			this->OrButton->TabIndex = 24;
			this->OrButton->Text = L"OR";
			this->OrButton->UseVisualStyleBackColor = true;
			// 
			// AndButton
			// 
			this->AndButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->AndButton->Location = System::Drawing::Point(889, 725);
			this->AndButton->Name = L"AndButton";
			this->AndButton->Size = System::Drawing::Size(150, 100);
			this->AndButton->TabIndex = 25;
			this->AndButton->Text = L"AND";
			this->AndButton->UseVisualStyleBackColor = true;
			// 
			// RotateLeft
			// 
			this->RotateLeft->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RotateLeft->Location = System::Drawing::Point(889, 619);
			this->RotateLeft->Name = L"RotateLeft";
			this->RotateLeft->Size = System::Drawing::Size(150, 100);
			this->RotateLeft->TabIndex = 26;
			this->RotateLeft->Text = L"LRO";
			this->RotateLeft->UseVisualStyleBackColor = true;
			// 
			// RotateRight
			// 
			this->RotateRight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RotateRight->Location = System::Drawing::Point(1045, 619);
			this->RotateRight->Name = L"RotateRight";
			this->RotateRight->Size = System::Drawing::Size(150, 100);
			this->RotateRight->TabIndex = 27;
			this->RotateRight->Text = L"RRO";
			this->RotateRight->UseVisualStyleBackColor = true;
			// 
			// LeftShift
			// 
			this->LeftShift->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LeftShift->Location = System::Drawing::Point(889, 513);
			this->LeftShift->Name = L"LeftShift";
			this->LeftShift->Size = System::Drawing::Size(150, 100);
			this->LeftShift->TabIndex = 28;
			this->LeftShift->Text = L"LSH";
			this->LeftShift->UseVisualStyleBackColor = true;
			// 
			// RightShift
			// 
			this->RightShift->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RightShift->Location = System::Drawing::Point(1045, 513);
			this->RightShift->Name = L"RightShift";
			this->RightShift->Size = System::Drawing::Size(150, 100);
			this->RightShift->TabIndex = 29;
			this->RightShift->Text = L"RSH";
			this->RightShift->UseVisualStyleBackColor = true;
			// 
			// Button0
			// 
			this->Button0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Button0->Location = System::Drawing::Point(12, 831);
			this->Button0->Name = L"Button0";
			this->Button0->Size = System::Drawing::Size(150, 100);
			this->Button0->TabIndex = 31;
			this->Button0->Text = L"0";
			this->Button0->UseVisualStyleBackColor = true;
			this->Button0->Click += gcnew System::EventHandler(this, &TestForm::Button0_Click);
			// 
			// ClearButton
			// 
			this->ClearButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.125F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ClearButton->Location = System::Drawing::Point(324, 834);
			this->ClearButton->Name = L"ClearButton";
			this->ClearButton->Size = System::Drawing::Size(150, 100);
			this->ClearButton->TabIndex = 32;
			this->ClearButton->Text = L"AC";
			this->ClearButton->UseVisualStyleBackColor = true;
			this->ClearButton->Click += gcnew System::EventHandler(this, &TestForm::ClearButton_Click);
			// 
			// TestForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1232, 943);
			this->Controls->Add(this->ClearButton);
			this->Controls->Add(this->Button0);
			this->Controls->Add(this->RightShift);
			this->Controls->Add(this->LeftShift);
			this->Controls->Add(this->RotateRight);
			this->Controls->Add(this->RotateLeft);
			this->Controls->Add(this->AndButton);
			this->Controls->Add(this->OrButton);
			this->Controls->Add(this->XorButton);
			this->Controls->Add(this->NotButton);
			this->Controls->Add(this->GreaterEqualToButton);
			this->Controls->Add(this->LessEqualToButton);
			this->Controls->Add(this->GreaterThanButton);
			this->Controls->Add(this->LessThanButton);
			this->Controls->Add(this->EqualButton);
			this->Controls->Add(this->ModButton);
			this->Controls->Add(this->DivideButton);
			this->Controls->Add(this->SubtractButton);
			this->Controls->Add(this->MultiplyButton);
			this->Controls->Add(this->AddButton);
			this->Controls->Add(this->Answer);
			this->Controls->Add(this->Button9);
			this->Controls->Add(this->Button8);
			this->Controls->Add(this->Button7);
			this->Controls->Add(this->Button6);
			this->Controls->Add(this->Button5);
			this->Controls->Add(this->Button4);
			this->Controls->Add(this->Button3);
			this->Controls->Add(this->Button2);
			this->Controls->Add(this->Button1);
			this->Controls->Add(this->Param2);
			this->Controls->Add(this->Param1);
			this->Name = L"TestForm";
			this->Text = L"TestForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void Param1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void Param2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void Answer_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		}

		private: System::Void Button0_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void Button1_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void Button2_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void Button3_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void Button4_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void Button6_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void Button7_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void Button8_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void Button9_Click(System::Object^ sender, System::EventArgs^ e) {
		}

		private: System::Void ClearButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			Param1->Text = "";
			Param2->Text = "";
			Answer->Text = "";
		}
	
		private: System::Void AddButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			marshal_context context;
			std::string x = context.marshal_as<std::string>(Param1->Text);
			std::string y = context.marshal_as<std::string>(Param2->Text);

			QInt A, B, C;
			A.ScanDecString(x);
			B.ScanDecString(y);
			Answer->Text = gcnew String((A + B).GetDecString().c_str());
		}

		private: System::Void SubtractButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			marshal_context context;
			std::string x = context.marshal_as<std::string>(Param1->Text);
			std::string y = context.marshal_as<std::string>(Param2->Text);

			QInt A, B, C;
			A.ScanDecString(x);
			B.ScanDecString(y);
			Answer->Text = gcnew String((A - B).GetDecString().c_str());
		}
		
		private: System::Void MultiplyButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			marshal_context context;
			std::string x = context.marshal_as<std::string>(Param1->Text);
			std::string y = context.marshal_as<std::string>(Param2->Text);

			QInt A, B, C;
			A.ScanDecString(x);
			B.ScanDecString(y);
			Answer->Text = gcnew String((A * B).GetDecString().c_str());
		}

		private: System::Void DivideButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			marshal_context context;
			std::string x = context.marshal_as<std::string>(Param1->Text);
			std::string y = context.marshal_as<std::string>(Param2->Text);

			QInt A, B, C;
			A.ScanDecString(x);
			B.ScanDecString(y);
			Answer->Text = gcnew String((A / B).GetDecString().c_str());
		}

		private: System::Void ModButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			marshal_context context;
			std::string x = context.marshal_as<std::string>(Param1->Text);
			std::string y = context.marshal_as<std::string>(Param2->Text);

			QInt A, B, C;
			A.ScanDecString(x);
			B.ScanDecString(y);
			Answer->Text = gcnew String((A % B).GetDecString().c_str());
		}

};
}
