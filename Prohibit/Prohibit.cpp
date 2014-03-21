// Prohibit.cpp : 定义控制台应用程序的入口点。
//
//************************************
// @FileName: Prohibit.cpp
// @Brief   : 限制网购默认
// @Author  : Waterstrong
// @DateTime: 2014-2-23 17:28:35
//************************************
#include "stdafx.h"

#define CONFIRG_ENTER(confirm, ch) cout<<"Please confirm: "<<flush; confirm = getch(); putchar('#'); putchar('\n'); if ( tolower(confirm) != ch){cout<<"--->Confirmation error!"<<endl; system("pause"); continue;}

bool WriteFile(string content)
{
	ofstream output;
	output.open(TARGET_PATH, ios::out);
	if (!output)
	{
		return false;
	}
	output<<content<<endl;
	output.close();
	return true;
}

string ReadFile()
{
	string str = "--No File! Load Default!--";
	ifstream input;
	input.open(TARGET_PATH, ios::in);
	if (!input)
	{
		return str;
	}
	getline(input, str);
	input.close();
	return str;
}

void MakeOption()
{
		string str = "淘宝 天猫 团购 商城 正品 亚马逊"; // 默认目标内容
		if (WriteFile(str))
		{
			cout<<"File configuration done!"<<endl;
		}
		else
		{
			cout<<"--->Write file error!"<<endl;
		}
}
void ShowTitle()
{
	cout<<"\n	    Welcome to use shopping killer!\n"
		"		======================================="<<endl;
}
int _tmain(int argc, _TCHAR* argv[])
{
	ShowTitle(); // 显示标题语
	//EnterPwd(); // 输入密码
	MakeOption(); // 选项
	system("pause");
	return 0;
}

