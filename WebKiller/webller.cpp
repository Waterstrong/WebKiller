// WebKiller.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


//************************************
// @Method   : VrvDeleteFile
// @FullName : VrvDeleteFile
// @Access   : public 
// @Qualifier:
// @Parameter: LPCSTR lpSrc 传入文件夹
// @Returns  : DWORD 返回执行代码，0为成功
// @Brief    : 删除文件
//************************************
DWORD VrvDeleteFile(LPCSTR lpSrc) 
{ 
	char szFile[MAX_PATH] = {0};
	lstrcpy(szFile,lpSrc);
	SHFILEOPSTRUCT shFileOp = {0};
	shFileOp.fFlags = FOF_NOCONFIRMATION;
	shFileOp.pFrom = szFile; 
	shFileOp.pTo = NULL; // 一定NULL
	shFileOp.wFunc = FO_DELETE; 
	return SHFileOperation(&shFileOp);
}

//复制的粘贴
DWORD VrvCopyFile(LPCSTR lpSrc, LPCSTR lpDst ) 
{
	char szFile[MAX_PATH] = {0};
	lstrcpy(szFile,lpSrc); // 特别重要，否则不成功。
	SHFILEOPSTRUCT shFileOp = {0};
	shFileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR;
	shFileOp.pFrom = szFile;
	shFileOp.pTo = lpDst;
	shFileOp.wFunc = FO_COPY;
	return SHFileOperation(&shFileOp); // return dwError
} 

//剪贴的粘贴
DWORD VrvMoveFile(LPCSTR lpSrc, LPCSTR lpDst) 
{ 
	char szFile[MAX_PATH] = {0}; 
	lstrcpy(szFile,lpSrc);
	SHFILEOPSTRUCT shFileOp = {0}; 
	shFileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR; 
	shFileOp.pFrom = szFile; 
	shFileOp.pTo = lpDst; 
	shFileOp.wFunc = FO_MOVE;
	return SHFileOperation(&shFileOp); // return dwError
} 

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

// 关闭窗口
void ForceCloseWindow(HWND hwnd)
{
	SendMessage(hwnd, WM_CLOSE, 0, 0);
	DestroyWindow(hwnd);
	PostMessage(hwnd, WM_QUIT, 0, 0);
}

// 终结目标名单
void TerminateTargets(vector<string> targets, vector<string> clsnames)
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
			ForceCloseWindow(hwnd); // 关闭窗口
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
				ForceCloseWindow(hwnd); // 关闭窗口
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
				ForceCloseWindow(hwnd); // 关闭窗口
			}
		}
	}
}

// 时间段
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

// 设置时间段
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

// 判断是否在时间盒子内
bool SafeTimeBucket(vector<TimeInterval> inters)
{
	// 获取当前时间
	time_t now = time(NULL);
	struct tm fmt;
	localtime_s(&fmt, &now);
	int minutes = fmt.tm_hour*60 + fmt.tm_min;
	// 当前时间与设定的时间段比较,如果在时间盒内表明不终结
	for(vector<TimeInterval>::iterator it = inters.begin(); it != inters.end(); ++it)
	{
		if (minutes >= (*it).start && minutes <= (*it).end)
		{
			return true;
		}
	}
	return false;
}
int main(int argc, _TCHAR* argv[])
{
	string path = WriteRegistry(); // 写入注册表，开机启动
	vector<string> targetList; // 目标字符串列表
	vector<TimeInterval> intervals; // 时间段
	vector<string> clsnames; // 特殊窗口的类名
	SetTargetList(targetList, path); // 设置目标字符串列表
	SetTimeInterval(intervals, path); // 设置时间段
	SetClsName(clsnames, path); // 设置单独处理的句柄
	while(true)
	{
		if (!SafeTimeBucket(intervals)) // 不在安全时间段内就结束
		{
			TerminateTargets(targetList, clsnames); // 终结目标
		}
		Sleep(1000); // 每秒监测一次
	}
	return 0;
}