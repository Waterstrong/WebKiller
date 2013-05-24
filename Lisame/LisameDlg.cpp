
// LisameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Lisame.h"
#include "LisameDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLisameDlg 对话框




CLisameDlg::CLisameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLisameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_keypath = _T("");
}

void CLisameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, m_keypath);
	DDX_Control(pDX, IDC_BUTTON_CHOOSE, m_btnChoose);
}

BEGIN_MESSAGE_MAP(CLisameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_QUERY, &CLisameDlg::OnBnClickedButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE, &CLisameDlg::OnBnClickedButtonChoose)
	ON_BN_CLICKED(IDC_BUTTON_LISA, &CLisameDlg::OnBnClickedButtonLisa)
END_MESSAGE_MAP()


// CLisameDlg 消息处理程序

BOOL CLisameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLisameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLisameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLisameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLisameDlg::OnBnClickedButtonQuery()
{
	TickClock tickClock;
	if (!tickClock.ReadFromFile())
	{
		MessageBox(L"计时配置文件读取/解析失败！", L"提示", MB_ICONSTOP|MB_OK);
		return;
	}
	CString tip;
	tip.Format(L"亲，您的网购剩余时间大约还有 %d 分钟。", tickClock.ClockSec()/60 );
	MessageBox(tip, L"提示", MB_ICONINFORMATION|MB_OK);
}


void CLisameDlg::OnBnClickedButtonChoose()
{
	CFileDialog fileDialog(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL, 
		NULL,
		OFN_FILEMUSTEXIST, //OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		L"验证钥文件(*.gen)|*.gen||",
		NULL);
	if(fileDialog.DoModal()==IDOK)
	{
		m_keypath = fileDialog.GetPathName(); //文件名保存在了FilePathName里
		UpdateData(FALSE);
	}
}


void CLisameDlg::OnBnClickedButtonLisa()
{
	UpdateData(TRUE);
	string strKey;
	if (!Decrypt(strKey)) // 解码
	{
		return;
	}
	CString cstr(strKey.c_str());
	CStringArray splitKey; // yyhua#19:54:33#2013-5-23#ONEHOUR#19:54:33
	ExtractString(splitKey, cstr, L"#"); // 分隔字符串
	if (!VerifyValidKey(splitKey)) // 验证有效性
	{
		return;
	}
	int clockSec = Type2Clock(splitKey[3]);
	if (clockSec == 0)
	{
		return;
	}
	if (WriteKey2TickFile(splitKey[2]+" "+splitKey[1], clockSec))
	{
		CString tip;
		tip.Format(L"网购时长设置成功！\n亲，您现在已有 %d 分钟的网购时长，祝您网购愉快！", clockSec / 60 );
		MessageBox(tip, L"提示", MB_ICONINFORMATION|MB_OK);
	}
}

// 将一个字符串分解后放到一个CStringArray中
void CLisameDlg::ExtractString(CStringArray& arr, const CString strSrc, const CString sep)
{
	// 预处理: 可根据需要决定是否需要Trim，以及是Trim掉空格/还是分隔符/还是其它
	CString str(strSrc);
	str.TrimLeft(); 
	str.TrimRight();

	if(str.IsEmpty())
		return;

	// 开始分解
	int pos = str.Find(sep);
	while (pos != -1)
	{
		//if(!str.Left(pos).IsEmpty()) // 如有必要也可在此Trim后再判断是否为空，为空则舍弃
		arr.Add(str.Left(pos));

		str = str.Mid(pos + sep.GetLength());
		pos = str.Find(sep);
	}
	arr.Add(str); // think
}


// 类型转化为时间秒
int CLisameDlg::Type2Clock(CString type)
{
	int clockSec = 0;
	if (type == "TENTEST")
	{
		clockSec = 605;
	}
	else if ("HALFHOUR")
	{
		clockSec = 1800;
	}
	else if ("ONEHOUR")
	{
		clockSec = 3600;
	}
	else if ("TWOHOUR")
	{
		clockSec = 7200;
	}
	else if ("THREEHOUR")
	{
		clockSec = 10800;
	}
	else
	{
		MessageBox(L"验证钥类型认证失败！", L"提示", MB_ICONSTOP|MB_OK);
	}
	return clockSec;
}


