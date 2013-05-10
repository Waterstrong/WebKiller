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

int TickSecond = 0; // ʱ������
// �ȴ�һ��
void WaitASecond()
{
	Sleep(1000); // ÿ����һ��
	++TickSecond;
}

// �رմ���
void ForceCloseWindow(HWND hwnd)
{
	// �����˳�����
	SendMessage(hwnd, WM_CLOSE, 0, 0);
	DestroyWindow(hwnd);
	PostMessage(hwnd, WM_QUIT, 0, 0);
	WaitASecond(); // �ȴ�ʱ��һ��
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

// �ս�Ŀ������
void TerminateTargets(vector<string> targets, vector<string> clsnames)
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
			ForceCloseWindow(hwnd); // �رմ���
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
				ForceCloseWindow(hwnd); // �رմ���
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
				ForceCloseWindow(hwnd); // �رմ���
			}
		}
	}
}

// ʱ���
struct TimeInterval
{
	TimeInterval()
	{
		start = 0;
		end = 0;
	}
	TimeInterval(int s, int e)
	{
		start = s;
		end = e;
	}
	int start;
	int end;
};

// ����ʱ���
void SetTimeInterval(vector<TimeInterval>& inters, string path)
{
	ifstream input;
	path += "\\config\\safeinter.dat";
	input.open(path, ios::in);
	char colon;
	int hour[2], minute[2];
	while(!input.eof())
	{
		if (input.fail())
		{
			break;
		}
		input>>hour[0]>>colon>>minute[0]>>hour[1]>>colon>>minute[1];
		inters.push_back(TimeInterval(hour[0]*60+minute[0], hour[1]*60+minute[1]));
	}
	input.close();
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

// �ж��Ƿ���ʱ�������
bool SafeTimeBucket(vector<TimeInterval> inters)
{
	// ��ȡ��ǰʱ��
	int minutes = TickSecond / 60;
	// ��ǰʱ�����趨��ʱ��αȽ�,�����ʱ����ڱ������ս�
	for(vector<TimeInterval>::iterator it = inters.begin(); it != inters.end(); ++it)
	{
		if (minutes >= (*it).start && minutes <= (*it).end)
		{
			return true;
		}
	}
	return false;
}

// ʱ��У׼ͬ��
void SyncTickSecond()
{
	// ��ȡ��ǰʱ��
	time_t now = time(NULL);
	struct tm fmt;
	localtime_s(&fmt, &now);
	TickSecond = (fmt.tm_hour*60+fmt.tm_min)*60 + fmt.tm_sec; // ͬ��
}

// �ж��Ƿ�ͬ����
bool IsTickSecondSync()
{
	// ��ȡ��ǰʱ��
	time_t now = time(NULL);
	struct tm fmt;
	localtime_s(&fmt, &now);
	int sec = (fmt.tm_hour*60+fmt.tm_min)*60 + fmt.tm_sec;
	if (abs(TickSecond - sec) < SEC_ACC)
	{
		TickSecond = sec; // У׼
		return true;
	}
	return false;
}

int main(int argc, _TCHAR* argv[])
{
 	string path = WriteRegistry(); // д��ע�����������
 	vector<string> targetList; // Ŀ���ַ����б�
 	vector<TimeInterval> intervals; // ʱ���
 	vector<string> clsnames; // ���ⴰ�ڵ�����
 	SetTargetList(targetList, path); // ����Ŀ���ַ����б�
 	SetTimeInterval(intervals, path); // ����ʱ���
 	SetClsName(clsnames, path); // ���õ�������ľ��
	SyncTickSecond(); // У׼ʱ��
	int clockTmp = 0; // ��ʱʱ��
	bool isSync = true; // ͬ�����
 	while(true)
	{
		if (isSync) // �����ͬ���ľ�Ҫ�ж��Ƿ��ڰ�ȫʱ����
		{
			if (!SafeTimeBucket(intervals)) // ���ڰ�ȫʱ����ھͽ���
			{
				TerminateTargets(targetList, clsnames); // �ս�Ŀ��
			}
			if (clockTmp++ % SYNC_PERIOD == 0) // ÿһ��������У׼һ��
			{
				clockTmp = 0; // ����
				if (!IsTickSecondSync()) // �ж�ʱ���Ƿ�ͬ��
				{
					isSync = false;
				}
			}
		}
		else // ����ֱ�Ӳ����ж�ȫ���ж�
		{
			TerminateTargets(targetList, clsnames); // �ս�Ŀ��
		}
		WaitASecond(); // �ȴ�ʱ��һ��
 	}
	return 0;
}