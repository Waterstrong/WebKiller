// TargCon.cpp : �������̨Ӧ�ó������ڵ㡣
//
//************************************
// @FileName: TargCon.cpp
// @Brief   : Ŀ�������ļ����޸�
// @Author  : Waterstrong
// @DateTime: 2013-7-4 20:29:52
//************************************
#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// "�Ա�" "��è" "�Ź�" "�̳�" "��Ʒ" "����ѷ";
	string pwd = "";
	cout<<"Please enter pwd:"<<flush;
	cin>>pwd;
	if (pwd != PWD)
	{
		cout<<"pwd error!"<<endl;
		return 0;
	}
	ofstream output;
	output.open(TARGET_PATH, ios::out);
	if (!output)
	{
		cout<<"no targfile.ini"<<endl;
		return 0;
	}
	output<<""<<endl;
	output.close();
	cout<<"Done!"<<endl;
	system("pause");
	return 0;
}

