
// LisameDlg.h : ͷ�ļ�
//

#pragma once
#include "endecryption.h"
#include "TickClock.h"

// CLisameDlg �Ի���
class CLisameDlg : public CDialogEx
{
// ����
public:
	CLisameDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LISAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonQuery();
	afx_msg void OnBnClickedButtonChoose();
	CString m_keypath;
	afx_msg void OnBnClickedButtonLisa();
protected:
	// ��һ���ַ����ֽ��ŵ�һ��CStringArray��
	void ExtractString(CStringArray& arr, const CString strSrc, const CString sep = L"\r\n" );
	// ����ת��Ϊʱ����
	int Type2Clock(CString type);
	// д�뵽Tick�ļ���
	bool WriteKey2TickFile(CString strKeyTime, int clockSec);
	// ����
	bool Decrypt(string& strKey);
	// ��֤��Ч��
	bool VerifyValidKey(CStringArray& splitKey);
	// ��֤Ψһ��
	bool VerifyUniqueKey(CString strKeyTime, CString strNowDate);
	// ����֤��Ϣд���ļ�, appendΪ���ʾ׷��
	bool WriteVerifi2File(CString cstr, bool append = false);
	// ɾ���ļ�,DWORD ����ִ�д��룬0Ϊ�ɹ�
	DWORD VrvDeleteFile(LPCWSTR lpSrc);
	// ����ָ������
	bool KillProcess(CString pro);
public:
	CButton m_btnChoose;
};
