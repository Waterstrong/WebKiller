// Prohibit.cpp : �������̨Ӧ�ó������ڵ㡣
//
//************************************
// @FileName: Prohibit.cpp
// @Brief   : ��������Ĭ��
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
		string str = "�Ա� ��è �Ź� �̳� ��Ʒ ����ѷ"; // Ĭ��Ŀ������
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
	ShowTitle(); // ��ʾ������
	//EnterPwd(); // ��������
	MakeOption(); // ѡ��
	system("pause");
	return 0;
}

