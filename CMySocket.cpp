#include "pch.h"
#include "CMySocket.h"
#include "MFCCharClient.h"
#include "MFCCharClientDlg.h"

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}

//回调 重写:当连接成功会执行相应代码
void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("####OnConnect");
	//此行代码记住
	CMFCCharClientDlg* dlg = (CMFCCharClientDlg*)AfxGetApp()->GetMainWnd();
	if (nErrorCode == 0) {
		CString csInfo = _T("与服务器连接成功");
		CString csMsg = _T("");
		CString csShow = dlg->CatShowString(csInfo, csMsg);
		dlg->m_list.AddString(csShow);
	}
	else {
		CString csInfo = _T("未能连接到服务器");
		CString csMsg = _T("");
		CString csShow = dlg->CatShowString(csInfo, csMsg);
		dlg->m_list.AddString(csShow);
	}
	CAsyncSocket::OnSend(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("####CMySocket OnReceive");
	//1接收数据到szRecvBuf
	//此行代码记住
	CMFCCharClientDlg* dlg = (CMFCCharClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);
	TRACE("####Server szRecvBuf = %s", szRecvBuf);

	//2显示Buf
	USES_CONVERSION;
	CString csRecvMsg = A2W(szRecvBuf);
	CString csInfo = _T("服务端：");
	CString csShow = dlg->CatShowString(csInfo, csRecvMsg);
	dlg->m_list.AddString(csShow);


	//选中自动回复
	if (((CButton*)dlg->GetDlgItem(IDC_AUTOSEND_RADIO))->GetCheck()) {
		//自动回复
		//1 读编辑框内容
		CString csAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSENDMSG_EDIT, csAutoSendMsg);

		//2 封包+组格式
		CString csName;
		dlg->GetDlgItemText(IDC_NAME_EDIT, csName);
		CString csMsg = _T("[自动回复]") + csAutoSendMsg;
		csMsg = csName + _T("：") + csMsg;
		
		
		//发送
		char* sendBuf = T2A(csMsg);
		dlg->m_client->Send(sendBuf, SEND_MAX_BUF, 0);
		
		CString csShow = dlg->CatShowString(_T(""), csMsg);
		dlg->m_list.AddString(csShow);
		dlg->m_list.UpdateData(FALSE);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}

void CMySocket::OnClose(int nErrorCode)
{
	TRACE("####Client OnClose");
	CMFCCharClientDlg* dlg = (CMFCCharClientDlg*)AfxGetApp()->GetMainWnd();
	dlg->m_client->ShutDown();
	dlg->m_client->Close();
	dlg->m_client = NULL;
	dlg->m_list.AddString(_T("服务器已断开连接"));
}
