#pragma once


// editcourse �Ի���

class editcourse : public CDialog
{
	DECLARE_DYNAMIC(editcourse)

public:
	editcourse(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~editcourse();

// �Ի�������
	enum { IDD = IDD_course };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_classname;
	CString classnumber;
	CString coursename;
	CString m_course;
	_RecordsetPtr pRst;
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnCbnSelchangeCombo1();
};
