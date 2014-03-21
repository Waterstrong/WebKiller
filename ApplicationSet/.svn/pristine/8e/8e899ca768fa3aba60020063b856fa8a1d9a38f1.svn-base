/*******************************************

	MFTrafficButton

	Version:	1.0
	Date:		31.10.2001
	Author:		Michael Fatzi
	Mail:		Michael_Fatzi@hotmail.com
	Copyright 1996-1997, Keith Rule

	You may freely use or modify this code provided this
	Copyright is included in all derived versions.
	
	History: 10.2001 Startup

	Handy little button control to display current 
	nettraffic as graph in a button.

********************************************/


#include "stdafx.h"
#include "NetTrafficButton.h"
#include "NetTrafficButtonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
#include "winnet.h"

#pragma comment(lib, "winnet.lib")
/////////////////////////////////////////////////////////////////////////////
// CNetTrafficButtonApp

CNetTrafficButtonApp theApp;

BEGIN_MESSAGE_MAP(CNetTrafficButtonApp, CWinApp)
	//{{AFX_MSG_MAP(CNetTrafficButtonApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetTrafficButtonApp Construction

CNetTrafficButtonApp::CNetTrafficButtonApp()
{
}

BOOL CNetTrafficButtonApp::InitInstance()
{
	int nArgumentCount = __argc;
	BOOL bNormalRunFlag = ( nArgumentCount <= 1);

	/////////////////////////////////////////////////////////////////
	/*只运行一个实例*/
	CString strMutexName = bNormalRunFlag ? "NetTraffic$#$ciffarTteN" : "NetTraffic#$#$#ciffarTteN";
	CreateMutex(NULL,TRUE, strMutexName); 
    if(ERROR_ALREADY_EXISTS == GetLastError())
	{
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////

#ifdef _AFXDLL
	Enable3dControls();			
#else
	Enable3dControlsStatic();	
#endif

	if(!NetInit())
	{
		return FALSE;
	}

	this->SetDialogBkColor(RGB(170,175,195),RGB(0,0,0));

	if(bNormalRunFlag)
	{
		CNetTrafficButtonDlg dlg;
		m_pMainWnd = &dlg;
		int nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
		}

		return FALSE;
	}
	else
	{
		BOOL bResult = m_wndNetTraffic.CreateEx(0, AfxRegisterWndClass(CS_NOCLOSE), 
												_T("NetTrafficWnd"), 
												WS_POPUP|WS_DISABLED, 
												0, 0, 0, 0,
												NULL, NULL);
		if( !bResult )
		{
			return FALSE;
		}

		m_pMainWnd = &m_wndNetTraffic;

		return TRUE;
	}

	return TRUE;
}

int CNetTrafficButtonApp::ExitInstance() 
{
	HWND hWnd = m_wndNetTraffic.m_hWnd;
	if( NULL != hWnd && ::IsWindow(hWnd))
	{
		m_wndNetTraffic.DestroyWindow();
	}

	NetUnint();
	
	return CWinApp::ExitInstance();
}
