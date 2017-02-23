#pragma once


// editcourse 对话框

class editcourse : public CDialog
{
	DECLARE_DYNAMIC(editcourse)

public:
	editcourse(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~editcourse();

// 对话框数据
	enum { IDD = IDD_course };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
