
// MFCCharClientDlg.h: 头文件
//

#pragma once

#include "CMySocket.h"

// CMFCCharClientDlg 对话框
class CMFCCharClientDlg : public CDialogEx
{
// 构造
public:
	CMFCCharClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHARCLIENT_DIALOG };
#endif

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
	
	afx_msg void OnBnClickedConnectBtn();
	afx_msg void OnBnClickedDisconnectBtn();

	CString CatShowString(CString csInfo, CString strMsg);
	WCHAR* GetName();
	

	CMySocket* m_client;
	CListBox m_list;
	CEdit m_input;
	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnBnClickedSavenameButton();
	afx_msg void OnBnClickedAutosendRadio();
	afx_msg void OnBnClickedClearmsgBtn();
};
