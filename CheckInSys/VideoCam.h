#pragma once


// VideoCam �Ի���

class VideoCam : public CDialog
{
	DECLARE_DYNAMIC(VideoCam)

public:
	VideoCam(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~VideoCam();

// �Ի�������
	enum { IDD = IDD_VIDEOCAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButton2();
	bool pics1;
	bool pics2;
	bool pics3;
	afx_msg void OnBnClickedButton3();
	bool pics4;
	bool pics5;
	bool pics6;
	CString m_name;
	virtual BOOL OnInitDialog();
	CString m_classname;
	_RecordsetPtr pRst;
};
