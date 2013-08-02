// TargCon.cpp : 定义控制台应用程序的入口点。
//
//************************************
// @FileName: TargCon.cpp
// @Brief   : 目标配置文件的修改
// @Author  : Waterstrong
// @DateTime: 2013-7-4 20:29:52
//************************************
#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// "淘宝" "天猫" "团购" "商城" "正品" "亚马逊";
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

