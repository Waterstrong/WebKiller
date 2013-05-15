// WebKiller.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

// д��ע�����Ŀ�������
string WriteRegistry()
{
	char sysPath[MAX_PATH]={0}; // ϵͳ·��
	char filePath[MAX_PATH]; // ���е��ļ�������·��
	HMODULE modH = GetModuleHandle(NULL);
	GetModuleFileName(modH, filePath, sizeof(filePath)); // �õ���ǰִ���ļ���ȫ·��

	strcpy_s(sysPath, SYSTEM_PATH); //�õ�ϵͳĿ¼��·��
	strcat_s(sysPath, "\\"); //�γ�Ҫ���Ƶ���ȫ·��
	strcat_s(sysPath, NEW_FILE);
	char tmpCh[MAX_PATH];
	strcpy_s(tmpCh, sysPath);
	size_t i; // ת��ΪСд�Ƚ�
	for (i = 0; i < strlen(filePath); ++i)
	{
		filePath[i] = tolower(filePath[i]);
	}
	for (i = 0; i < strlen(tmpCh); ++i)
	{
		tmpCh[i] = tolower(tmpCh[i]);
	}
	// ��������Լ�������
	if (strcmp(filePath, tmpCh) != 0)
	{
		sprintf_s(tmpCh, "taskkill /f /im %s", NEW_FILE);
		system(tmpCh); // ����֮ǰ���еĳ���
		CopyFile(filePath, sysPath, false);//���Ҹ��Ƶ�Ŀ��·�������Ǵ����ļ�

		HKEY hKey; // д�뵽ע����Ա㿪���Զ�����
		// ��ע���·������HEKY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run
		RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
		// ����һ��ֵ����������������ֵΪҪ�������е��ļ�������·��
		RegSetValueEx(hKey, "ϵͳ��ȫ����", 0, REG_SZ, (const unsigned char*)sysPath, sizeof(sysPath));
		RegCloseKey(hKey); // �ر�ע���

		ShellExecute(NULL,"open", sysPath, NULL, NULL, SW_SHOWNORMAL);
		//system(sysPath);
		//WinExec(sysPath, SW_SHOWNORMAL);
		return "exit";
	}
	else
	{
		_tcsrchr(sysPath, _T('\\'))[0] = 0;
		return sysPath; // �������е�·��
	}
}

// ��ȡ��ǰ���λ�õĴ��ھ��
HWND GetCursorHwnd()
{
	POINT curPos = {0, 0};
	// ��ȡ��굱ǰλ��
	if (GetCursorPos(&curPos))
	{
		// ��ȡ������ڴ��ڵľ��
		return WindowFromPoint(curPos);
	}
	return NULL;
}

// ��ȡ�����ھ��
HWND GetParentHwnd(HWND hchild)
{
	return ::GetParent(hchild);
}

string GetWindowTitle(HWND hwnd)
{
	TCHAR szWindowTitle[100];
	//��ȡ���ڱ���
	::GetWindowTextA(hwnd, szWindowTitle, sizeof(szWindowTitle));
	return string(szWindowTitle);
}

// ģ���Ƚ�
bool FuzzyCompare(string title, string str)
{
	if (title.find(str) != string::npos)
	{
		return true;
	}
	return false;
}

// ����Ŀ���ַ����б�
void SetTargetList(vector<string>& targets, string path)
{
	ifstream input; // �����ļ�
	path += TARGET_FILE;
	input.open(path, ios::in);
	if (!input)
	{ // �Ա� ��è �Ź� ��ɱ ���� ���� �̳�
		cout<<"no targetlist.dat"<<endl;
		targets.push_back("�Ա�");
		targets.push_back("��è");
		targets.push_back("�Ź�");
		targets.push_back("��ɱ");
		targets.push_back("����");
		targets.push_back("����");
		targets.push_back("�̳�");
		targets.push_back("��Ʒ");
		targets.push_back("Ůװ");
		targets.push_back("�����");
		targets.push_back("ΨƷ��");
		targets.push_back("����");
		//targets.push_back("�Ż�");
		//targets.push_back("�ۿ�");
		//targets.push_back("����");
		//targets.push_back("����");
		//targets.push_back("�ػ�");
		//targets.push_back("����");
		//targets.push_back("��װ");
		//targets.push_back("����");
		//targets.push_back("��̩");
		return;
	}
	// ����Ŀ���ַ���
	copy(istream_iterator<string>(input), istream_iterator<string>(), back_inserter(targets));
	input.close();
}

