
// LisameDlg.h : 头文件
//

#pragma once
#include "endecryption.h"
#include "TickClock.h"

// CLisameDlg 对话框
class CLisameDlg : public CDialogEx
{
// 构造
public:
	CLisameDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LISAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	// 将一个字符串分解后放到一个CStringArray中
	void ExtractString(CStringArray& arr, const CString strSrc, const CString sep = L"\r\n" );
	// 类型转化为时间秒
	int Type2Clock(CString type);
	// 写入到Tick文件中
	bool WriteKey2TickFile(CString strKeyTime, int clockSec);
	// 译码
	bool Decrypt(string& strKey);
	// 验证有效性
	bool VerifyValidKey(CStringArray& splitKey);
	// 验证唯一性
	bool VerifyUniqueKey(CString strKeyTime, CString strNowDate);
	// 将验证信息写入文件, append为真表示追加
	bool WriteVerifi2File(CString cstr, bool append = false);
	// 删除文件,DWORD 返回执行代码，0为成功
	DWORD VrvDeleteFile(LPCWSTR lpSrc);
	// 结束指定进程
	bool KillProcess(CString pro);
public:
	CButton m_btnChoose;
};
