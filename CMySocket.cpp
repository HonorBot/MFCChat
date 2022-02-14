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

//�ص� ��д:�����ӳɹ���ִ����Ӧ����
void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("####OnConnect");
	//���д����ס
	CMFCCharClientDlg* dlg = (CMFCCharClientDlg*)AfxGetApp()->GetMainWnd();
	if (nErrorCode == 0) {
		CString csInfo = _T("����������ӳɹ�");
		CString csMsg = _T("");
		CString csShow = dlg->CatShowString(csInfo, csMsg);
		dlg->m_list.AddString(csShow);
	}
	else {
		CString csInfo = _T("δ�����ӵ�������");
		CString csMsg = _T("");
		CString csShow = dlg->CatShowString(csInfo, csMsg);
		dlg->m_list.AddString(csShow);
	}
	CAsyncSocket::OnSend(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("####CMySocket OnReceive");
	//1�������ݵ�szRecvBuf
	//���д����ס
	CMFCCharClientDlg* dlg = (CMFCCharClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);
	TRACE("####Server szRecvBuf = %s", szRecvBuf);

	//2��ʾBuf
	USES_CONVERSION;
	CString csRecvMsg = A2W(szRecvBuf);
	CString csInfo = _T("����ˣ�");
	CString csShow = dlg->CatShowString(csInfo, csRecvMsg);
	dlg->m_list.AddString(csShow);


	//ѡ���Զ��ظ�
	if (((CButton*)dlg->GetDlgItem(IDC_AUTOSEND_RADIO))->GetCheck()) {
		//�Զ��ظ�
		//1 ���༭������
		CString csAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSENDMSG_EDIT, csAutoSendMsg);

		//2 ���+���ʽ
		CString csName;
		dlg->GetDlgItemText(IDC_NAME_EDIT, csName);
		CString csMsg = _T("[�Զ��ظ�]") + csAutoSendMsg;
		csMsg = csName + _T("��") + csMsg;
		
		
		//����
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
	dlg->m_list.AddString(_T("�������ѶϿ�����"));
}
