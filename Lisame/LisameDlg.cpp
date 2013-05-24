
// LisameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Lisame.h"
#include "LisameDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CLisameDlg �Ի���




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


// CLisameDlg ��Ϣ�������

BOOL CLisameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLisameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLisameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLisameDlg::OnBnClickedButtonQuery()
{
	TickClock tickClock;
	if (!tickClock.ReadFromFile())
	{
		MessageBox(L"��ʱ�����ļ���ȡ/����ʧ�ܣ�", L"��ʾ", MB_ICONSTOP|MB_OK);
		return;
	}
	CString tip;
	CTime dtNow = CTime::GetCurrentTime();
	if (tickClock.Year() != dtNow.GetYear() || 
		tickClock.Month() != dtNow.GetMonth() ||
		tickClock.Day() != dtNow.GetDay())
	{
		tip.Format(L"��������ܻ�δ���й�������ʣ��ʱ�������ο���\n\n�ף���������ʣ��ʱ���Լ���� %d ���ӡ�", tickClock.ClockSec()/60 );
		MessageBox(tip, L"��ʾ", MB_ICONWARNING|MB_OK);
	}
	else
	{
		tip.Format(L"�ף���������ʣ��ʱ���Լ���� %d ���ӡ�", tickClock.ClockSec()/60 );
		MessageBox(tip, L"��ʾ", MB_ICONINFORMATION|MB_OK);
	}
	
}


void CLisameDlg::OnBnClickedButtonChoose()
{
	CFileDialog fileDialog(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL, 
		NULL,
		OFN_FILEMUSTEXIST, //OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		L"��֤Կ�ļ�(*.gen)|*.gen||",
		NULL);
	if(fileDialog.DoModal()==IDOK)
	{
		m_keypath = fileDialog.GetPathName(); //�ļ�����������FilePathName��
		UpdateData(FALSE);
	}
}


void CLisameDlg::OnBnClickedButtonLisa()
{
	UpdateData(TRUE);
	string strKey;
	if (!Decrypt(strKey)) // ����
	{
		return;
	}
	CString cstr(strKey.c_str());
	CStringArray splitKey; // yyhua#19:54:33#2013-5-23#ONEHOUR#19:54:33
	ExtractString(splitKey, cstr, L"#"); // �ָ��ַ���
	if (!VerifyValidKey(splitKey)) // ��֤��Ч��
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
		tip.Format(L"����ʱ�����óɹ���\n�ף����������� %d ���ӵ�����ʱ����ף��������죡", clockSec / 60 );
		MessageBox(tip, L"��ʾ", MB_ICONINFORMATION|MB_OK);
	}
}

// ��һ���ַ����ֽ��ŵ�һ��CStringArray��
void CLisameDlg::ExtractString(CStringArray& arr, const CString strSrc, const CString sep)
{
	// Ԥ����: �ɸ�����Ҫ�����Ƿ���ҪTrim���Լ���Trim���ո�/���Ƿָ���/��������
	CString str(strSrc);
	str.TrimLeft(); 
	str.TrimRight();

	if(str.IsEmpty())
		return;

	// ��ʼ�ֽ�
	int pos = str.Find(sep);
	while (pos != -1)
	{
		//if(!str.Left(pos).IsEmpty()) // ���б�ҪҲ���ڴ�Trim�����ж��Ƿ�Ϊ�գ�Ϊ��������
		arr.Add(str.Left(pos));

		str = str.Mid(pos + sep.GetLength());
		pos = str.Find(sep);
	}
	arr.Add(str); // think
}


// ����ת��Ϊʱ����
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
		MessageBox(L"��֤Կ������֤ʧ�ܣ�", L"��ʾ", MB_ICONSTOP|MB_OK);
	}
	return clockSec;
}


// д�뵽Tick�ļ���
bool CLisameDlg::WriteKey2TickFile(CString strKeyTime, int clockSec)
{
	TickClock tickClock;
	if (!tickClock.ReadFromFile())
	{
		MessageBox(L"��ʱ�����ļ���ȡ/����ʧ�ܣ�", L"��ʾ", MB_ICONSTOP|MB_OK);
		return false;
	}
	CTime dtTick(tickClock.Year(), tickClock.Month(), tickClock.Day(), tickClock.Hour(), tickClock.Minute(), tickClock.Second());
	CTime dtNow = CTime::GetCurrentTime();
	CString strNowDate = dtNow.Format("%Y-%m-%d");
	CString strTickDate = dtTick.Format("%Y-%m-%d");
	if (strTickDate != strNowDate)
	{
		MessageBox(L"������֤ʧ�ܣ�����������ԭ��\n1.�����컹δ���й�����\n2.ϵͳ���ڱ��Ƿ�����", L"��ʾ", MB_ICONSTOP|MB_OK);
		return false;
	}
	if (!VerifyUniqueKey( strKeyTime, strNowDate ) )
	{
		return false;
	}
	
	// ��������
	CString newfile(NEW_FILE);
	if (!KillProcess(newfile))
	{
		MessageBox(L"�����������ʧ�ܣ�", L"��ʾ", MB_ICONWARNING|MB_OK);
		return false;
	}
	

	// ������������ʱ��
	tickClock.Year() = dtNow.GetYear();
	tickClock.Month() = dtNow.GetMonth();
	tickClock.Day() = dtNow.GetDay();
	tickClock.Hour() = dtNow.GetHour();
	tickClock.Minute() = dtNow.GetMinute();
	tickClock.Second() = dtNow.GetSecond();
	tickClock.ClockSec() = clockSec;
	if (!tickClock.WriteToFile()) // д���ļ�����
	{
		return false;
	}

	// ����������
	CString sysPath(SYSTEM_PATH);// �õ�ϵͳĿ¼��·��
	sysPath += "\\";
	sysPath += NEW_FILE; //�γ�Ҫ���Ƶ���ȫ·��
	ShellExecute(NULL,L"open", sysPath, NULL, NULL, SW_SHOWNORMAL);

	// ɾ����֤Կ�ļ�
	VrvDeleteFile(m_keypath);
	m_keypath = "";
	UpdateData(FALSE);
	return true;
}

