// CheckInSysDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxext.h"


// CCheckInSysDlg �Ի���
class CCheckInSysDlg : public CDialog
{
// ����
public:
	CCheckInSysDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHECKINSYS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	_RecordsetPtr pRst;
	afx_msg void OnBnClickedButton3();
	CButton m_btn3;
	//CBitmapButton but1;
	CString m_COID;
};
