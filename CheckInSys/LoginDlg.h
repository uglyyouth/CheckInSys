#pragma once


// LoginDlg 对话框

class LoginDlg : public CDialog
{
	DECLARE_DYNAMIC(LoginDlg)

public:
	LoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LoginDlg();

// 对话框数据
	enum { IDD = IDD_LOGIN_D };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	CString m_user;
	CString m_password;
public:
	virtual BOOL OnInitDialog();
	_RecordsetPtr pRst;
	virtual BOOL DestroyWindow();
};
