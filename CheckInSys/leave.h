#pragma once


// leave 对话框

class leave : public CDialog
{
	DECLARE_DYNAMIC(leave)

public:
	leave(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~leave();

// 对话框数据
	enum { IDD = IDD_leave };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
