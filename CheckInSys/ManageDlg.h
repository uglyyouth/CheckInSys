#pragma once


// ManageDlg 对话框

	class ManageDlg : public CDialog
{
	DECLARE_DYNAMIC(ManageDlg)

public:
	ManageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ManageDlg();

// 对话框数据
	enum { IDD = IDD_MANAGE_D };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnVideocam();
	afx_msg void OnChangepass();
	
	virtual BOOL OnInitDialog();
protected:
public:
	afx_msg void OnLbnSelchangeList1();
	CString m_course;
	afx_msg void OnMcnSelchangeMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult);
	COleDateTime m_daysel;
	_RecordsetPtr pRst;

	afx_msg void Onleave();
	afx_msg void Oncourse();
	afx_msg void Oncheck();
	};
