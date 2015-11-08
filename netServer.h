#pragma once
#include "jayce.h"

namespace Calculator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// netServer ժҪ
	/// </summary>

	public ref class netServer : public System::Windows::Forms::Form
	{
	public:
		ref class ClientEntry
		{
		public:
			String^ name;
			SOCKET  sock;
			Thread ^recvThread; //������Ϊÿ���ͻ���ά��һ�������߳�
			int flag;			//Ϊ�˺�����չ��flag����Ϊint��
			ClientEntry^ next;
		};

		netServer(void)
		{
			InitializeComponent();
			initServer();
			pClientEntryHead = nullptr;
			pClientEntryTail = nullptr;
			pthis = this;
			timeCx = 0;
			//
			//TODO:  �ڴ˴���ӹ��캯������
			//
		}

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~netServer()
		{
			if (components)
			{
				delete components;
			}
			if(acceptThread!=nullptr && acceptThread->IsAlive)
				acceptThread->Abort();
			printf("clear serverThread.... totel %d \n", clientCx);
			//all client thread clean

			for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
			{
				if (p->recvThread->IsAlive)
					p->recvThread->Abort();
			}
			if (keepAlive != nullptr && keepAlive->IsAlive)
				keepAlive->Abort();
			if (timeThread != nullptr && timeThread->IsAlive)
				timeThread->Abort();

			closesocket(sockSrv);
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: Thread^ acceptThread;
	private: Thread^ keepAlive;
	private: Thread^ timeThread;
	private: static SOCKET sockSrv;
	private: static int clientCx;
	private: int timeCx;
	private: static ClientEntry^ pClientEntryHead;
	private: static ClientEntry^ pClientEntryTail;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: static netServer^ pthis;
	private: System::Windows::Forms::Button^  btn_c1;
	private: System::Windows::Forms::Button^  btn_c3;
	private: System::Windows::Forms::Button^  btn_c2;
	private: System::Windows::Forms::Button^  btn_all;



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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->btn_c1 = (gcnew System::Windows::Forms::Button());
			this->btn_c3 = (gcnew System::Windows::Forms::Button());
			this->btn_c2 = (gcnew System::Windows::Forms::Button());
			this->btn_all = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 12);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(324, 197);
			this->textBox1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(154, 242);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"RUN";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &netServer::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(261, 242);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Send";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &netServer::button2_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(154, 215);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(182, 21);
			this->textBox2->TabIndex = 2;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &netServer::textBox2_TextChanged);
			// 
			// btn_c1
			// 
			this->btn_c1->FlatAppearance->BorderSize = 0;
			this->btn_c1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_c1->Location = System::Drawing::Point(12, 215);
			this->btn_c1->Name = L"btn_c1";
			this->btn_c1->Size = System::Drawing::Size(37, 23);
			this->btn_c1->TabIndex = 3;
			this->btn_c1->UseVisualStyleBackColor = true;
			this->btn_c1->Click += gcnew System::EventHandler(this, &netServer::btn_c1_Click);
			// 
			// btn_c3
			// 
			this->btn_c3->FlatAppearance->BorderSize = 0;
			this->btn_c3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_c3->Location = System::Drawing::Point(12, 244);
			this->btn_c3->Name = L"btn_c3";
			this->btn_c3->Size = System::Drawing::Size(37, 23);
			this->btn_c3->TabIndex = 3;
			this->btn_c3->UseVisualStyleBackColor = true;
			this->btn_c3->Click += gcnew System::EventHandler(this, &netServer::btn_c3_Click);
			// 
			// btn_c2
			// 
			this->btn_c2->FlatAppearance->BorderSize = 0;
			this->btn_c2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_c2->Location = System::Drawing::Point(69, 215);
			this->btn_c2->Name = L"btn_c2";
			this->btn_c2->Size = System::Drawing::Size(37, 23);
			this->btn_c2->TabIndex = 3;
			this->btn_c2->UseVisualStyleBackColor = true;
			this->btn_c2->Click += gcnew System::EventHandler(this, &netServer::btn_c2_Click);
			// 
			// btn_all
			// 
			this->btn_all->FlatAppearance->BorderSize = 0;
			this->btn_all->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_all->Location = System::Drawing::Point(69, 244);
			this->btn_all->Name = L"btn_all";
			this->btn_all->Size = System::Drawing::Size(37, 23);
			this->btn_all->TabIndex = 3;
			this->btn_all->UseVisualStyleBackColor = true;
			this->btn_all->Click += gcnew System::EventHandler(this, &netServer::btn_all_Click);
			// 
			// netServer
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(351, 274);
			this->Controls->Add(this->btn_all);
			this->Controls->Add(this->btn_c2);
			this->Controls->Add(this->btn_c3);
			this->Controls->Add(this->btn_c1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Name = L"netServer";
			this->Text = L"netServer";
			this->Load += gcnew System::EventHandler(this, &netServer::netServer_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		void initServer()
		{
			//��ʼ��winsocket
			WORD wVersionRequested;
			WSADATA wsaData;
			int err;
			wVersionRequested = MAKEWORD(1, 1);//��һ������Ϊ��λ�ֽڣ��ڶ�������Ϊ��λ��
			err = WSAStartup(wVersionRequested, &wsaData);//��winsock DLL����̬���ӿ��ļ������г�ʼ����Э��Winsock�İ汾֧�֣��������Ҫ����Դ��
			if (err != 0)
			{
				return;
			}
			if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)//LOBYTE����ȡ��16���������λ��HIBYTE����ȡ��16��������ߣ�����ߣ��Ǹ��ֽڵ�����		
			{
				WSACleanup();
				return;
			}
			sockSrv = socket(AF_INET, SOCK_STREAM, 0);//����socket��AF_INET��ʾ��Internet��ͨ�ţ�SOCK_STREAM��ʾsocket�����׽��֣���Ӧtcp��0ָ������Э��ΪTCP/IP
			SOCKADDR_IN addrSrv;
			addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");	//htonl�����������ֽ�˳��ת��Ϊ�����ֽ�˳��(to network long													//INADDR_ANY����ָ����ַΪ0.0.0.0�ĵ�ַ,												//��ʾ��ȷ����ַ,�������ַ������
			addrSrv.sin_family = AF_INET;
			addrSrv.sin_port = htons(4001);//htons�����������ֽ�˳��ת��Ϊ�����ֽ�˳��(to network short)
			bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//�����ص�ַ�󶨵���������socket�ϣ���ʹ�������ϱ�ʶ��socket
			printf("server----addr %s \n", inet_ntoa(addrSrv.sin_addr));
			listen(sockSrv, 5);//socket������׼��������������
		}

		static void clientEntryClean()
		{
			char disp[50];
			string dispStr;
			if(clientCx>0)
			{
				ClientEntry^ pre, ^p;
				pre = p = pClientEntryHead;
				while ( p != nullptr)
				{
					if (p->flag == 0) //��ǰ�����Ҫɾ��
					{
						if (p == pClientEntryHead)
						{
							printf("Server��------------ %s may DIE....\n", p->name);
							sprintf(disp,"%s may die...........\r\n",p->name);
							dispStr = disp;
							pthis->textBox1->Text += gcnew String(dispStr.c_str());
							pthis->textBox1->SelectionStart = pthis->textBox1->Text->Length;
							pthis->textBox1->ScrollToCaret();
							pClientEntryHead = p->next;
							pre = p;
							p = p->next;
							delete pre;
							pre = p;
							clientCx--;
						}
						else
						{
							printf("Server��------------ %s may DIE....\n", p->name);
							sprintf(disp, "%s may die...........\r\n", p->name);
							dispStr = disp;
							pthis->textBox1->Text += gcnew String(dispStr.c_str());
							pthis->textBox1->SelectionStart = pthis->textBox1->Text->Length;
							pthis->textBox1->ScrollToCaret();
							pre->next = p->next;
							delete p;
							p = pre->next;
							clientCx--;
						}
					
					}
					else //����ɾ����ǰ���
					{
						pre = p;
						p = p->next;
					}
				}
				pClientEntryTail = pre; //������β�ڵ�
				printf("Server : After clean...there are %d remain....\n", clientCx);
			}
		}
	
		static void IsAlive(Object^ arg)
		{
			char recvBuf[50];
			while (1)
			{
				//Ϊÿ���ͻ�����һ�������߳�
				if (clientCx > 0)
				{
					EnterCriticalSection(&g_CriticalSection);
				//	for (int i = 1; i < clientCx + 1; i++)
					//	stateOfAllClient[i] = 0; //�ȼٶ�������
					for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
					{
						p->flag = 0;
					}
					for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
					{
						send(p->sock, "1KEEPALIVE", 50, 0);
					}
					printf("send keepAlive package to all %d client.....\n", clientCx);
					LeaveCriticalSection(&g_CriticalSection);

				}
				Sleep(2000);//2000����

				//����������ȥ��client
				EnterCriticalSection(&g_CriticalSection);
				clientEntryClean();
				LeaveCriticalSection(&g_CriticalSection);
			}
		}

		static void TimeThread(Object^ arg)
		{
			while(1)
			{
			if (pthis->timeCx < 1)
			{
				pthis->timeCx = 0;
				pthis->Text = "netServer";
			}
			pthis->timeCx--;
			Sleep(1000);
			}
		}
		//Ϊÿ���ͻ�����һ�������߳�
		static void RecvThread(Object^ arg) //��������̹߳������������Ψһ�������ÿ���߳��ڲ�ͬ��sock�ϵȴ���Ϣ
		{
			char recvBuf[50];
			string recvStr = "";
			ClientEntry ^me= (ClientEntry ^)arg;
			SOCKET clientSock = me->sock;
			char name[20];
			sprintf(name, "%s", me->name);
			printf("server create RecvThread for %s ..", name);
			while(1)
			{
				int i;
				if (recv(clientSock, recvBuf, 50, 0) < 0)  //sock�������ݿɶ�
				{
					return;
				}
			for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
			{
				if (p->sock == clientSock)
				{
					p->flag = 1;
					break;
				}
			}
			printf("recv   %s from client %s : \n", recvBuf+1,name);  //��һλ��Ϊ��ʶλ�����ֲ�ͬ����Ϣ
			if (recvBuf[0] != '0' && recvBuf[0] != '1') //����ʾ�ǿ�����Ϣ, 0 NAME����1��ʾ������
			{
				char disp[50];
				sprintf(disp, "%s: %s ...\r\n", name, recvBuf + 1);
				recvStr = disp;
				pthis->textBox1->Text += gcnew String(recvStr.c_str());
				pthis->textBox1->SelectionStart = pthis->textBox1->Text->Length;
				pthis->textBox1->ScrollToCaret();
			}
			Sleep(200);//2000����
			}
		}
		//�����߳�  
		//��̬��Ա��������
		static void AcceptThread(Object^ arg)
		{	
			string str = "";
				SOCKADDR_IN addrClient;
				int len = sizeof(SOCKADDR);
				printf("server-------acceptThread run.... \n");
				while (1)
				{
					SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);//Ϊһ�����������ṩ����addrClient�����˷�����������Ŀͻ���IP��ַ��Ϣ�����ص���socket������������ÿͻ���������
					//������Ϊÿ���ͻ��˴���һ���̣߳������������ǵ���Ϣ
					send(sockConn, "0NAME", 50, 0);
					printf("server-------User(%d) from %s Connected!",clientCx+1,inet_ntoa(addrClient.sin_addr));
					 //Э�̵õ�client name
					char recvBuf[50];
					recv(sockConn, recvBuf, 50, 0);
					string recv = recvBuf+1; //��һλ��Ϊ��ʶλ�����ֲ�ͬ����Ϣ

					EnterCriticalSection(&g_CriticalSection);  //��Ա�����߳�ͬ������
					//add client entry
					clientCx++;
					Thread^ recvThread = gcnew Thread(gcnew ParameterizedThreadStart(netServer::RecvThread));//���ξ�̬��Ա�̺߳���
					ClientEntry ^ce = gcnew ClientEntry();
					ce->name = gcnew String(recv.c_str());
					ce->flag = 1;
					ce->recvThread = recvThread;
					ce->sock = sockConn;
					ce->next = nullptr;
					if (pClientEntryHead == nullptr)
					{
						pClientEntryHead = ce;
						pClientEntryTail = ce;
					}
					else
					{
						pClientEntryTail->next = ce;
						pClientEntryTail = ce;
					}
					recvThread->Start(ce);
					char temp[50];
					sprintf(temp, "%s", ce->name);
					if (strcmp(temp, "c1")==0)
					{
						pthis->btn_c1->Visible = true;
						pthis->btn_c1->Text = ce->name;
						pthis->btn_c1->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
						pthis->btn_all->Text = "all";
						pthis->btn_all->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
					}
					else if (strcmp(temp, "c2")==0)
					{
						pthis->btn_c2->Text = ce->name;
						pthis->btn_c2->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
						pthis->btn_all->Text = "all";
						pthis->btn_all->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
					}
					else if (strcmp(temp, "c3")==0)
					{
						pthis->btn_c3->Text = ce->name;
						pthis->btn_c3->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
						pthis->btn_all->Text = "all";
						pthis->btn_all->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
					}
					sprintf(temp, "User(%s),connected....\r\n", ce->name);
					str = temp;
					pthis->textBox1->Text += gcnew String(str.c_str());
					pthis->textBox1->SelectionStart = pthis->textBox1->Text->Length;
					pthis->textBox1->ScrollToCaret();
					LeaveCriticalSection(&g_CriticalSection);

					Sleep(200);//2000����
				}
		}
		

