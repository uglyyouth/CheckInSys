#pragma once


// LoginDlg �Ի���

class LoginDlg : public CDialog
{
	DECLARE_DYNAMIC(LoginDlg)

public:
	LoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LoginDlg();

// �Ի�������
	enum { IDD = IDD_LOGIN_D };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
