#pragma once
#include<io.h>
#include <vector>
#include <string>

vector<string> files;

void getFiles(string path, vector<string>& files)
{
	//�ļ����
	long   hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮
			//�������,�����б�
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
	using excelDLL::ExcelCheck;
	using pptDLL::PptCheck;
	using AccessSimpleDLL::AccessCheckSimple;
	/// <summary>
	/// judge ժҪ
	/// </summary>
	public ref class judge : public System::Windows::Forms::Form
	{
	public:
		judge(void)
		{
			InitializeComponent();
			
			//
			//TODO:  �ڴ˴���ӹ��캯������
			//
		}

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~judge()
		{
			if (components)
			{
				delete components;
			}
			if (judgeThread != nullptr && judgeThread->IsAlive)
				judgeThread->Abort();
			if (extraThread != nullptr &&extraThread->IsAlive)
				extraThread->Abort();
		}
	private: System::Windows::Forms::Button^  btn_brown1;
	private: System::Windows::Forms::Button^  btn_brown_directory;

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
		
	private: Thread^ extraThread;
	private: Thread^ judgeThread;
	private: int docSum;
	private: int typeOfjudge;
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
		/// ����������������
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ�޸�
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
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
			this->btn_brown1->Text = L"ָ�����ĵ�..";
			this->btn_brown1->UseVisualStyleBackColor = true;
			this->btn_brown1->Click += gcnew System::EventHandler(this, &judge::btn_brown1_Click);
			// 
			// btn_brown_directory
			// 
			this->btn_brown_directory->Location = System::Drawing::Point(294, 41);
			this->btn_brown_directory->Name = L"btn_brown_directory";
			this->btn_brown_directory->Size = System::Drawing::Size(45, 23);
			this->btn_brown_directory->TabIndex = 0;
			this->btn_brown_directory->Text = L"Ŀ¼";
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
			this->btn_judge->Text = L"�о�";
			this->btn_judge->UseVisualStyleBackColor = true;
			this->btn_judge->Click += gcnew System::EventHandler(this, &judge::btn_judge_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"����", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label1->ForeColor = System::Drawing::Color::Red;
			this->label1->Location = System::Drawing::Point(2, 76);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(227, 24);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Tips: ϵͳ���Զ�ʶ���ĵ�����\r\n      ΪĿ¼ʱ,����Ŀ¼�������ĵ��ľ�";
			// 
			// btn_brown_file
			// 
			this->btn_brown_file->Location = System::Drawing::Point(239, 41);
			this->btn_brown_file->Name = L"btn_brown_file";
			this->btn_brown_file->Size = System::Drawing::Size(45, 23);
			this->btn_brown_file->TabIndex = 0;
			this->btn_brown_file->Text = L"�ļ�";
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
			//���ǵ���������ļ���invokeЧ��̫��,����appʱ�俪����
			using namespace Runtime::InteropServices;
			char* cstr = (char*)(Marshal::StringToHGlobalAnsi(pthis->textBox2->Text)).ToPointer();
			string strtemp = cstr;
			files.clear();
			getFiles(strtemp, files);
			pthis->docSum = files.size();
			Sleep(2000);
			while(1)
			{
				if (pthis->typeOfjudge == 1) //��ǰ���word�ĵ�
				{
					ss << (pthis->docSum - wordCheck::wdDocCx);
				}
				if (pthis->typeOfjudge == 2) //��ǰ���excel�ĵ�
				{
					ss << (pthis->docSum - ExcelCheck::excelDocCx);
				}
				if (pthis->typeOfjudge == 3) //��ǰ���ppt�ĵ�
				{
					ss << (pthis->docSum - PptCheck::pptDocCx);
				}
				if (pthis->typeOfjudge == 4) //��ǰ���access�ĵ�
				{
					ss << (pthis->docSum - AccessCheckSimple::accessDocCx);
				}
				ss >> str;
				str += " remains.";
				ss.clear();
				pthis->btn_judge->Text = gcnew String(str.c_str());
				Sleep(500);//����cpu����
			}
		
		}
		static void judgeThreadFun(Object^ arg)
		{
			judge ^pthis = (judge^)arg;
			pthis->textBox1->Enabled = false;
			pthis->textBox2->Enabled = false;
			pthis->btn_judge->Text = "�����о�";
			pthis->btn_judge->Enabled = false;
			String ^ansPath = pthis->textBox1->Text;
			String ^stuPath = pthis->textBox2->Text;

			//ʶ��ͬ�ĵ����ò�ͬDLL�ӿ�
			if (ansPath->EndsWith(".docx"))
			{
				pthis->typeOfjudge = 1;
				pthis->Text = "judge word";
				wordCheck::wdDocCx = 0;
				wordCheck ^wc = gcnew wordCheck();
				wc->getWordScore(ansPath, stuPath);
			}
			if (ansPath->EndsWith(".xlsx"))
			{
				pthis->typeOfjudge = 2;
				pthis->Text = "judge excel";
				ExcelCheck::excelDocCx = 0;
				ExcelCheck ^ec = gcnew ExcelCheck();
				ec->getExcelScore(ansPath, stuPath);
			}
			if (ansPath->EndsWith(".pptx"))
			{
				pthis->typeOfjudge = 3;
				pthis->Text = "judge ppt";
				PptCheck::pptDocCx = 0;
				PptCheck ^pc = gcnew PptCheck();
				pc->getPPTScore(ansPath, stuPath);
			}
			if (ansPath->EndsWith(".accdb"))
			{
				pthis->typeOfjudge = 4;
				pthis->Text = "judge access";
				AccessCheckSimple::accessDocCx = 0;
				AccessCheckSimple ^ac = gcnew AccessCheckSimple();
				ac->getAccessScore(ansPath, stuPath);
			}
			if (pthis->extraThread != nullptr && pthis->extraThread->IsAlive)
				pthis->extraThread->Abort();

			pthis->Text = "judge";
			pthis->btn_judge->Text = "�о�";
			pthis->btn_judge->Enabled = true;
			pthis->textBox1->Enabled = true;
			pthis->textBox2->Enabled = true;

			if (pthis->judgeThread != nullptr && pthis->judgeThread->IsAlive)
				pthis->judgeThread->Abort();
		}

	private: System::Void btn_judge_Click(System::Object^  sender, System::EventArgs^  e) {
		//�ö����߳�ȥ�����о���ֹ���н��潩��
		judgeThread = gcnew Thread(gcnew ParameterizedThreadStart(judge::judgeThreadFun));//���ξ�̬��Ա�̺߳���
		judgeThread->Start(this);
		
		//Ϊ��������飬���Ч�ʣ������̶߳�̬��ʾ�����ĵ���
		extraThread = gcnew Thread(gcnew ParameterizedThreadStart(judge::extraThreadFun));//���ξ�̬��Ա�̺߳���
		extraThread->Start(this);
		
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
		
	}
private: System::Void btn_brown1_Click(System::Object^  sender, System::EventArgs^  e) {
	this->openFileDialog1->Title = "Ѱ�Ҵ��ĵ�";
	this->openFileDialog1->ShowDialog();
	this->textBox1->Text  = this->openFileDialog1->FileName;

}

private: System::Void btn_brown_file_Click(System::Object^  sender, System::EventArgs^  e) {
	this->openFileDialog1->Title = "Ѱ��ѧ���ĵ�";
	this->openFileDialog1->ShowDialog();
	this->textBox2->Text = this->openFileDialog1->FileName;
}
private: System::Void btn_brown_directory_Click(System::Object^  sender, System::EventArgs^  e) {
	this->folderBrowserDialog1->Description = "Ѱ��ѧ���ĵ�Ŀ¼";
	this->folderBrowserDialog1->ShowDialog();
	this->textBox2->Text = this->folderBrowserDialog1->SelectedPath;
}
};
}