// �رմ��ڣ��ս�Ŀ��
void TerminateTarget(HWND hwnd)
{
	// �����˳�����
	SendMessage(hwnd, WM_CLOSE, 0, 0);
	DestroyWindow(hwnd);
	PostMessage(hwnd, WM_QUIT, 0, 0);
	Sleep(1000); // �ȴ�ʱ��1��
	// ǿ�ƽ�������
	DWORD dwProcId = 0;
	if (GetWindowThreadProcessId(hwnd, &dwProcId))  
	{       
		HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, dwProcId);
		if (hProc != NULL)
		{          
			TerminateProcess(hProc, 0);
			CloseHandle(hProc); 
		}
	}
}

// ��ʱ���ս�Ŀ��
HWND FindTarget(vector<string> targets, vector<string> clsnames)
{
	string title;
	HWND hwnd;
	// ����Ŀ���б�
	for (vector<string>::iterator it = targets.begin(); it != targets.end(); ++it)
	{
		hwnd = GetCursorHwnd(); // ������ڴ��ڱ�����
		title = GetWindowTitle(hwnd);
		if ( FuzzyCompare(title, *it))
		{
			return hwnd;
		}
		else
		{
			if (!hwnd)
			{
				continue;
			}
			hwnd = GetParentHwnd(hwnd);// ������ڴ�����
			title = GetWindowTitle(hwnd);
			if (FuzzyCompare(title, *it) )
			{
				return hwnd;
			}
		}
		for (vector<string>::iterator its = clsnames.begin(); its != clsnames.end(); ++its)
		{
			hwnd = FindWindow((*its).c_str(), NULL);
			if (!hwnd)
			{
				continue;
			}
			title = GetWindowTitle(hwnd);
			if (FuzzyCompare(title, *it))
			{
				return hwnd;
			}
		}
	}
	return NULL;
}

void SetClsName(vector<string>& clsnames, string path)
{// IE����/����֮���ȵ������� IEFrame TheWorld_Frame SE_SogouExplorerFrame
	ifstream input;
	path += CLSNAME_FILE;
	input.open(path, ios::in);
	if (!input)
	{
		cout<<"no clsname.dat"<<endl;
		clsnames.push_back("IEFrame");
		clsnames.push_back("TheWorld_Frame");
		clsnames.push_back("SE_SogouExplorerFrame");
		return;
	}
	// �����ַ���
	copy(istream_iterator<string>(input), istream_iterator<string>(), back_inserter(clsnames));
	input.close();
}

struct TickClock
{
	int year; // ������
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int clockSec; // ��ʱ��������Ϊ��λ
	string path; // �ļ�·��
	TickClock()
	{
		year = 1900;
		month = 1;
		day = 1;
		hour = 0;
		minute = 0;
		second = 0;
		clockSec = 0;
		path = TICK_PATH;
	}
	// �µ�һ����Ҫ�������ں�ʱ��
	void UpdateDateTime()
	{
		// �޸�Ϊ��ǰʱ��
		SYSTEMTIME st = {0};
		GetLocalTime(&st);
		year = st.wYear;
		month = st.wMonth;
		day = st.wDay;
		hour = st.wHour;
		minute = st.wMinute;
		second = st.wSecond;
	}

	// ����Tick״̬
	void WriteToFile()
	{
		ofstream output;
		output.open(path, ios::out);
		if (!output)
		{
			cout<<"no tickclock.ini"<<endl;
			return;
		}
		output<<year<<"-"<<month<<"-"<<day<<" "
			<<hour<<":"<<minute<<":"<<second<<" "
			<<clockSec<<endl;
		output.close();
	}
	// ��ȡTick״̬
	void ReadFromFile()
	{
		ifstream input;
		input.open(path, ios::in);
		if (!input)
		{
			cout<<"no tickclock.ini"<<endl;
			return;
		}
		char ch;
		input>>year>>ch>>month>>ch>>day
			>>hour>>ch>>minute>>ch>>second
			>>clockSec;
		input.close();
	}
	// �ж�ʱ���� 1δ����0���ڣ�-1��ȥ
	int TimeLine()
	{
		// ��ȡ��ǰʱ��
		//time_t now = time(NULL);
		//tm fmt;
		//localtime_s(&fmt, &now);
		SYSTEMTIME st = {0};
		GetLocalTime(&st);
		if (st.wYear == year && st.wMonth == month && st.wDay == day)
		{
			return 0; // ͣ���ڵ���
		}
		else // δ�����ȥ
		{
			int monCur = st.wYear*12+st.wMonth; // ʵ�ʵ�������
			int monTic = year*12+month; // ��ȡ�ĵ�������
			if (monCur ==  monTic)
			{
				if (st.wDay > day)
				{
					return 1;// ��ʾ�Ѿ�����δ����
				}
				else
				{
					return -1;
				}
			}
			else if (monCur > monTic)
			{
				return 1;
			}
			else
			{
				return -1;// �ص��˹�ȥ
			}
		}
	}
};TickClock gTick;

