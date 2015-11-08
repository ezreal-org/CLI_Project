#pragma once
#include "jayce.h"
#include <sstream>
#include<string>
#include<Windows.h>
using namespace std;

static int g_cx = 10000; //测试线程之间的同步
extern CRITICAL_SECTION g_CriticalSection;

namespace Calculator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	
	
	/// <summary>
	/// childForm 摘要
	/// </summary>
	 class ChildExtraThread;

	public ref class childForm : public System::Windows::Forms::Form
	{
	public:
		childForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//	
			direct = true;
			extraThread = gcnew Thread(gcnew ParameterizedThreadStart(childForm::DoWork1));//带参静态成员线程函数
			extraThread->Start(this);
			cx = 10000;
		}
		 

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~childForm()
		{
			if (components)
			{
				delete components;
				
			}
			if(extraThread->IsAlive)
				extraThread->Abort();

		
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: Thread^ extraThread ;
	private:  System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button3;
	private: bool direct; //direct==true ++1
	private: int cx;
	protected:

		//定义线程  
		//静态成员函数方法
		static void DoWork1(Object^ arg)
		{
			childForm^ pthis = (childForm^) arg;
			stringstream ss;
			string str="";
			while (1)
			{
				EnterCriticalSection(&g_CriticalSection);  //成员属性线程同步测试
				ss.clear();
				if (pthis->direct)
					pthis->cx += 1;
				else
					pthis->cx -= 1;
				ss << pthis->cx;
				ss >> str;
				LeaveCriticalSection(&g_CriticalSection);
				pthis->label1->Text += gcnew String(str.c_str())+"\r\n";
				
				Thread::Sleep(100);
			}
		

		}
		static void DoWork2(Object^ arg)
		{
			
			childForm^ pthis = (childForm^)arg;
			stringstream ss;
			string str = "";
	
			while (1)
			{
				EnterCriticalSection(&g_CriticalSection); //全局共享变量线程同步测试
				ss.clear();
				g_cx--;
				ss << g_cx;
				ss >> str;
				Application::OpenForms["calForm"]->Controls["tb_calculateWindow"]->Text += pthis->Name+": "+gcnew String(str.c_str())+"\r\n";
				LeaveCriticalSection(&g_CriticalSection);
				Thread::Sleep(100);	
			}
		}
	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(78, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Trick  Father";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &childForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(78, 56);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(100, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Close Father";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &childForm::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(155, 103);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 12);
			this->label1->TabIndex = 2;
			this->label1->Text = L"label1";
			this->label1->Click += gcnew System::EventHandler(this, &childForm::label1_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(265, 12);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 3;
			this->button3->Text = L"direct";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &childForm::button3_Click);
			// 
			// childForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(448, 515);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"childForm";
			this->Text = L"childForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	
		


#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		 Application::OpenForms["calForm"]->Visible -= 1 ;
		// extern int abc;
		 //abc = 1;
		 if (Application::OpenForms["calForm"]->Visible)
		 {
			 if (Application::OpenForms["calForm"]->Controls["label_jayce"]->Text == "hello father")
				 Application::OpenForms["calForm"]->Controls["label_jayce"]->Text = "father hello";
			 else
				 Application::OpenForms["calForm"]->Controls["label_jayce"]->Text = "hello father";
		 }
		 if (Application::OpenForms["childForm1"]->Controls["button3"]->Text == "XIXI")
		 { 
			 Application::OpenForms["childForm1"]->Controls["button3"]->Text = "HAHA";
			 Application::OpenForms["childForm2"]->Controls["button3"]->Text = "HAHA";
		 }	
		 else
		 {
			 Application::OpenForms["childForm1"]->Controls["button3"]->Text = "XIXI";
			 Application::OpenForms["childForm2"]->Controls["button3"]->Text = "XIXI";
		 }
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		Application::OpenForms["calForm"]->Close();
	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	direct -= 1;
}
};

}


