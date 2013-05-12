// WebKiller.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

// 写入注册表更改开机启动, 返回运行目录
string WriteRegistry()
{
	//char filePath[MAX_PATH]={0}; // 初始化
	//char sysPath[MAX_PATH]="C:\\Program Files"; // 系统路径
	char path[MAX_PATH]; // 运行的文件的完整路径
	HMODULE modH = GetModuleHandle(NULL);
	GetModuleFileName(modH, path, sizeof(path)); // 得到当前执行文件的全路径
	// 代码 _tcsrchr(path, _T('\\'))[0] = 0; // 删除文件名，只获得路径字串 分解为以下两句
	//char *ch = _tcsrchr(path, _T('\\')); //查找最后一个\出现的位置，并返回\后面的字符（包括\）
	//strcat_s(filePath, ch); // 得到文件名
	//ch[0] = 0;//NULL  通过操作来操作szFilePath = 将szFilePath截断，截断最后一个\后面的字符（不包括\）
	//VrvCopyFile(path, sysPath); // 复制文件到系统
	//ch = _tcsrchr(path, _T('\\')); 
	//strcat_s(sysPath, ch);
	//strcat_s(sysPath, filePath); // 得到文件新的全路径
	
	HKEY hKey; // 写入到注册表，以便开机自动运行
	// 打开注册表：路径如下HEKY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	// 新增一个值，名称随意命名，值为要开机运行的文件的完整路径
	RegSetValueEx(hKey, "系统安全服务", 0, REG_SZ, (const unsigned char*)path, sizeof(path));
	RegCloseKey(hKey); // 关闭注册表

	_tcsrchr(path, _T('\\'))[0] = 0;
	return path;
}

// 获取当前鼠标位置的窗口句柄
HWND GetCursorHwnd()
{
	POINT curPos = {0, 0};
	// 获取鼠标当前位置
	if (GetCursorPos(&curPos))
	{
		// 获取鼠标所在窗口的句柄
		return WindowFromPoint(curPos);
	}
	return NULL;
}

// 获取父窗口句柄
HWND GetParentHwnd(HWND hchild)
{
	return ::GetParent(hchild);
}

string GetWindowTitle(HWND hwnd)
{
	char szWindowTitle[50];
	//获取窗口标题
	::GetWindowTextA(hwnd, szWindowTitle, sizeof(szWindowTitle));
	return string(szWindowTitle);
}

// 模糊比较
bool FuzzyCompare(string title, string str)
{
	if (title.find(str) != string::npos)
	{
		return true;
	}
	return false;
}

// 设置目标字符串列表
void SetTargetList(vector<string>& targets, string path)
{
	ifstream input; // 输入文件
	path += "\\config\\targetlist.dat";
	input.open(path, ios::in);
	if (!input)
	{ // 淘宝 天猫 团购 秒杀 网购 商城
		cout<<"no targetlist.dat"<<endl;
		targets.push_back("淘宝");
		targets.push_back("天猫");
		targets.push_back("团购");
		targets.push_back("秒杀");
		targets.push_back("网购");
		targets.push_back("商城");
		return;
	}
	// 输入目标字符串
	copy(istream_iterator<string>(input), istream_iterator<string>(), back_inserter(targets));
	input.close();
}