// ��ʾ��
void RemindNotify(string tip)
{
	// ��ȡ����·��
	TCHAR deskPath[MAX_PATH];
	SHGetSpecialFolderPath(0,deskPath,CSIDL_DESKTOPDIRECTORY,0); 
	strcat_s(deskPath, "\\��ɾ��.txt");
	// д����±����
	ofstream output;
	output.open(deskPath, ios::out);
	if (!output)
	{
		cout<<"no remind.txt"<<endl;
		return;
	}
	output<<tip<<endl;
	output.close();
	//TCHAR filePath[MAX_PATH];
	//sprintf_s(filePath, "Notepad.exe %s", deskPath);
	//WinExec(filePath, SW_SHOWMAXIMIZED);
	ShellExecute(NULL,"open",deskPath,NULL,NULL,SW_SHOWMAXIMIZED); 
}

bool IsTickOff()
{
	int tline = gTick.TimeLine();// �ж��������ĸ�ʱ��λ����
	if (tline == 1) // ����δ��
	{
		gTick.UpdateDateTime(); // �µ�һ��������ں�ʱ��
		gTick.clockSec = INIT_SEC; // ��ʼ����ʱ��
		gTick.WriteToFile(); // д���ļ�
	}
	else if(tline == -1 && gTick.clockSec != 0) // �ص��˹�ȥ
	{
		gTick.clockSec = 0; // ����
		gTick.WriteToFile();
	}
	if(gTick.clockSec > 0) // ʱ�仹δ����
	{
		--gTick.clockSec; // ʱ�����
		if (gTick.clockSec == REMINDING || gTick.clockSec == 0)
		{
			char tip[MAX_PATH] = {0};
			SYSTEMTIME st = {0};
			GetLocalTime(&st);
			if (gTick.clockSec == 0)
			{
				sprintf_s(tip, "%d-%d-%d %d:%d:%d\n\n�ף������������ʱ�������꣬Ҫ�ú�ѧϰ����������Ŷ��\n\nע�⣺�����йرղ�ɾ��λ������ĸ��ļ���",
					st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
				gTick.UpdateDateTime();
				gTick.WriteToFile();
			}
			else
			{
				sprintf_s(tip, "%d-%d-%d %d:%d:%d\n\n�ף���������ʣ��ʱ���Ѳ���%d���ӣ��뾡�챣������״̬��\n\nע�⣺�����йرղ�ɾ��λ������ĸ��ļ���",
					st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, REMINDING/60);
			}
			RemindNotify(tip); // ״̬����
		}
		return false;
	}
	return true; // ʱ��������<= 0
}

int main(int argc, _TCHAR* argv[])
{
	string path = WriteRegistry(); // д�뿪ʼ���в��ж�·��
 	if (path == "exit")
 	{
 		return 0; // �������
 	}
	vector<string> targetList; // Ŀ���ַ����б�
	vector<string> clsnames; // ���ⴰ�ڵ�����
	SetTargetList(targetList, path); // ����Ŀ���ַ����б�
	SetClsName(clsnames, path); // ���õ�������ľ��
	gTick.ReadFromFile();// ����ʱ��״̬
	HWND hwnd = NULL;
	bool writeFlag = false;
	int cntSec = 0;
	while(true)
	{
		hwnd = FindTarget(targetList, clsnames); // ���Ŀ��
		if (hwnd) // ���Ŀ�����,����ʱ������
		{
			if (IsTickOff())
			{
				TerminateTarget(hwnd); // �ս�Ŀ��
			}
			else
			{
				writeFlag = true; // Ҫд���ļ���
			}
		}
		if (++cntSec == SAVE_FREQ)
		{
			cntSec = 0;
			if (writeFlag)
			{
				writeFlag = false;
				gTick.UpdateDateTime(); // ����ʱ��
				gTick.WriteToFile(); // д���ļ�����״̬
			}
		}
		Sleep(1000); // ÿ����һ��
	}
	return 0;
}