// 写入到Tick文件中
bool CLisameDlg::WriteKey2TickFile(CString strKeyTime, int clockSec)
{
	TickClock tickClock;
	if (!tickClock.ReadFromFile())
	{
		MessageBox(L"计时配置文件读取/解析失败！", L"提示", MB_ICONSTOP|MB_OK);
		return false;
	}
	CTime dtTick(tickClock.Year(), tickClock.Month(), tickClock.Day(), tickClock.Hour(), tickClock.Minute(), tickClock.Second());
	CTime dtNow = CTime::GetCurrentTime();
	CString strNowDate = dtNow.Format("%Y-%m-%d");
	CString strTickDate = dtTick.Format("%Y-%m-%d");
	if (strTickDate != strNowDate)
	{
		MessageBox(L"系统时间可能被更改，日期验证失败！", L"提示", MB_ICONSTOP|MB_OK);
		return false;
	}
	if (!VerifyUniqueKey( strKeyTime, strNowDate ) )
	{
		return false;
	}
	
	// 结束程序
	CString newfile(NEW_FILE);
	KillProcess(newfile);

	// 重新配置网购时长
	tickClock.Year() = dtNow.GetYear();
	tickClock.Month() = dtNow.GetMonth();
	tickClock.Day() = dtNow.GetDay();
	tickClock.Hour() = dtNow.GetHour();
	tickClock.Minute() = dtNow.GetMinute();
	tickClock.Second() = dtNow.GetSecond();
	tickClock.ClockSec() = clockSec;
	if (!tickClock.WriteToFile()) // 写入文件保存
	{
		return false;
	}

	// 再启动程序
	CString sysPath(SYSTEM_PATH);// 得到系统目录的路径
	sysPath += "\\";
	sysPath += NEW_FILE; //形成要复制到的全路径
	ShellExecute(NULL,L"open", sysPath, NULL, NULL, SW_SHOWNORMAL);

	// 删除验证钥文件
	VrvDeleteFile(m_keypath);
	m_keypath = "";
	UpdateData(FALSE);
	return true;
}

// 译码
bool CLisameDlg::Decrypt(string& strKey)
{
	if (m_keypath.Trim() == "")
	{
		MessageBox(L"请选择验证钥文件！", L"提示", MB_ICONWARNING|MB_OK);
		m_btnChoose.SetFocus();
		return false;
	}
	ifstream input;
	input.open(m_keypath.Trim(), ios::in);
	if (!input)
	{
		MessageBox(L"读取验证钥文件失败，找不到文件！", L"提示", MB_ICONWARNING|MB_OK);
		return false;
	}
	getline(input, strKey);
	input.close();
	EnDecryption ende;
	ende.SetCryptograph(strKey);
	strKey = ende.GetRealPwd(); // 解密
	return true;
}


// 验证有效性
bool CLisameDlg::VerifyValidKey(CStringArray& splitKey)
{
	if (splitKey.GetCount() != 5)
	{
		MessageBox(L"验证钥文件数据被破坏，解析失败！", L"提示", MB_ICONSTOP|MB_OK);
		return false;
	}
	if (splitKey[1] != splitKey[4])
	{
		MessageBox(L"验证钥文件数据被破坏，解析失败！", L"提示", MB_ICONSTOP|MB_OK);
		return false;
	}
	if (splitKey[0] != IDENTITY)
	{
		MessageBox(L"验证钥身份认证失败！", L"提示", MB_ICONSTOP|MB_OK);
		return false;
	}
	//int year, month, day, hour, minute, second;
	//sscanf(splitKey[2], "%d-%d-%d", &year, &month, &day);
	//sscanf(splitKey[1], "%d:%d:%d", &hour, &minute, &second); 
	//CTime dtKey(year, month, day, hour, minute, second);
	CTime dtNow = CTime::GetCurrentTime();
	CString strNowDate = dtNow.Format("%Y-%m-%d");
	if (splitKey[2] != strNowDate)
	{
		MessageBox(L"验证钥已过期或失效！", L"提示", MB_ICONSTOP|MB_OK);
		return false;
	}
	return true;
}


