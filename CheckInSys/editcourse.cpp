// editcourse.cpp : 实现文件
//

#include "stdafx.h"
#include "CheckInSys.h"
#include "editcourse.h"


// editcourse 对话框

IMPLEMENT_DYNAMIC(editcourse, CDialog)

editcourse::editcourse(CWnd* pParent /*=NULL*/)
	: CDialog(editcourse::IDD, pParent)
	, m_classname(_T(""))
	, classnumber(_T(""))
	, coursename(_T(""))
	, m_course(_T(""))
{

}

editcourse::~editcourse()
{
}

void editcourse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, m_classname);
	DDX_Text(pDX, IDC_EDIT2, classnumber);
	DDX_Text(pDX, IDC_EDIT1, coursename);
	DDX_LBString(pDX, IDC_LIST1, m_course);
}


BEGIN_MESSAGE_MAP(editcourse, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &editcourse::OnLbnSelchangeList1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &editcourse::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// editcourse 消息处理程序

BOOL editcourse::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CListBox*)GetDlgItem(IDC_COMBO1))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("星期一"));
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("星期二"));
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("星期三"));
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("星期四"));
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("星期五"));
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("星期六"));
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("星期日"));
	//((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("Tuseday");
	//((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("Friday");

		//pRst.CreateInstance("ADODB.Recordset");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void editcourse::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();


	//CString sql=_T("");
	//CString kecheng=_T("");
	//((CListBox*)GetDlgItem(IDC_LIST2))->ResetContent();




	//sql.Format(_T("select * from people where CID='%s'"),csTemp); 
	////pRst.CreateInstance("ADODB.Recordset");
	//pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);

	//	while(!pRst->rsEOF)
	//	{
	//		kecheng.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("name"));
	//		((CListBox*)GetDlgItem(IDC_LIST2))->AddString(kecheng);
	//		pRst->MoveNext();
	//	}

	//pRst->Close();

}

void editcourse::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	int weekday=0;

	
	if (m_classname==_T("星期一"))
	{
		weekday=1;
	}
	else if(m_classname==_T("星期二"))
	{
		weekday=2;
	}else if(m_classname==_T("星期三"))
	{
		weekday=3;
	}else if(m_classname==_T("星期四"))
	{
		weekday=4;
	}else if(m_classname==_T("星期五"))
	{
	weekday=5;
	}else
	{
	weekday=1;}




	CString sql=_T("");
	CString kecheng=_T("");
	((CListBox*)GetDlgItem(IDC_LIST1))->ResetContent();




	sql.Format(_T("select * from course where weektime=%d"),weekday) ;
	pRst.CreateInstance("ADODB.Recordset");
	
	pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);

		while(!pRst->rsEOF)
		{
			kecheng.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("coursename")+_T("--------")+(_bstr_t)pRst->GetCollect("daytime"));
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(kecheng);
			pRst->MoveNext();
		}

	pRst->Close();
}
