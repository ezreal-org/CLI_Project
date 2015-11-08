/*
*Copyright(c)2011:tian
*���������� ����һ�б��ʽ ,�Ա��ʽ��ֵ,֧������,�ײ�,����,С����,�ݷ�,������
*���ʱ�䣺13/10/2011 - 14/10/2011
*��ǰ�汾��1.0
*�޸ļ�¼��
*/
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<sstream>
using namespace std;
#define MAX 100

struct Stacknum       //�洢�����
{
	float n[MAX];
	int top;
}Save_n;
struct Stackchar        //�洢����
{
	char n[MAX];
	int top;
}Save_c;

bool StackEmpty1(Stacknum s)   //�ж�ջ�Ƿ�Ϊ��
{
	if (s.top == -1) return 1;
	else return 0;
}
bool StackEmpty2(Stackchar s)    //�ж�ջ�Ƿ�Ϊ��
{
	if (s.top == -1) return 1;
	else return 0;
}

void Push1(Stacknum& s, float e)  //��e��ջ
{
	if (s.top == MAX - 1) { cout << "ջ����" << endl; return; }
	s.top++;
	s.n[s.top] = e;
}
void Push2(Stackchar& s, char e)  //��e��ջ
{
	if (s.top == MAX - 1) { cout << "ջ����" << endl; return; }
	s.top++;
	s.n[s.top] = e;
}

void Pop1(Stacknum& s, float& e)  //ջ��Ԫ�س�ջ���浽e��
{
	if (s.top == -1) { cout << "ջΪ��" << endl; }
	else { e = s.n[s.top]; s.top--; }
}
void Pop2(Stackchar& s, char& e)  //ջ��Ԫ�س�ջ���浽e��
{
	if (s.top == -1) { cout << "ջΪ��" << endl; }
	else { e = s.n[s.top]; s.top--; }
}


/*     operator ���ȼ�
+�� * /  (   )   ^
��   2   0   0   7   5
��   1   3   7   0   6  */

int In(char e)                 //e��ջ�ڵ����ȼ�����ֵ�����ȼ���
{
	if (e == '+' || e == '-') return 2;
	if (e == '*' || e == '/') return 4;
	if (e == '^') return 5;
	if (e == '(') return 0;
	if (e == ')') return 7;
	return -1;
}
int Out(char e)                 //e��ջ������ȼ�����ֵ�����ȼ���
{
	if (e == '+' || e == '-') return 1;
	if (e == '*' || e == '/') return 3;
	if (e == '^') return 6;
	if (e == '(') return 7;
	if (e == ')') return 0;
	return -1;
}

void Count(float a, char ope, float b)  //���м��㣬���ѽ����ջ
{
	float sum;
	if (ope == '+') sum = a + b;
	if (ope == '-') sum = a - b;
	if (ope == '*') sum = a*b;
	if (ope == '/') sum = a / b;
	if (ope == '^') sum = pow(a, b);
	Push1(Save_n, sum);
}

float Rank(float m)                         //��m�ײ�
{
	if (m == 0 || m == 1) return 1;
	else return m*Rank(m - 1);
}

bool validateSentence(string str) //�����ʽ��Ч�ԣ��򵥵ļ���ٽ��Ƿ�Ϊ������
{
	for (int i = 0; i < str.size(); i++)
	{
		if ((str[i] == '.' || str[i]=='+'||str[i]=='-' || str[i] == '*' || str[i] == '/')&& (str[i+1] == '.' || str[i+1] == '+' || str[i+1] == '-' || str[i+1] == '*' || str[i+1] == '/'))
		{
			return false;
		}
	}
	return true;
}

string tkCalculator(string str)
{
	if (!validateSentence(str))
		return "��Ч���ʽ";
	int i = 0, len, j;   // lenΪ����ʽ����
	float a, b;                   // a,b ����ջ�׳��Ĳ����� ���� ��ʱ���ײ����
	char line[MAX], operate, temp[20]; //temp[]��ʱ��Ų�������һ����������
	int m[10], k = 0, clen = 0;              //m[]���������Ӧ��ֵ ,k����forѭ��������������
	char c[10];                        //clen��ʾ��������,   c[]�洢����
									   //line = str.c_str()
	for (int tk = 0; tk < str.size(); tk++)
		line[tk] = str[tk];
	line[str.size()] = 0;
	len = strlen(line);
	Save_n.top = -1;              //��ջ�ÿ�
	Save_c.top = -1;              //��ջ�ÿ�
	while (true)
	{
		if (isdigit(line[i]))     //�Ӵ��ж���һ�����������֣����� '.'
		{
			j = 0;
			while (isdigit(line[i]) || line[i] == '.')
			{
				temp[j++] = line[i];
				i++;
				if (i >= len) break;
			}
			temp[j] = '\0';
			b = atof(temp);
			Push1(Save_n, b);
			if (i >= len) break;
		}
		else if (isalpha(line[i]))           //line[i]�Ǳ���������
		{
			if (clen == 0)
			{
				c[0] = line[i];
				cout << "input " << line[i] << ":";
				cin >> m[0];
				Push1(Save_n, m[0]);
				clen++;
				i++;
			}
			else                          //������line[i]�����Ƿ���c[]�д���
			{
				for (k = 0; k<clen; k++)
				{
					if (line[i] == c[k]) { Push1(Save_n, m[k]); break; }
				}
				if (k == clen)                    //�����ڣ�����������c[]��ͬʱ��
				{                              //��Ӧm[]��Stacknumջ
					cout << "input " << line[i] << ":";
					cin >> m[clen];
					c[clen] = line[i];
					Push1(Save_n, m[clen]);
					clen++;
				}
				i++;
			}
		}
		else if (line[i] == '-' && (i == 0 || line[i - 1] == '('))  //�����Ϊ����
		{
			Push1(Save_n, 0);
			Push2(Save_c, line[i]);
			i++;
		}
		else if (line[i] == '!')                            //�ײ㴦��
		{
			Pop1(Save_n, a);
			b = Rank(a);
			Push1(Save_n, b);
			i++;
		}
		//�����㷨
		//����������operatorջ��ջ��Ԫ�رȽϣ���������Ӧ����
		else if (In(Save_c.n[Save_c.top]) < Out(line[i]) || StackEmpty2(Save_c))
		{
			Push2(Save_c, line[i]); i++;
		}
		else if (In(Save_c.n[Save_c.top]) == Out(line[i])) { Save_c.top--; i++; }
		else //if (In(Save_c.n[Save_c.top]) > Out(line[i]))
		{
			Pop1(Save_n, a);
			Pop1(Save_n, b);
			Pop2(Save_c, operate);
			Count(b, operate, a);
		}
		if (i >= len) break;
	}
	while (Save_c.top != -1)
	{
		Pop1(Save_n, a);
		Pop1(Save_n, b);
		Pop2(Save_c, operate);
		Count(b, operate, a);
	}
	stringstream ans;
	ans << Save_n.n[Save_n.top];
	return  ans.str();
}