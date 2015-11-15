#pragma once
#include<io.h>
#include <vector>
#include <string>

vector<string> files;

void getFiles(string path, vector<string>& files)
{
	//文件句柄
	long   hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				if(fileinfo.name[0]!='~')
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

namespace Calculator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using wordDLL::wordCheck;
	/// <summary>
	/// judge 摘要
	/// </summary>
	public ref class judge : public System::Windows::Forms::Form
	{
	public:
		judge(void)
		{
			InitializeComponent();
			
			//
			//TODO:  在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~judge()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btn_brown1;
	private: System::Windows::Forms::Button^  btn_brown_directory;

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
		
	private: Thread^ extraThread;
	private: int docSum;
	private: System::Windows::Forms::Button^  btn_judge;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  btn_brown_file;

	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;




	private:


	protected:

	protected:

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
			this->btn_brown1 = (gcnew System::Windows::Forms::Button());
			this->btn_brown_directory = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->btn_judge = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btn_brown_file = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->SuspendLayout();
			// 
			// btn_brown1
			// 
			this->btn_brown1->Location = System::Drawing::Point(239, 12);
			this->btn_brown1->Name = L"btn_brown1";
			this->btn_brown1->Size = System::Drawing::Size(100, 23);
			this->btn_brown1->TabIndex = 0;
			this->btn_brown1->Text = L"指定答案文档..";
			this->btn_brown1->UseVisualStyleBackColor = true;
			this->btn_brown1->Click += gcnew System::EventHandler(this, &judge::btn_brown1_Click);
			// 
			// btn_brown_directory
			// 
			this->btn_brown_directory->Location = System::Drawing::Point(294, 41);
			this->btn_brown_directory->Name = L"btn_brown_directory";
			this->btn_brown_directory->Size = System::Drawing::Size(45, 23);
			this->btn_brown_directory->TabIndex = 0;
			this->btn_brown_directory->Text = L"目录";
			this->btn_brown_directory->UseVisualStyleBackColor = true;
			this->btn_brown_directory->Click += gcnew System::EventHandler(this, &judge::btn_brown_directory_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 14);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(218, 21);
			this->textBox1->TabIndex = 1;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(12, 43);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(218, 21);
			this->textBox2->TabIndex = 1;
			// 
			// btn_judge
			// 
			this->btn_judge->Location = System::Drawing::Point(239, 71);
			this->btn_judge->Name = L"btn_judge";
			this->btn_judge->Size = System::Drawing::Size(100, 23);
			this->btn_judge->TabIndex = 3;
			this->btn_judge->Text = L"判卷";
			this->btn_judge->UseVisualStyleBackColor = true;
			this->btn_judge->Click += gcnew System::EventHandler(this, &judge::btn_judge_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label1->ForeColor = System::Drawing::Color::Red;
			this->label1->Location = System::Drawing::Point(2, 76);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(227, 24);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Tips: 系统将自动识别文档类型\r\n      为目录时,将对目录下所以文档阅卷";
			// 
			// btn_brown_file
			// 
			this->btn_brown_file->Location = System::Drawing::Point(239, 41);
			this->btn_brown_file->Name = L"btn_brown_file";
			this->btn_brown_file->Size = System::Drawing::Size(45, 23);
			this->btn_brown_file->TabIndex = 0;
			this->btn_brown_file->Text = L"文件";
			this->btn_brown_file->UseVisualStyleBackColor = true;
			this->btn_brown_file->Click += gcnew System::EventHandler(this, &judge::btn_brown_file_Click);
			// 
			// judge
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(351, 107);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btn_judge);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->btn_brown_file);
			this->Controls->Add(this->btn_brown_directory);
			this->Controls->Add(this->btn_brown1);
			this->Name = L"judge";
			this->Text = L"judge";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		
		static void extraThreadFun(Object^ arg)
		{
			judge ^pthis = (judge^)arg;
			stringstream ss;
			string str;
			while(1)
			{
				ss << (pthis->docSum- wordCheck::wdDocCx);
				ss >> str;
				str += " remains.";
				ss.clear();
				pthis->btn_judge->Text = gcnew String(str.c_str());
				Sleep(500);//减轻cpu负担
			}
		
		}

	private: System::Void btn_judge_Click(System::Object^  sender, System::EventArgs^  e) {
		this->textBox1->Enabled = false;
		this->textBox2->Enabled = false;
		this->btn_judge->Text = "正在判卷";
		this->btn_judge->Enabled = false;
		String ^ansPath = this->textBox1->Text;
		String ^stuPath = this->textBox2->Text;
		//考虑到逐个传入文件名invoke效率太低,创建app时间开销大
		using namespace Runtime::InteropServices;
		char* cstr = (char*)(Marshal::StringToHGlobalAnsi(stuPath)).ToPointer();
		string str = cstr;
		getFiles(str, files);
		this->docSum = files.size();
		
		//为了提高体验，兼顾效率，增加线程动态显示已阅文档数
		extraThread = gcnew Thread(gcnew ParameterizedThreadStart(judge::extraThreadFun));//带参静态成员线程函数
		extraThread->Start(this);

		wordCheck ^wc = gcnew wordCheck();
		wc->getWordScore(ansPath, stuPath);
		/*
		stringstream ss;
		for (int i = 0; i < files.size(); i++)
		{
			wc->getWordScore(ansPath, gcnew String(files[i].c_str()));
			cx++;
			ss << (files.size()-cx);
			ss >> str;
			str += "remain.";
			ss.clear();
			this->btn_judge->Text = gcnew String(str.c_str());
		}
		*/
		this->btn_judge->Text = "判卷";
		this->btn_judge->Enabled = true;
		this->textBox1->Enabled = true;
		this->textBox2->Enabled = true;
		if (extraThread!=nullptr && extraThread->IsAlive)
			extraThread->Abort();
	}
private: System::Void btn_brown1_Click(System::Object^  sender, System::EventArgs^  e) {
	this->openFileDialog1->Title = "寻找答案文档";
	this->openFileDialog1->ShowDialog();
	this->textBox1->Text  = this->openFileDialog1->FileName;

}

private: System::Void btn_brown_file_Click(System::Object^  sender, System::EventArgs^  e) {
	this->openFileDialog1->Title = "寻找学生文档";
	this->openFileDialog1->ShowDialog();
	this->textBox2->Text = this->openFileDialog1->FileName;
}
private: System::Void btn_brown_directory_Click(System::Object^  sender, System::EventArgs^  e) {
	this->folderBrowserDialog1->Description = "寻找学生文档目录";
	this->folderBrowserDialog1->ShowDialog();
	this->textBox2->Text = this->folderBrowserDialog1->SelectedPath;
}
};
}
