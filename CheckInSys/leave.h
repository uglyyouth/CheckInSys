#pragma once


// leave �Ի���

class leave : public CDialog
{
	DECLARE_DYNAMIC(leave)

public:
	leave(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~leave();

// �Ի�������
	enum { IDD = IDD_leave };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
