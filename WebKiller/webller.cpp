// WebKiller.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

// д��ע�����Ŀ�������, ��������Ŀ¼
string WriteRegistry()
{
	//char filePath[MAX_PATH]={0}; // ��ʼ��
	//char sysPath[MAX_PATH]="C:\\Program Files"; // ϵͳ·��
	char path[MAX_PATH]; // ���е��ļ�������·��
	HMODULE modH = GetModuleHandle(NULL);
	GetModuleFileName(modH, path, sizeof(path)); // �õ���ǰִ���ļ���ȫ·��
	// ���� _tcsrchr(path, _T('\\'))[0] = 0; // ɾ���ļ�����ֻ���·���ִ� �ֽ�Ϊ��������
	//char *ch = _tcsrchr(path, _T('\\')); //�������һ��\���ֵ�λ�ã�������\������ַ�������\��
	//strcat_s(filePath, ch); // �õ��ļ���
	//ch[0] = 0;//NULL  ͨ������������szFilePath = ��szFilePath�ضϣ��ض����һ��\������ַ���������\��
	//VrvCopyFile(path, sysPath); // �����ļ���ϵͳ
	//ch = _tcsrchr(path, _T('\\')); 
	//strcat_s(sysPath, ch);
	//strcat_s(sysPath, filePath); // �õ��ļ��µ�ȫ·��
	
	HKEY hKey; // д�뵽ע����Ա㿪���Զ�����
	// ��ע���·������HEKY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	// ����һ��ֵ����������������ֵΪҪ�������е��ļ�������·��
	RegSetValueEx(hKey, "ϵͳ��ȫ����", 0, REG_SZ, (const unsigned char*)path, sizeof(path));
	RegCloseKey(hKey); // �ر�ע���

	_tcsrchr(path, _T('\\'))[0] = 0;
	return path;
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
	char szWindowTitle[50];
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
	path += "\\config\\targetlist.dat";
	input.open(path, ios::in);
	if (!input)
	{ // �Ա� ��è �Ź� ��ɱ ���� �̳�
		cout<<"no targetlist.dat"<<endl;
		targets.push_back("�Ա�");
		targets.push_back("��è");
		targets.push_back("�Ź�");
		targets.push_back("��ɱ");
		targets.push_back("����");
		targets.push_back("�̳�");
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
	path += "\\config\\clsname.dat";
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
	int year;
	int month;
	int day;
	int sec;
	string path;
	TickClock()
	{
		year = 1900;
		month = 0;
		day = 0;
		sec = 0;
		path = TICK_PATH;
	}
	
	void NewDayUpdate()
	{
		sec = INIT_SEC;
		SYSTEMTIME st = {0};
		GetLocalTime(&st);
		year = st.wYear;
		month = st.wMonth;
		day = st.wDay;
	}

	// ����Tick״̬
	void WriteToFile()
	{
		ofstream output;
		output.open(path, ios::out);
		if (!output)
		{
			cout<<"no tickclock.ini"<<endl;
			exit(0);
		}
		char ch='-';
		output<<year<<ch<<month<<ch<<day<<" "<<sec<<endl;
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
			sec = INIT_SEC;
			return;
		}
		char ch;
		input>>year>>ch>>month>>ch>>day>>sec;
		input.close();
	}

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
	ShellExecute(NULL,"open",deskPath,NULL,NULL,SW_SHOWMAXIMIZED); 
}

// ���ػ����¼�
BOOL WINAPI ConsoleHandler(DWORD dwEvent)
{
	switch(dwEvent)
	{
	case CTRL_CLOSE_EVENT: // �رճ���ʱ
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
		gTick.WriteToFile(); // ����Tick״̬
		return TRUE;
	case CTRL_SHUTDOWN_EVENT: // �ػ�ʱ
	case CTRL_LOGOFF_EVENT: // ע��ʱ
		gTick.WriteToFile();
		return FALSE;
	default:
		return FALSE;
	}
}
bool IsTickOff()
{
	int tline = gTick.TimeLine();// �ж��������ĸ�ʱ��λ����
	if (tline == 1) // ����δ��
	{
		gTick.NewDayUpdate(); // �µ�һ�������Ϣ֮��
		gTick.WriteToFile(); // д���ļ�
	}
	else if(tline == -1) // �ص��˹�ȥ
	{
		gTick.sec = 0;
		gTick.WriteToFile();
	}
	if(gTick.sec > 0) // ʱ�仹δ����
	{
		--gTick.sec; // ʱ�����
		if (gTick.sec == REMINDING)
		{
			char tip[MAX_PATH];
			sprintf_s(tip, "\n\n�ף���������ʣ��ʱ���Ѳ���%d���ӣ��뾡�챣������״̬��\n\nע�⣺�����йرղ�ɾ��λ������ĸ��ļ���", REMINDING/60);
			RemindNotify(tip); // ״̬����
		}
		if (gTick.sec == 0)
		{
			RemindNotify("\n\n�ף������������ʱ�������꣬Ҫ�ú�ѧϰ����������Ŷ��\n\nע�⣺�����йرղ�ɾ��λ������ĸ��ļ���");
		}
		return false;
	}
	return true; // ʱ��������<= 0
}

int main(int argc, _TCHAR* argv[])
{
	// �����жϿ��ƣ����ػ��˳��ȡ�
	if (!SetConsoleCtrlHandler( (PHANDLER_ROUTINE)ConsoleHandler, TRUE))
	{
		cout<<"Unable to install handler!"<<endl;
	}
	string path = WriteRegistry(); // д��ע�����������
	vector<string> targetList; // Ŀ���ַ����б�
	vector<string> clsnames; // ���ⴰ�ڵ�����
	SetTargetList(targetList, path); // ����Ŀ���ַ����б�
	SetClsName(clsnames, path); // ���õ�������ľ��
	gTick.ReadFromFile();// ����ʱ��״̬
	HWND hwnd = NULL;
	while(true)
	{
		hwnd = FindTarget(targetList, clsnames); // ���Ŀ��
		if (hwnd && IsTickOff()) // ���Ŀ�����,����ʱ������
		{
			TerminateTarget(hwnd); // �ս�Ŀ��
		}
		Sleep(1000); // ÿ����һ��
	}
	return 0;
}