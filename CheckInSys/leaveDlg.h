#pragma once


// leaveDlg �Ի���

class leaveDlg : public CDialog
{
	DECLARE_DYNAMIC(leaveDlg)

public:
	leaveDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~leaveDlg();

// �Ի�������
	enum { IDD = IDD_leave };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
		_RecordsetPtr pRst;

		afx_msg void OnLbnSelchangeList1();

		CString m_course;
		COleDateTime m_daysel;
		afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
		CString m_people;
		afx_msg void OnBnClickedButton3();
		CString csTemp;
		CString m_COID;
};
