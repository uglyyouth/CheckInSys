#pragma once
#include "afxwin.h"


// password �Ի���

class password : public CDialog
{
	DECLARE_DYNAMIC(password)

public:
	password(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~password();

// �Ի�������
	enum { IDD = IDD_CHANGEPASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_passwordo;
	CString m_passwordnn;
	CString m_passwordn;
	afx_msg void OnBnClickedButton1();
	_RecordsetPtr pRst;
	virtual BOOL OnInitDialog();
};
