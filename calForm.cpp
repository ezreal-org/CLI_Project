#include "calForm.h"
using namespace Calculator; //�Լ��������ռ�

CRITICAL_SECTION g_CriticalSection; // ����

[STAThread]
int main()
{
	InitializeCriticalSection(&g_CriticalSection);      // ��ʼ��  
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	calForm^ g_cF = gcnew calForm();
	Application::Run(g_cF);
	DeleteCriticalSection(&g_CriticalSection);
	return 0;
}