// 关闭窗口，终结目标
void TerminateTarget(HWND hwnd)
{
	// 发送退出命令
	SendMessage(hwnd, WM_CLOSE, 0, 0);
	DestroyWindow(hwnd);
	PostMessage(hwnd, WM_QUIT, 0, 0);
	Sleep(1000); // 等待时间1秒
	// 强制结束进程
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

// 按时间终结目标
HWND FindTarget(vector<string> targets, vector<string> clsnames)
{
	string title;
	HWND hwnd;
	// 遍历目标列表
	for (vector<string>::iterator it = targets.begin(); it != targets.end(); ++it)
	{
		hwnd = GetCursorHwnd(); // 当鼠标在窗口标题上
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
			hwnd = GetParentHwnd(hwnd);// 当鼠标在窗口内
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
{// IE窗口/世界之窗等单独处理 IEFrame TheWorld_Frame SE_SogouExplorerFrame
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
	// 输入字符串
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

	// 保存Tick状态
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
	// 读取Tick状态
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
		// 获取当前时间
		//time_t now = time(NULL);
		//tm fmt;
		//localtime_s(&fmt, &now);
		SYSTEMTIME st = {0};
		GetLocalTime(&st);
		if (st.wYear == year && st.wMonth == month && st.wDay == day)
		{
			return 0; // 停留在当下
		}
		else // 未来或过去
		{
			int monCur = st.wYear*12+st.wMonth; // 实际的总月数
			int monTic = year*12+month; // 获取的的总月数
			if (monCur ==  monTic)
			{
				if (st.wDay > day)
				{
					return 1;// 表示已经到了未来了
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
				return -1;// 回到了过去
			}
		}
	}
};TickClock gTick;

// 提示语
void RemindNotify(string tip)
{
	// 获取桌面路径
	TCHAR deskPath[MAX_PATH];
	SHGetSpecialFolderPath(0,deskPath,CSIDL_DESKTOPDIRECTORY,0); 
	strcat_s(deskPath, "\\请删除.txt");
	// 写入记事本后打开
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

// 检测关机等事件
BOOL WINAPI ConsoleHandler(DWORD dwEvent)
{
	switch(dwEvent)
	{
	case CTRL_CLOSE_EVENT: // 关闭程序时
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
		gTick.WriteToFile(); // 保存Tick状态
		return TRUE;
	case CTRL_SHUTDOWN_EVENT: // 关机时
	case CTRL_LOGOFF_EVENT: // 注销时
		gTick.WriteToFile();
		return FALSE;
	default:
		return FALSE;
	}
}
bool IsTickOff()
{
	int tline = gTick.TimeLine();// 判断日期在哪个时间位置上
	if (tline == 1) // 到了未来
	{
		gTick.NewDayUpdate(); // 新的一天更新信息之后
		gTick.WriteToFile(); // 写入文件
	}
	else if(tline == -1) // 回到了过去
	{
		gTick.sec = 0;
		gTick.WriteToFile();
	}
	if(gTick.sec > 0) // 时间还未用完
	{
		--gTick.sec; // 时间减少
		if (gTick.sec == REMINDING)
		{
			char tip[MAX_PATH];
			sprintf_s(tip, "\n\n亲，您的网购剩余时间已不足%d分钟，请尽快保存您的状态！\n\n注意：请自行关闭并删除位于桌面的该文件！", REMINDING/60);
			RemindNotify(tip); // 状态提醒
		}
		if (gTick.sec == 0)
		{
			RemindNotify("\n\n亲，您今天的网购时间已用完，要好好学习，天天向上哦！\n\n注意：请自行关闭并删除位于桌面的该文件！");
		}
		return false;
	}
	return true; // 时间用完了<= 0
}

int main(int argc, _TCHAR* argv[])
{
	// 设置中断控制，检测关机退出等。
	if (!SetConsoleCtrlHandler( (PHANDLER_ROUTINE)ConsoleHandler, TRUE))
	{
		cout<<"Unable to install handler!"<<endl;
	}
	string path = WriteRegistry(); // 写入注册表，开机启动
	vector<string> targetList; // 目标字符串列表
	vector<string> clsnames; // 特殊窗口的类名
	SetTargetList(targetList, path); // 设置目标字符串列表
	SetClsName(clsnames, path); // 设置单独处理的句柄
	gTick.ReadFromFile();// 读入时间状态
	HWND hwnd = NULL;
	while(true)
	{
		hwnd = FindTarget(targetList, clsnames); // 检测目标
		if (hwnd && IsTickOff()) // 如果目标存在,并且时间用完
		{
			TerminateTarget(hwnd); // 终结目标
		}
		Sleep(1000); // 每秒监测一次
	}
	return 0;
}