// 验证唯一性
bool CLisameDlg::VerifyUniqueKey(CString strKeyTime, CString strNowDate)
{
	ifstream input;
	input.open(VERIFI_PATH, ios::in);
	if (!input)
	{
		if (!WriteVerifi2File(strKeyTime))
		{
			return false;
		}
	}
	else
	{
		string strVerifi;
		getline(input, strVerifi);
		input.close();
		CString cstr(strVerifi.c_str());
		CStringArray splitVerifi;
		ExtractString(splitVerifi, cstr, L"#");
		if(splitVerifi.GetCount() == 0)
		{
			if (!WriteVerifi2File(strKeyTime))
			{
				return false;
			}
		}
		// 判断验证钥是否当天被使用了，过了当天后自动清除，因为过期了
		else if (splitVerifi[0].SpanExcluding(L" ") != strNowDate)//splitVerifi[0].Left(splitVerifi[0].Find(L' '))
		{
			if (!WriteVerifi2File(strKeyTime))
			{
				return false;
			}
		}
		else
		{
			int i;
			for (i = 0; i < splitVerifi.GetCount(); ++i)
			{
				if (splitVerifi[i] == strKeyTime)
				{
					MessageBox(L"该验证钥不能重复验证！", L"提示", MB_ICONSTOP|MB_OK);
					return false;
				}
			}
			WriteVerifi2File(L"#" + strKeyTime, true);
		}
	}
	return true;
}


// 将验证信息写入文件, append==true表示追加
bool CLisameDlg::WriteVerifi2File(CString cstr, bool append)
{
	CStdioFile file;
	CString path(VERIFI_PATH);
	file.Open(path, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
	if (!file.m_pStream)
	{
		MessageBox(L"验证文件写入时出错！", L"提示", MB_ICONSTOP|MB_OK);
		return false;
	}
	if (append == true)
	{
		file.SeekToEnd();
	}
	file.WriteString(cstr);
	file.Close();
	return true;
}


// 删除文件,DWORD 返回执行代码，0为成功
DWORD CLisameDlg::VrvDeleteFile(LPCWSTR lpSrc)
{
	WCHAR szFile[MAX_PATH] = {0};
	lstrcpy(szFile,lpSrc);
	SHFILEOPSTRUCT shFileOp = {0};
	shFileOp.fFlags = FOF_NOCONFIRMATION;
	shFileOp.pFrom = szFile; 
	shFileOp.pTo = NULL; // 一定NULL
	shFileOp.wFunc = FO_DELETE; 
	return SHFileOperation(&shFileOp);
	return 0;
}


// 结束指定进程
void CLisameDlg::KillProcess(CString pro)
{
	WCHAR szTarget[MAX_PATH];
	lstrcpy(szTarget, pro);//复制
	CharLowerBuff(szTarget, MAX_PATH);//转化为小写字母
	PROCESSENTRY32 pro32;
	HANDLE hProcessSnap  = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)//CreateToolhelp32Snapshot调用失败
	{
		//MessageBox(0,"系统程序出现异常！\nCreateToolhelp32Snapshot调用失败！","出错信息",MB_OK);
		CloseHandle(hProcessSnap);//清除snapshot对象
		return;
	}
	pro32.dwSize = sizeof(pro32);
	BOOL bProcess = Process32First(hProcessSnap , &pro32);//获得进程列表中的第一个进程
	while (bProcess)
	{
		CharLowerBuff(pro32.szExeFile, MAX_PATH);//转化为小写字母
		if (lstrcmp(szTarget,pro32.szExeFile)==0)//匹配字符串，判断是否存在指定进程
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE,FALSE,(DWORD)pro32.th32ProcessID);//获取进程句柄 //PROCESS_ALL_ACCESS
			TerminateProcess(hProcess, 0);//结束进程
			//ExitProcess(0);
		}
		bProcess=Process32Next(hProcessSnap , &pro32);//获得进程列表中的下一个进程
	}
	CloseHandle(hProcessSnap);//清除snapshot对象
}