// ����
bool CLisameDlg::Decrypt(string& strKey)
{
	if (m_keypath.Trim() == "")
	{
		MessageBox(L"��ѡ����֤Կ�ļ���", L"��ʾ", MB_ICONWARNING|MB_OK);
		m_btnChoose.SetFocus();
		return false;
	}
	ifstream input;
	input.open(m_keypath.Trim(), ios::in);
	if (!input)
	{
		MessageBox(L"��ȡ��֤Կ�ļ�ʧ�ܣ��Ҳ����ļ���", L"��ʾ", MB_ICONWARNING|MB_OK);
		return false;
	}
	getline(input, strKey);
	input.close();
	EnDecryption ende;
	ende.SetCryptograph(strKey);
	strKey = ende.GetRealPwd(); // ����
	return true;
}


// ��֤��Ч��
bool CLisameDlg::VerifyValidKey(CStringArray& splitKey)
{
	if (splitKey.GetCount() != 5)
	{
		MessageBox(L"��֤Կ�ļ����ݱ��ƻ�������ʧ�ܣ�", L"��ʾ", MB_ICONSTOP|MB_OK);
		return false;
	}
	if (splitKey[1] != splitKey[4])
	{
		MessageBox(L"��֤Կ�ļ����ݱ��ƻ�������ʧ�ܣ�", L"��ʾ", MB_ICONSTOP|MB_OK);
		return false;
	}
	if (splitKey[0] != IDENTITY)
	{
		MessageBox(L"��֤Կ�����֤ʧ�ܣ�", L"��ʾ", MB_ICONSTOP|MB_OK);
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
		MessageBox(L"������֤ʧ�ܣ���֤Կ�ѹ��ڻ�δ��Ч��", L"��ʾ", MB_ICONSTOP|MB_OK);
		return false;
	}
	return true;
}


// ��֤Ψһ��
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
		else if (splitVerifi[0].SpanExcluding(L" ") != strNowDate) // �ж���֤Կ�Ƿ��챻ʹ���ˣ����˵�����Զ��������Ϊ������
		{ //splitVerifi[0].Left(splitVerifi[0].Find(L' '))
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
					MessageBox(L"����֤Կ��ʹ�ã������ظ���֤��", L"��ʾ", MB_ICONSTOP|MB_OK);
					return false;
				}
			}
			WriteVerifi2File(L"#" + strKeyTime, true);
		}
	}
	return true;
}


// ����֤��Ϣд���ļ�, append==true��ʾ׷��
bool CLisameDlg::WriteVerifi2File(CString cstr, bool append)
{
	CStdioFile file;
	CString path(VERIFI_PATH);
	file.Open(path, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
	if (!file.m_pStream)
	{
		MessageBox(L"��֤Կ�ļ�д��ʱ����", L"��ʾ", MB_ICONSTOP|MB_OK);
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


// ɾ���ļ�,DWORD ����ִ�д��룬0Ϊ�ɹ�
DWORD CLisameDlg::VrvDeleteFile(LPCWSTR lpSrc)
{
	WCHAR szFile[MAX_PATH] = {0};
	lstrcpy(szFile,lpSrc);
	SHFILEOPSTRUCT shFileOp = {0};
	shFileOp.fFlags = FOF_NOCONFIRMATION;
	shFileOp.pFrom = szFile; 
	shFileOp.pTo = NULL; // һ��NULL
	shFileOp.wFunc = FO_DELETE; 
	return SHFileOperation(&shFileOp);
	return 0;
}


// ����ָ������
bool CLisameDlg::KillProcess(CString pro)
{
	WCHAR szTarget[MAX_PATH];
	lstrcpy(szTarget, pro);//����
	CharLowerBuff(szTarget, MAX_PATH);//ת��ΪСд��ĸ
	PROCESSENTRY32 pro32;
	HANDLE hProcessSnap  = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)//CreateToolhelp32Snapshot����ʧ��
	{
		//MessageBox(0,"ϵͳ��������쳣��\nCreateToolhelp32Snapshot����ʧ�ܣ�","������Ϣ",MB_OK);
		CloseHandle(hProcessSnap);//���snapshot����
		return false;
	}
	pro32.dwSize = sizeof(pro32);
	BOOL bProcess = Process32First(hProcessSnap , &pro32);//��ý����б��еĵ�һ������
	while (bProcess)
	{
		CharLowerBuff(pro32.szExeFile, MAX_PATH);//ת��ΪСд��ĸ
		if (lstrcmp(szTarget,pro32.szExeFile)==0)//ƥ���ַ������ж��Ƿ����ָ������
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE,FALSE,(DWORD)pro32.th32ProcessID);//��ȡ���̾�� //PROCESS_ALL_ACCESS
			TerminateProcess(hProcess, 0);//��������
			//ExitProcess(0);
		}
		bProcess=Process32Next(hProcessSnap , &pro32);//��ý����б��е���һ������
	}
	CloseHandle(hProcessSnap);//���snapshot����
	return true;
}
