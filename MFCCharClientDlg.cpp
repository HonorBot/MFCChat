
// MFCCharClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCCharClient.h"
#include "MFCCharClientDlg.h"
#include "afxdialogex.h"
#include<atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCCharClientDlg 对话框



CMFCCharClientDlg::CMFCCharClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHARCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCharClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_SENDMSG_EDIT, m_input);
}

BEGIN_MESSAGE_MAP(CMFCCharClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CMFCCharClientDlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_DISCONNECT_BTN, &CMFCCharClientDlg::OnBnClickedDisconnectBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCCharClientDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_SAVENAME_BUTTON, &CMFCCharClientDlg::OnBnClickedSavenameButton)
	ON_BN_CLICKED(IDC_AUTOSEND_RADIO, &CMFCCharClientDlg::OnBnClickedAutosendRadio)
	ON_BN_CLICKED(IDC_CLEARMSG_BTN, &CMFCCharClientDlg::OnBnClickedClearmsgBtn)
END_MESSAGE_MAP()


// CMFCCharClientDlg 消息处理程序
//初始化对话框时，需要执行的代码
BOOL CMFCCharClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("6000"));
	GetDlgItem(IDC_IPADDRESS1)->SetWindowText(_T("127.0.0.1"));

	//从配置文件里读取昵称
	SetDlgItemTextW(IDC_NAME_EDIT, GetName());
	UpdateData(FALSE);
	

	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCCharClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCCharClientDlg::OnPaint()
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
HCURSOR CMFCCharClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//拼接字符串	时间+csInfo+csMsg
CString CMFCCharClientDlg::CatShowString(CString csInfo, CString csMsg) {
	CString csTime = CTime::GetCurrentTime().Format("%X ");
	CString csShow;
	csShow = csTime + csShow ;
	csShow += csInfo;
	csShow += csMsg;
	return csShow;
}

//从配置文件里读取昵称
WCHAR* CMFCCharClientDlg::GetName()
{
	
	WCHAR wszName[MAX_PATH] = { 0 };
	WCHAR strPath[MAX_PATH] = { 0 };
	//获取当前路径
	GetCurrentDirectoryW(MAX_PATH, strPath);
	CString csFilePath;
	csFilePath.Format(L"%ls//Test.ini", strPath);
	DWORD dwNum = GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"), NULL,
		wszName, MAX_PATH, csFilePath);
	if (dwNum <= 0)  {
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), L"客户端", csFilePath);
		wcscpy_s(wszName, L"客户端");
	}
	return wszName;
}


void CMFCCharClientDlg::OnBnClickedConnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csPort, csIP;
	//从控件里面获取内容,两种方法
	//GetDlgItemTextW(IDC_PORT_EDIT, csPort);
	//GetDlgItemTextW(IDC_IPADDRESS1, csIp);
	//获取端口和ip
	GetDlgItem(IDC_PORT_EDIT)->GetWindowTextW(csPort);
	GetDlgItem(IDC_IPADDRESS1)->GetWindowTextW(csIP);

	//CString转char*
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(csPort);
	LPCSTR szIP = (LPCSTR)T2A(csIP);
	
	TRACE("%s,%s",szPort, szIP);

	int iPort = _ttoi(csPort);
	//创建一个socket对象
	m_client = new CMySocket();
	//创建套接字	容错
	if (!m_client->Create()) {
		TRACE("m_client Create error %d", GetLastError());
		return;
	}
	//连接
	if (int i = m_client->Connect(csIP, iPort) != SOCKET_ERROR) {
		TRACE("m_client Connect error %d", i);
	}
}

//与服务器断开连接
void CMFCCharClientDlg::OnBnClickedDisconnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_client->ShutDown();
	m_client->Close();
	m_client = NULL;
	m_list.AddString(CatShowString(_T(""),_T("与服务器断开连接")));
}


//发送消息
void CMFCCharClientDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_client) {
		MessageBox(_T("没有连接的服务器"));
		return;
	}
	//1获取编辑框内容
	CString csTmpMsg;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowTextW(csTmpMsg);
	if (csTmpMsg == "") {
		MessageBox(_T("请输入要发送的信息"));
		return;
	}

	//获取昵称
	
	CString csName;
	GetDlgItem(IDC_NAME_EDIT)->GetWindowTextW(csName);
	csTmpMsg = csName + _T("：") + csTmpMsg;
	USES_CONVERSION;
	char* szSendBuf = T2A(csTmpMsg);

	//2发送给服务端
	if (m_client->Send(szSendBuf, SEND_MAX_BUF, 0) != SOCKET_ERROR) {
		//3显示到列表框
		CString csShow;

		//拼接字符串
		csShow = CatShowString(_T(""), csTmpMsg);
		m_list.AddString(csShow);
		//m_list.AddString(_T("     ")+csTmpMsg);
	}
	else {
		m_list.AddString(_T("消息发送失败"));
	}
	UpdateData(FALSE);

	//清空编辑框
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowTextW(_T(""));
	
}

//保存昵称
void CMFCCharClientDlg::OnBnClickedSavenameButton()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取文本框内容
	CString csName;
	GetDlgItemText(IDC_NAME_EDIT, csName);
	if (csName.GetLength() <= 0) {
		MessageBox(L"昵称不能为空");
		SetDlgItemText(IDC_NAME_EDIT, GetName());
		return;
	}
	if (IDOK == AfxMessageBox(_T("是否修改昵称？"), MB_OKCANCEL)) {
		
		WCHAR strPath[MAX_PATH] = { 0 };
		//获取当前路径
		GetCurrentDirectoryW(MAX_PATH, strPath);
		TRACE("#####strPath = %ls", strPath);
		
		CString csFilePath;
		csFilePath.Format(L"%ls//Test.ini", strPath);

		//写入配置文件
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), csName, csFilePath);
	}
	
}


void CMFCCharClientDlg::OnBnClickedAutosendRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_AUTOSEND_RADIO))->GetCheck()) {
		((CButton*)GetDlgItem(IDC_AUTOSEND_RADIO))->SetCheck(FALSE);
	}
	else {
		((CButton*)GetDlgItem(IDC_AUTOSEND_RADIO))->SetCheck(TRUE);
	}
}

//清屏
void CMFCCharClientDlg::OnBnClickedClearmsgBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}
