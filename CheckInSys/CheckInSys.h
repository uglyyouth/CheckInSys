// CheckInSys.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCheckInSysApp:
// �йش����ʵ�֣������ CheckInSys.cpp
//

class CCheckInSysApp : public CWinApp
{
public:
	CCheckInSysApp();
	_ConnectionPtr pConn;
	CString managename;

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

};

extern CCheckInSysApp theApp;