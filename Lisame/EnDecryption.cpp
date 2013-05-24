#include "StdAfx.h"
#include "EnDecryption.h"


EnDecryption::EnDecryption(void)
{
	distance = ""; 
	cryptograph = "";   
	realPwd = ""; 
}


EnDecryption::~EnDecryption(void)
{
}

string EnDecryption::GetRealPwd()
{
	realPwd = "";
	int nRealStrLength = cryptograph.length();
	string pwd = cryptograph.substr(0, nRealStrLength / 2);
	string dis = cryptograph.substr(nRealStrLength / 2);
	for (int i = 0; i < nRealStrLength / 2; i++ )
	{
		char ch = (char)(pwd[i] + dis[i] - 48);
		realPwd += ch;
	}
	return realPwd;
}

string EnDecryption::GetCryptograph()
{
	string strReal = "";
	int nPwdLength = realPwd.length();
	srand((unsigned)time(NULL)); 
	distance = "";
	for (int i = 0; i < nPwdLength; i++)
	{
		int nRandNumber = rand() % 9;
		char ch = (char)(realPwd[i] - nRandNumber);
		strReal += ch;
		distance += (char)(nRandNumber + 48);
	}
	strReal += distance;
	return strReal;
}

void EnDecryption::SetCryptograph(string value)
{
	cryptograph = value;
	int nRealStrLength = cryptograph.length();
	realPwd = cryptograph.substr(0, nRealStrLength / 2);
	distance = cryptograph.substr(nRealStrLength / 2);
}