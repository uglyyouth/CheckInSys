#pragma once


// checkbox �Ի���

class checkbox : public CDialog
{
	DECLARE_DYNAMIC(checkbox)

public:
	checkbox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~checkbox();

// �Ի�������
	enum { IDD = IDD_checkbox };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
		_RecordsetPtr pRst;
		_RecordsetPtr pRst2;
		_RecordsetPtr pRst3;
		virtual BOOL OnInitDialog();
		CString m_class;
		CString m_people;
		afx_msg void OnLbnSelchangeList1();
		CString csTemp;
		afx_msg void OnBnClickedButton1();
};
