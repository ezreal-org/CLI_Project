#pragma once
#include"jayce.h"



namespace Calculator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// netClient 摘要
	/// </summary>
	public ref class netClient : public System::Windows::Forms::Form
	{
	public:
		netClient(void)
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
		~netClient()
		{
			if (recvThread != nullptr && recvThread->IsAlive)
				recvThread->Abort();
			if (components)
			{
				delete components;
			}
			closesocket(sockClient);
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button2;
	private: Thread^ recvThread;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: SOCKET sockClient;
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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(107, 117);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Send";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &netClient::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 12);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(170, 72);
			this->textBox1->TabIndex = 1;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 117);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Connect";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &netClient::button2_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(12, 90);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(170, 21);
			this->textBox2->TabIndex = 3;
			// 
			// netClient
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(193, 156);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"netClient";
			this->Text = L"netClient";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		//定义线程  
		//静态成员函数方法
		static void ReceiveThreadRun(Object^ arg)
		{
			printf("client-----recvThread created success....\n");
			netClient^ pthis = (netClient^)arg;
			char sendBuf[50];
			char recvBuf[50];
			char disp[50];
			string dispStr = "";
			while(1)
			{
				recv(pthis->sockClient, recvBuf, 50, 0);
				printf("%s client-----server msg : %s\n", pthis->Name,recvBuf+1);
				if (strcmp(recvBuf, "1KEEPALIVE") == 0)
				{	
					send(pthis->sockClient, "1I'm alive...", 50, 0);
				}
				if (strcmp(recvBuf, "0NAME") == 0)
				{ 
					sprintf(sendBuf, "0%s", pthis->Name);
					send(pthis->sockClient, sendBuf, 50, 0);
				}
				if (recvBuf[0] != '0' && recvBuf[0] != '1')
				{
					sprintf(disp, "server: %s...\r\n", recvBuf+1);
					dispStr = disp;
					pthis->textBox1->Text += gcnew String(dispStr.c_str());
					pthis->textBox1->SelectionStart = pthis->textBox1->Text->Length;
					pthis->textBox1->ScrollToCaret();
				}
			}		
			//closesocket(pthis->sockClient);
		}

#pragma endregion
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		this->button2->Enabled = false;
		//connect
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;
		wVersionRequested = MAKEWORD(1, 1);//第一个参数为低位字节；第二个参数为高位字节
		err = WSAStartup(wVersionRequested, &wsaData);//对winsock DLL（动态链接库文件）进行初始化，协商Winsock的版本支持，并分配必要的资源。
		if (err != 0)
		{
			return;
		}
		if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)//LOBYTE（）取得16进制数最低位；HIBYTE（）取得16进制数最高（最左边）那个字节的内容		
		{
			WSACleanup();
			return;
		}
		sockClient = socket(AF_INET, SOCK_STREAM, 0);
		SOCKADDR_IN addrSvr;//需要包含服务端IP信息	
		addrSvr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");// inet_addr将IP地址从点数格式转换成网络字节格式整型。
		addrSvr.sin_family = AF_INET;
		addrSvr.sin_port = htons(4001);
		printf("client-----ready to conn\n");
		connect(sockClient, (SOCKADDR*)&addrSvr,sizeof(SOCKADDR));//客户机向服务器发出

		//create receive Thread
		recvThread = gcnew Thread(gcnew ParameterizedThreadStart(netClient::ReceiveThreadRun));//带参静态成员线程函数
		recvThread->Start(this);
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		char sendBuf[50];
		sprintf(sendBuf, "2%s", this->textBox2->Text);
		send(sockClient, sendBuf, 50, 0);
		this->textBox1->Text += ("me: " + this->textBox2->Text + "\r\n");
		this->textBox2->Text = "";
		this->textBox1->SelectionStart = this->textBox1->Text->Length;
		this->textBox1->ScrollToCaret();
	}
};
}
