#pragma once
#include <afxsock.h>
/*
    ��дClient��socket��
*/
class CMySocket :
    public CAsyncSocket
{
public:
    CMySocket();
    virtual ~CMySocket();
    virtual void OnConnect(int nErrorCode);
    virtual void OnReceive(int nErrorCode);
    virtual void OnClose(int nErrorCode);
};