#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		this->button1->Enabled = false;
		clientCx = 0;
		acceptThread = gcnew Thread(gcnew ParameterizedThreadStart(netServer::AcceptThread));//���ξ�̬��Ա�̺߳���
		acceptThread->Start(0);
		keepAlive = gcnew Thread(gcnew ParameterizedThreadStart(netServer::IsAlive));//���ξ�̬��Ա�̺߳���
		keepAlive->Start(this);	
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			
		char peerName[20];
		char eachName[20];
		string dispStr = "";
		if (!(this->textBox2->Text->Contains("@")))
		{
			sprintf(eachName, "2%s", this->textBox2->Text);
			dispStr = "Server to all: ";
			dispStr += eachName + 1;
			dispStr += "\r\n";
			this->textBox1->Text += gcnew String(dispStr.c_str());
			this->textBox1->SelectionStart = this->textBox1->Text->Length;
			this->textBox1->ScrollToCaret();
			for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
			{
				send(p->sock, eachName, 50, 0);
			}
		}
		else
		{
			sprintf(peerName, "%s", this->textBox2->Text->Substring(1, 2));
			for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
			{
				sprintf(eachName, "%s", p->name);
				if (strcmp(eachName, peerName) == 0)
				{
					sprintf(eachName, "2%s", this->textBox2->Text->Substring(4));
					send(p->sock, eachName, 50, 0);
					sprintf(eachName, "Server to %s:  %s...\r\n", p->name, this->textBox2->Text->Substring(4));
					dispStr = eachName;
					this->textBox1->Text += gcnew String(dispStr.c_str());
					this->textBox1->SelectionStart = this->textBox1->Text->Length;
					this->textBox1->ScrollToCaret();
					return;
				}

			}
		}
		
		
		this->textBox2->Text = ""; 
	}
