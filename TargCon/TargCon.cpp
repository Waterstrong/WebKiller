// TargCon.cpp : 定义控制台应用程序的入口点。
//
//************************************
// @FileName: TargCon.cpp
// @Brief   : 目标配置文件的修改
// @Author  : Waterstrong
// @DateTime: 2013-7-4 20:29:52
//************************************
#include "stdafx.h"

#define CONFIRG_ENTER(confirm, ch) cout<<"Please confirm: "<<flush; confirm = getch(); putchar('#'); putchar('\n'); if ( tolower(confirm) != ch){cout<<"--->Confirmation error!"<<endl; system("pause"); continue;}

string EncryptPwd()
{
	char ch;
	string pwd = "";
	while(true)
	{
		ch = getch();
		if (ch == 13)
		{
			putchar('\n');
			break;
		}
		if (ch == 27)
		{
			pwd = "";
			putchar('\n');
			break;
		}
		if (ch == '\b')
		{
			printf("%c %c", '\b', '\b');
			pwd.erase(pwd.length()-1);
			continue;
		}
		pwd += ch;
		putchar('*');
	}
	return pwd;
}
void EnterPwd()
{
	string pwd = "";
	cout<<"Please enter password："<<flush;
	pwd = EncryptPwd();
	while (pwd != PWD)
	{
		if (pwd != "")
		{
			cout<<"--->Password error!!!"<<endl;
		}
		cout<<"Please enter password: "<<flush;
		pwd = EncryptPwd();
	}
}

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
	while(true)
	{
		string str;
		char option;
		char confirm;
		cout<<"\n-----------File Configuration-----------\n"
			"0.Help    1.Remove    2.Free    3.Custom    4.Default    5.Query    6.Exit"<<endl;
		cout<<"\nPlease enter the option code: "<<flush;
		option = getch();
		putchar(option);
		putchar('\n');
		switch (option)
		{
		case '0':
			cout<<"1.Remove  Delete file, the program will load its default content.\n"
				"2.Free  Empty file content, you can shop online freely.\n"
				"3.Custom  Make your own content for termination.\n"
				"4.Default  Use the default content.\n"<<flush;
			system("pause");
			continue;
		case '1':
			CONFIRG_ENTER(confirm, 'r');
			if (DeleteFile( _T(TARGET_PATH) ))
			{
				cout<<"File remove done!"<<endl;
			}
			else
			{
				cout<<"--->Could not find file! Remove error!"<<endl;
			}
			system("pause");
			continue;
		case '2':
			CONFIRG_ENTER(confirm, 'f');
			str = ""; // 内容清空后就释放了，无目标了。
			break;
		case '3':
			CONFIRG_ENTER(confirm, 'c');
			cout<<"Please input the content: "<<flush;
			getline(cin, str); // 自定义内容
			break;
		case '4': // "淘宝" "天猫" "团购" "商城" "正品" "亚马逊";
			CONFIRG_ENTER(confirm, 'd');
			str = "淘宝 天猫 团购 商城 正品 亚马逊"; // 默认目标内容
			break;
		case '5':
			CONFIRG_ENTER(confirm, 'q');
			str = ReadFile() ;
			if (str == "")
			{
				cout<<"Free for shopping!"<<endl;
			}
			else
			{
				cout<<"Content<"+ str +">"<<endl;
			}
			system("pause");
			continue;
		case '6':
			CONFIRG_ENTER(confirm, 'e');
			cout<<"--->Already exit! Thanks for using!"<<endl;
			return; // 退出
		default:
			cout<<"--->No such option!"<<endl;
			system("pause");
			continue;
		}
		if (WriteFile(str))
		{
			cout<<"File configuration done! ---Content<"<<str<<">"<<endl;
		}
		else
		{
			cout<<"--->Write file error!"<<endl;
		}
		system("pause");
	}
}
void ShowTitle()
{
	cout<<"\n			Welcome to use TargCon !\n"
		"		======================================="<<endl;
}
int _tmain(int argc, _TCHAR* argv[])
{
	ShowTitle(); // 显示标题语
	EnterPwd(); // 输入密码
	MakeOption(); // 选项
	system("pause");
	return 0;
}

