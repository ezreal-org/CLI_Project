/*
*Copyright(c)2011:tian
*功能描述： 输入一行表达式 ,对表达式求值,支持括号,阶层,负号,小数点,幂方,变量等
*完成时间：13/10/2011 - 14/10/2011
*当前版本：1.0
*修改记录：
*/
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<sstream>
using namespace std;
#define MAX 100

struct Stacknum       //存储运算符
{
	float n[MAX];
	int top;
}Save_n;
struct Stackchar        //存储数字
{
	char n[MAX];
	int top;
}Save_c;

bool StackEmpty1(Stacknum s)   //判断栈是否为空
{
	if (s.top == -1) return 1;
	else return 0;
}
bool StackEmpty2(Stackchar s)    //判断栈是否为空
{
	if (s.top == -1) return 1;
	else return 0;
}

void Push1(Stacknum& s, float e)  //将e入栈
{
	if (s.top == MAX - 1) { cout << "栈已满" << endl; return; }
	s.top++;
	s.n[s.top] = e;
}
void Push2(Stackchar& s, char e)  //将e入栈
{
	if (s.top == MAX - 1) { cout << "栈已满" << endl; return; }
	s.top++;
	s.n[s.top] = e;
}

void Pop1(Stacknum& s, float& e)  //栈顶元素出栈，存到e中
{
	if (s.top == -1) { cout << "栈为空" << endl; }
	else { e = s.n[s.top]; s.top--; }
}
void Pop2(Stackchar& s, char& e)  //栈顶元素出栈，存到e中
{
	if (s.top == -1) { cout << "栈为空" << endl; }
	else { e = s.n[s.top]; s.top--; }
}


/*     operator 优先级
+— * /  (   )   ^
内   2   0   0   7   5
外   1   3   7   0   6  */

int In(char e)                 //e在栈内的优先级，数值大优先级高
{
	if (e == '+' || e == '-') return 2;
	if (e == '*' || e == '/') return 4;
	if (e == '^') return 5;
	if (e == '(') return 0;
	if (e == ')') return 7;
	return -1;
}
int Out(char e)                 //e在栈外的优先级，数值大优先级高
{
	if (e == '+' || e == '-') return 1;
	if (e == '*' || e == '/') return 3;
	if (e == '^') return 6;
	if (e == '(') return 7;
	if (e == ')') return 0;
	return -1;
}

void Count(float a, char ope, float b)  //进行计算，并把结果入栈
{
	float sum;
	if (ope == '+') sum = a + b;
	if (ope == '-') sum = a - b;
	if (ope == '*') sum = a*b;
	if (ope == '/') sum = a / b;
	if (ope == '^') sum = pow(a, b);
	Push1(Save_n, sum);
}

float Rank(float m)                         //求m阶层
{
	if (m == 0 || m == 1) return 1;
	else return m*Rank(m - 1);
}

bool validateSentence(string str) //检查表达式有效性，简单的检查临近是否都为操作符
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
		return "无效表达式";
	int i = 0, len, j;   // len为输入式长度
	float a, b;                   // a,b 接收栈抛出的操作数 或者 临时传阶层参数
	char line[MAX], operate, temp[20]; //temp[]临时存放操作符间一段数字数字
	int m[10], k = 0, clen = 0;              //m[]储存变量对应的值 ,k将在for循环中作计数变量
	char c[10];                        //clen表示变量个数,   c[]存储变量
									   //line = str.c_str()
	for (int tk = 0; tk < str.size(); tk++)
		line[tk] = str[tk];
	line[str.size()] = 0;
	len = strlen(line);
	Save_n.top = -1;              //将栈置空
	Save_c.top = -1;              //将栈置空
	while (true)
	{
		if (isdigit(line[i]))     //从串中读出一个完整的数字，包括 '.'
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
		else if (isalpha(line[i]))           //line[i]是变量的情形
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
			else                          //检测读的line[i]变量是否在c[]中存在
			{
				for (k = 0; k<clen; k++)
				{
					if (line[i] == c[k]) { Push1(Save_n, m[k]); break; }
				}
				if (k == clen)                    //不存在，将变量加入c[]，同时将
				{                              //对应m[]入Stacknum栈
					cout << "input " << line[i] << ":";
					cin >> m[clen];
					c[clen] = line[i];
					Push1(Save_n, m[clen]);
					clen++;
				}
				i++;
			}
		}
		else if (line[i] == '-' && (i == 0 || line[i - 1] == '('))  //运算符为负号
		{
			Push1(Save_n, 0);
			Push2(Save_c, line[i]);
			i++;
		}
		else if (line[i] == '!')                            //阶层处理
		{
			Pop1(Save_n, a);
			b = Rank(a);
			Push1(Save_n, b);
			i++;
		}
		//核心算法
		//读入数据与operator栈的栈顶元素比较，并进行相应操作
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