#pragma once
#include "afxwin.h"


// password 对话框

class password : public CDialog
{
	DECLARE_DYNAMIC(password)

public:
	password(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~password();

// 对话框数据
	enum { IDD = IDD_CHANGEPASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_passwordo;
	CString m_passwordnn;
	CString m_passwordn;
	afx_msg void OnBnClickedButton1();
	_RecordsetPtr pRst;
	virtual BOOL OnInitDialog();
};
