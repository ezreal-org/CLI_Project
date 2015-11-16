#pragma once

//定义库文件与全局变量
#include<stdlib.h>
#include<string>
#include<iomanip>
#include<cmath>
#include <sstream>
#include <iostream>
#include "jayce.h"
#include "childForm.h"
#include "keyTest.h"
#include "netClient.h"
#include "netServer.h"
#include "followForm.h"
#include "judge.h"
using namespace Calculator;

extern __declspec(dllimport) string tkCalculator(string);

namespace Calculator{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	using namespace System::Threading;
	using  wordDLL::wordCheck;
				  /// <summary>
				  /// Form1 摘要
				  /// </summary>
	public ref class calForm : public System::Windows::Forms::Form
	{
	public:
		calForm(void)
		{
			InitializeComponent();
			tkInit(); //自定义变量初始化
			//
			//TODO: 在此处添加构造函数代码
			//
		}
		

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~calForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::LinkLabel^  linkLabel1;
	private: System::Windows::Forms::Button^  btn_one;
	private: System::Windows::Forms::Button^  btn_two;
	private: System::Windows::Forms::Button^  btn_three;
	private: System::Windows::Forms::Button^  bnt_four;
	private: System::Windows::Forms::Button^  btn_five;
	private: System::Windows::Forms::Button^  btn_six;
	private: System::Windows::Forms::Button^  btn_seven;
	private: System::Windows::Forms::Button^  btn_eight;
	private: System::Windows::Forms::Button^  btn_nine;
	private: System::Windows::Forms::Button^  btn_zero;
	private: System::Windows::Forms::Button^  btn_add;
	private: System::Windows::Forms::Button^  btn_sub;
	private: System::Windows::Forms::Button^  btn_multi;
	private: System::Windows::Forms::Button^  btn_div;
	private: System::Windows::Forms::Button^  btn_dot;
	private: System::Windows::Forms::Button^  btn_rightBracket;
	private: System::Windows::Forms::TextBox^  tb_calculateWindow;
	private: System::Windows::Forms::Button^  btn_calculate;
	private: System::Windows::Forms::Button^  btn_del;
	private: System::Windows::Forms::Button^  btn_leftBracket;
	private: System::Windows::Forms::Label^  label_jayce;
	private: System::Windows::Forms::Button^  btn_negtive;

	private: Boolean isWaiting;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void tkInit()  //完成一些自定义初始化操作
		{
			isWaiting = true;
			this->StartPosition = FormStartPosition::CenterScreen;
		}
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(calForm::typeid));
			this->btn_one = (gcnew System::Windows::Forms::Button());
			this->btn_two = (gcnew System::Windows::Forms::Button());
			this->btn_three = (gcnew System::Windows::Forms::Button());
			this->bnt_four = (gcnew System::Windows::Forms::Button());
			this->btn_five = (gcnew System::Windows::Forms::Button());
			this->btn_six = (gcnew System::Windows::Forms::Button());
			this->btn_seven = (gcnew System::Windows::Forms::Button());
			this->btn_eight = (gcnew System::Windows::Forms::Button());
			this->btn_nine = (gcnew System::Windows::Forms::Button());
			this->btn_zero = (gcnew System::Windows::Forms::Button());
			this->btn_add = (gcnew System::Windows::Forms::Button());
			this->btn_sub = (gcnew System::Windows::Forms::Button());
			this->btn_multi = (gcnew System::Windows::Forms::Button());
			this->btn_div = (gcnew System::Windows::Forms::Button());
			this->btn_dot = (gcnew System::Windows::Forms::Button());
			this->btn_rightBracket = (gcnew System::Windows::Forms::Button());
			this->tb_calculateWindow = (gcnew System::Windows::Forms::TextBox());
			this->btn_calculate = (gcnew System::Windows::Forms::Button());
			this->btn_del = (gcnew System::Windows::Forms::Button());
			this->btn_leftBracket = (gcnew System::Windows::Forms::Button());
			this->label_jayce = (gcnew System::Windows::Forms::Label());
			this->btn_negtive = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btn_one
			// 
			this->btn_one->FlatAppearance->BorderSize = 0;
			this->btn_one->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_one->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_one->Location = System::Drawing::Point(14, 171);
			this->btn_one->Name = L"btn_one";
			this->btn_one->Size = System::Drawing::Size(34, 24);
			this->btn_one->TabIndex = 2;
			this->btn_one->Text = L"1";
			this->btn_one->UseVisualStyleBackColor = true;
			this->btn_one->Click += gcnew System::EventHandler(this, &calForm::btn_one_Click);
			// 
			// btn_two
			// 
			this->btn_two->FlatAppearance->BorderSize = 0;
			this->btn_two->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_two->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_two->Location = System::Drawing::Point(54, 171);
			this->btn_two->Name = L"btn_two";
			this->btn_two->Size = System::Drawing::Size(34, 24);
			this->btn_two->TabIndex = 3;
			this->btn_two->Text = L"2";
			this->btn_two->UseVisualStyleBackColor = true;
			this->btn_two->Click += gcnew System::EventHandler(this, &calForm::btn_two_Click);
			// 
			// btn_three
			// 
			this->btn_three->FlatAppearance->BorderSize = 0;
			this->btn_three->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_three->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_three->Location = System::Drawing::Point(94, 171);
			this->btn_three->Name = L"btn_three";
			this->btn_three->Size = System::Drawing::Size(34, 24);
			this->btn_three->TabIndex = 4;
			this->btn_three->Text = L"3";
			this->btn_three->UseVisualStyleBackColor = true;
			this->btn_three->Click += gcnew System::EventHandler(this, &calForm::btn_three_Click);
			// 
			// bnt_four
			// 
			this->bnt_four->FlatAppearance->BorderSize = 0;
			this->bnt_four->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bnt_four->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->bnt_four->Location = System::Drawing::Point(14, 141);
			this->bnt_four->Name = L"bnt_four";
			this->bnt_four->Size = System::Drawing::Size(34, 24);
			this->bnt_four->TabIndex = 5;
			this->bnt_four->Text = L"4";
			this->bnt_four->UseVisualStyleBackColor = true;
			this->bnt_four->Click += gcnew System::EventHandler(this, &calForm::bnt_four_Click);
			// 
			// btn_five
			// 
			this->btn_five->FlatAppearance->BorderSize = 0;
			this->btn_five->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_five->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_five->Location = System::Drawing::Point(54, 141);
			this->btn_five->Name = L"btn_five";
			this->btn_five->Size = System::Drawing::Size(34, 24);
			this->btn_five->TabIndex = 6;
			this->btn_five->Text = L"5";
			this->btn_five->UseVisualStyleBackColor = true;
			this->btn_five->Click += gcnew System::EventHandler(this, &calForm::btn_five_Click);
			// 
			// btn_six
			// 
			this->btn_six->FlatAppearance->BorderSize = 0;
			this->btn_six->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_six->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_six->Location = System::Drawing::Point(94, 141);
			this->btn_six->Name = L"btn_six";
			this->btn_six->Size = System::Drawing::Size(34, 24);
			this->btn_six->TabIndex = 7;
			this->btn_six->Text = L"6";
			this->btn_six->UseVisualStyleBackColor = true;
			this->btn_six->Click += gcnew System::EventHandler(this, &calForm::btn_six_Click);
			// 
			// btn_seven
			// 
			this->btn_seven->FlatAppearance->BorderSize = 0;
			this->btn_seven->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_seven->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_seven->Location = System::Drawing::Point(14, 111);
			this->btn_seven->Name = L"btn_seven";
			this->btn_seven->Size = System::Drawing::Size(34, 24);
			this->btn_seven->TabIndex = 8;
			this->btn_seven->Text = L"7";
			this->btn_seven->UseVisualStyleBackColor = true;
			this->btn_seven->Click += gcnew System::EventHandler(this, &calForm::btn_seven_Click);
			// 
			// btn_eight
			// 
			this->btn_eight->FlatAppearance->BorderSize = 0;
			this->btn_eight->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_eight->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_eight->Location = System::Drawing::Point(54, 111);
			this->btn_eight->Name = L"btn_eight";
			this->btn_eight->Size = System::Drawing::Size(34, 24);
			this->btn_eight->TabIndex = 9;
			this->btn_eight->Text = L"8";
			this->btn_eight->UseVisualStyleBackColor = true;
			this->btn_eight->Click += gcnew System::EventHandler(this, &calForm::btn_eight_Click);
			// 
			// btn_nine
			// 
			this->btn_nine->FlatAppearance->BorderSize = 0;
			this->btn_nine->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_nine->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_nine->Location = System::Drawing::Point(94, 111);
			this->btn_nine->Name = L"btn_nine";
			this->btn_nine->Size = System::Drawing::Size(34, 24);
			this->btn_nine->TabIndex = 10;
			this->btn_nine->Text = L"9";
			this->btn_nine->UseVisualStyleBackColor = true;
			this->btn_nine->Click += gcnew System::EventHandler(this, &calForm::btn_nine_Click);
			// 
			// btn_zero
			// 
			this->btn_zero->FlatAppearance->BorderSize = 0;
			this->btn_zero->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_zero->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_zero->Location = System::Drawing::Point(54, 201);
			this->btn_zero->Name = L"btn_zero";
			this->btn_zero->Size = System::Drawing::Size(34, 24);
			this->btn_zero->TabIndex = 11;
			this->btn_zero->Text = L"0";
			this->btn_zero->UseVisualStyleBackColor = true;
			this->btn_zero->Click += gcnew System::EventHandler(this, &calForm::btn_zero_Click);
			// 
			// btn_add
			// 
			this->btn_add->DialogResult = System::Windows::Forms::DialogResult::Retry;
			this->btn_add->FlatAppearance->BorderSize = 0;
			this->btn_add->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_add->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_add->Location = System::Drawing::Point(134, 171);
			this->btn_add->Name = L"btn_add";
			this->btn_add->Size = System::Drawing::Size(34, 24);
			this->btn_add->TabIndex = 12;
			this->btn_add->Text = L"+";
			this->btn_add->UseVisualStyleBackColor = true;
			this->btn_add->Click += gcnew System::EventHandler(this, &calForm::btn_add_Click);
			// 
			// btn_sub
			// 
			this->btn_sub->FlatAppearance->BorderSize = 0;
			this->btn_sub->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_sub->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_sub->Location = System::Drawing::Point(134, 141);
			this->btn_sub->Name = L"btn_sub";
			this->btn_sub->Size = System::Drawing::Size(34, 24);
			this->btn_sub->TabIndex = 13;
			this->btn_sub->Text = L"-";
			this->btn_sub->UseVisualStyleBackColor = true;
			this->btn_sub->Click += gcnew System::EventHandler(this, &calForm::btn_sub_Click);
			// 
			// btn_multi
			// 
			this->btn_multi->FlatAppearance->BorderSize = 0;
			this->btn_multi->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_multi->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_multi->Location = System::Drawing::Point(134, 111);
			this->btn_multi->Name = L"btn_multi";
			this->btn_multi->Size = System::Drawing::Size(34, 24);
			this->btn_multi->TabIndex = 14;
			this->btn_multi->Text = L"×";
			this->btn_multi->UseVisualStyleBackColor = true;
			this->btn_multi->Click += gcnew System::EventHandler(this, &calForm::btn_multi_Click);
			// 
			// btn_div
			// 
			this->btn_div->FlatAppearance->BorderSize = 0;
			this->btn_div->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_div->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_div->Location = System::Drawing::Point(134, 84);
			this->btn_div->Name = L"btn_div";
			this->btn_div->Size = System::Drawing::Size(34, 24);
			this->btn_div->TabIndex = 15;
			this->btn_div->Text = L"÷";
			this->btn_div->UseVisualStyleBackColor = true;
			this->btn_div->Click += gcnew System::EventHandler(this, &calForm::btn_div_Click);
			// 
			// btn_dot
			// 
			this->btn_dot->FlatAppearance->BorderSize = 0;
			this->btn_dot->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_dot->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_dot->Location = System::Drawing::Point(94, 199);
			this->btn_dot->Name = L"btn_dot";
			this->btn_dot->Size = System::Drawing::Size(34, 24);
			this->btn_dot->TabIndex = 16;
			this->btn_dot->Text = L".";
			this->btn_dot->UseVisualStyleBackColor = true;
			this->btn_dot->Click += gcnew System::EventHandler(this, &calForm::btn_dot_Click);
			// 
			// btn_rightBracket
			// 
			this->btn_rightBracket->FlatAppearance->BorderSize = 0;
			this->btn_rightBracket->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_rightBracket->Font = (gcnew System::Drawing::Font(L"新宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_rightBracket->Location = System::Drawing::Point(54, 82);
			this->btn_rightBracket->Name = L"btn_rightBracket";
			this->btn_rightBracket->Size = System::Drawing::Size(34, 24);
			this->btn_rightBracket->TabIndex = 17;
			this->btn_rightBracket->Text = L")";
			this->btn_rightBracket->UseVisualStyleBackColor = true;
			this->btn_rightBracket->Click += gcnew System::EventHandler(this, &calForm::btn_rightBracket_Click);
			// 
			// tb_calculateWindow
			// 
			this->tb_calculateWindow->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tb_calculateWindow->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->tb_calculateWindow->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->tb_calculateWindow->Location = System::Drawing::Point(13, 12);
			this->tb_calculateWindow->Multiline = true;
			this->tb_calculateWindow->Name = L"tb_calculateWindow";
			this->tb_calculateWindow->ReadOnly = true;
			this->tb_calculateWindow->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->tb_calculateWindow->Size = System::Drawing::Size(147, 54);
			this->tb_calculateWindow->TabIndex = 18;
			this->tb_calculateWindow->TabStop = false;
			this->tb_calculateWindow->Text = L"                                                                                0"
				L"";
			this->tb_calculateWindow->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// btn_calculate
			// 
			this->btn_calculate->FlatAppearance->BorderSize = 0;
			this->btn_calculate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_calculate->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_calculate->Location = System::Drawing::Point(135, 201);
			this->btn_calculate->Name = L"btn_calculate";
			this->btn_calculate->Size = System::Drawing::Size(33, 20);
			this->btn_calculate->TabIndex = 19;
			this->btn_calculate->Text = L"=";
			this->btn_calculate->UseVisualStyleBackColor = true;
			this->btn_calculate->Click += gcnew System::EventHandler(this, &calForm::btn_calculate_Click);
			// 
			// btn_del
			// 
			this->btn_del->FlatAppearance->BorderSize = 0;
			this->btn_del->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_del->Location = System::Drawing::Point(94, 83);
			this->btn_del->Name = L"btn_del";
			this->btn_del->Size = System::Drawing::Size(34, 24);
			this->btn_del->TabIndex = 15;
			this->btn_del->Text = L"Del";
			this->btn_del->UseVisualStyleBackColor = true;
			this->btn_del->Click += gcnew System::EventHandler(this, &calForm::btn_del_Click);
			// 
			// btn_leftBracket
			// 
			this->btn_leftBracket->FlatAppearance->BorderSize = 0;
			this->btn_leftBracket->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_leftBracket->Font = (gcnew System::Drawing::Font(L"新宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_leftBracket->Location = System::Drawing::Point(14, 82);
			this->btn_leftBracket->Name = L"btn_leftBracket";
			this->btn_leftBracket->Size = System::Drawing::Size(34, 24);
			this->btn_leftBracket->TabIndex = 17;
			this->btn_leftBracket->Text = L"(";
			this->btn_leftBracket->UseVisualStyleBackColor = true;
			this->btn_leftBracket->Click += gcnew System::EventHandler(this, &calForm::btn_leftBracket_Click);
			// 
			// label_jayce
			// 
			this->label_jayce->AutoSize = true;
			this->label_jayce->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label_jayce->ForeColor = System::Drawing::Color::Red;
			this->label_jayce->Location = System::Drawing::Point(69, 241);
			this->label_jayce->Name = L"label_jayce";
			this->label_jayce->Size = System::Drawing::Size(39, 17);
			this->label_jayce->TabIndex = 26;
			this->label_jayce->Text = L"Jayce";
			this->label_jayce->Click += gcnew System::EventHandler(this, &calForm::label_jayce_Click);
			this->label_jayce->DoubleClick += gcnew System::EventHandler(this, &calForm::label_jayce_DoubleClick);
			// 
			// btn_negtive
			// 
			this->btn_negtive->FlatAppearance->BorderSize = 0;
			this->btn_negtive->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_negtive->Font = (gcnew System::Drawing::Font(L"宋体", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->btn_negtive->Location = System::Drawing::Point(14, 201);
			this->btn_negtive->Name = L"btn_negtive";
			this->btn_negtive->Size = System::Drawing::Size(34, 24);
			this->btn_negtive->TabIndex = 11;
			this->btn_negtive->Text = L"±";
			this->btn_negtive->UseVisualStyleBackColor = true;
			this->btn_negtive->Click += gcnew System::EventHandler(this, &calForm::btn_negtive_Click);
			// 
			// calForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(174, 268);
			this->Controls->Add(this->label_jayce);
			this->Controls->Add(this->btn_calculate);
			this->Controls->Add(this->btn_leftBracket);
			this->Controls->Add(this->btn_rightBracket);
			this->Controls->Add(this->btn_dot);
			this->Controls->Add(this->btn_del);
			this->Controls->Add(this->btn_div);
			this->Controls->Add(this->btn_multi);
			this->Controls->Add(this->btn_sub);
			this->Controls->Add(this->btn_add);
			this->Controls->Add(this->btn_negtive);
			this->Controls->Add(this->btn_zero);
			this->Controls->Add(this->btn_nine);
			this->Controls->Add(this->btn_eight);
			this->Controls->Add(this->btn_seven);
			this->Controls->Add(this->btn_six);
			this->Controls->Add(this->btn_five);
			this->Controls->Add(this->bnt_four);
			this->Controls->Add(this->btn_three);
			this->Controls->Add(this->btn_two);
			this->Controls->Add(this->btn_one);
			this->Controls->Add(this->tb_calculateWindow);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"calForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
			this->Text = L"计算器";
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		//Systen::String转换成std::string
		void MarshalString(String ^ s, string& os) {
			using namespace Runtime::InteropServices;
			const char* chars =
				(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

		void dealStatus()  //为了让每次开始计算时显得平滑
		{
			if (isWaiting)
			{
				if (this->tb_calculateWindow->Text->EndsWith(" 0")) //刚执行完计算后的/r/n不应该别清理掉
					this->tb_calculateWindow->Text = this->tb_calculateWindow->Text->Substring(0, this->tb_calculateWindow->TextLength - 1);
				else //刚计算玩
					this->tb_calculateWindow->Text += "\r\n";
				isWaiting = false;
			}
		}

#pragma endregion


	private: System::Void btn_calculate_Click(System::Object^  sender, System::EventArgs^  e) {
		if (!isWaiting)
		{
			System::String^ str = this->tb_calculateWindow->Text;
			if (str->Contains("=")) //存在历史计算
			{
				str = str->Substring(str->LastIndexOf("="));  //为支持历史纪录功能，采用截取上一计算以后内容的方法完成计算
				str = str->Substring(str->IndexOf("\r\n"));
			}
			str = str->Replace(" ", "");                         //去空格
			str = str->Replace("\r\n=", "");                      //去回车
			string cstr = "";
			MarshalString(str, cstr); //转换为c++的string
			cstr  = tkCalculator(cstr);
			str = gcnew String(cstr.c_str());
			this->tb_calculateWindow->Text += "\r\n= ";
			this->tb_calculateWindow->Text += str;
		//	this->tb_calculateWindow->Text += "\r\n";
			this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
			this->tb_calculateWindow->ScrollToCaret();
			//System::Windows::Forms::MessageBox::Show(str, L"提示信息");
			isWaiting = true;
		}
	}
	private: System::Void btn_add_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "+";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_del_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		System::String^ edit = this->tb_calculateWindow->Text;
		if (edit->Length > 0)
		{
			this->tb_calculateWindow->Text = edit->Substring(0, edit->Length - 1);
			this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
			this->tb_calculateWindow->ScrollToCaret();
		}
	}

	private: System::Void label_jayce_Click(System::Object^  sender, System::EventArgs^  e) {		
		this->tb_calculateWindow->Text = "";
		for (int i = 0; i < 10; i++)
			this->tb_calculateWindow->Text += "        ";
		this->tb_calculateWindow->Text += "0";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
		isWaiting = true;
	}
			 private: System::Void label_jayce_Click1(System::Object^  sender, System::EventArgs^  e) {
				 MessageBox::Show("Double Click!");
			 }
	private: System::Void btn_leftBracket_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "(";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_rightBracket_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += ")";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_div_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "/";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_multi_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "*";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_sub_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "-";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_dot_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += ".";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_negtive_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "(-";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_zero_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "0";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_one_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "1";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_two_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "2";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_three_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "3";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void bnt_four_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "4";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_five_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "5";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_six_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "6";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_seven_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "7";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_eight_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "8";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void btn_nine_Click(System::Object^  sender, System::EventArgs^  e) {
		dealStatus();
		this->tb_calculateWindow->Text += "9";
		this->tb_calculateWindow->SelectionStart = this->tb_calculateWindow->TextLength;
		this->tb_calculateWindow->ScrollToCaret();
	}
	private: System::Void label_jayce_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
		/*
		childForm^ z = gcnew childForm();
		z->Name = "childForm1";
		z->Text = "childForm1";
		z->Show();
		childForm^ z2 = gcnew childForm();
		z2->Name = "childForm2";
		z2->Text = "childForm2";
		z2->Show();

		keyTest^ kt1 = gcnew keyTest();
		kt1->Name = "kt1";
		kt1->Text = "kt1";
		kt1->Show();
		*/
		/*
		netClient^ c1 = gcnew netClient();
		netClient^ c2 = gcnew netClient();
		netClient^ c3 = gcnew netClient();
		netServer^ s1 = gcnew netServer();
		c1->Name = "c1";
		c2->Name = "c2";
		c3->Name = "c3";
		s1->Name = "s1";
		c1->Text = "c1";
		c2->Text = "c2";
		c3->Text = "c3";
		s1->Text = "s1";
		s1->StartPosition = FormStartPosition::CenterScreen;
		c1->Show();
		c3->Show();
		c2->Show();
		s1->Show();
		*/
		judge ^j1 = gcnew judge();
		j1->Name = "j1";
		j1->Text = "judge";
		j1->Show();
	
		//this->Hide();
	//	this->tb_calculateWindow->Text = "";
	}
};
}