private: System::Void btn_c1_Click(System::Object^  sender, System::EventArgs^  e) {
	this->btn_c1->Enabled = false;
	this->btn_c2->Enabled = true;
	this->btn_c3->Enabled = true;
	this->btn_all->Enabled = true;
	this->textBox2->Text = "@c1 ";

}
private: System::Void btn_c2_Click(System::Object^  sender, System::EventArgs^  e) {
	this->btn_c2->Enabled = false;
	this->btn_c1->Enabled = true;
	this->btn_c3->Enabled = true;
	this->btn_all->Enabled = true;
	this->textBox2->Text = "@c2 ";
}
private: System::Void btn_c3_Click(System::Object^  sender, System::EventArgs^  e) {
	this->btn_c3->Enabled = false;
	this->btn_c1->Enabled = true;
	this->btn_c2->Enabled = true;
	this->btn_all->Enabled = true;
	this->textBox2->Text = "@c3 ";
}
private: System::Void btn_all_Click(System::Object^  sender, System::EventArgs^  e) {
	this->btn_all->Enabled = false;
	this->btn_c1->Enabled = true;
	this->btn_c2->Enabled = true;
	this->btn_c3->Enabled = true;
	this->textBox2->Text = "";
}
private: System::Void netServer_Load(System::Object^  sender, System::EventArgs^  e) {
	this->btn_c1->Visible = false;
	timeThread = gcnew Thread(gcnew ParameterizedThreadStart(netServer::TimeThread));//���ξ�̬��Ա�̺߳���
	timeThread->Start(0);
}
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	timeCx = 1; //1��û��������ʾû������
	this->Text = "��������...";
}
};

	

}

