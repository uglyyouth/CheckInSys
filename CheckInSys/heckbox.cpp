// heckbox.cpp : 实现文件
//

#include "stdafx.h"
#include "CheckInSys.h"
#include "heckbox.h"


// checkbox 对话框

IMPLEMENT_DYNAMIC(checkbox, CDialog)

checkbox::checkbox(CWnd* pParent /*=NULL*/)
	: CDialog(checkbox::IDD, pParent)
	, m_class(_T(""))
	, m_people(_T(""))
	, csTemp(_T(""))
{

}

checkbox::~checkbox()
{
}

void checkbox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_LBString(pDX, IDC_LIST1, m_class);
	DDX_LBString(pDX, IDC_LIST2, m_people);
}


BEGIN_MESSAGE_MAP(checkbox, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &checkbox::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &checkbox::OnBnClickedButton1)
END_MESSAGE_MAP()


// checkbox 消息处理程序

BOOL checkbox::OnInitDialog()
{
	CDialog::OnInitDialog();


	// TODO:  在此添加额外的初始化
	CTime mt = CTime::GetCurrentTime();
int nowmonth=mt.GetMonth();
int nowyear=mt.GetYear();
	CString strTime;
	strTime.Format(_T("%d/%d"),nowyear,nowmonth);
    CString sql=_T("");
	CString sql2=_T("");
	CString someclass=_T("");
	CString CID=_T("");
	int showcount=0;
	int takeoff=0;
	sql.Format(_T("select * from class")); 
	pRst.CreateInstance("ADODB.Recordset");
	pRst2.CreateInstance("ADODB.Recordset");
	pRst3.CreateInstance("ADODB.Recordset");
	pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
	
	//CID.Format((_bstr_t)mmpRst->GetCollect("CID"));
	while(!pRst->rsEOF)
	{
		someclass.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("classname"));
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(someclass);
		pRst->MoveNext();
	}

	pRst->Close();
	((CListBox*)GetDlgItem(IDC_LIST1))->SetCurSel(0);

	UpdateData();
	AfxExtractSubString(csTemp,(LPCTSTR)m_class,0,'-'); 

	sql.Format(_T("select * from people where CID='%s'"),csTemp); 
	pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);

		while(!pRst->rsEOF)
		{
			showcount=0;
			takeoff=0;
			someclass.Format((_bstr_t)pRst->GetCollect("ID"));
			//sql2.Format(_T("select * from state where  PID='%s'and show=YES and sday like '%s'"),someclass,strTime);
			sql2.Format(_T("select * from state where PID='%s'and show=YES and sday like '%s/"),someclass,strTime);
			sql2+="%'";
			//sql2.Format(_T("select * from state where PID='%s'and show=YES"),someclass);
			pRst2->Open(_variant_t(sql2),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
				while(!pRst2->rsEOF)
				{
					showcount++;
				pRst2->MoveNext();
				
				}
			pRst2->Close();
			sql2.Format(_T("select * from state where PID='%s'and takeoff=YES and sday like '%s/"),someclass,strTime);
			sql2+="%'";
			pRst2->Open(_variant_t(sql2),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
				while(!pRst2->rsEOF)
				{
					takeoff++;
				pRst2->MoveNext();
				
				}
			pRst2->Close();
			someclass.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("name")+_T("   -   ")+_T("出勤")+_T("：")+(_bstr_t)showcount+_T("   -  ")+_T("请假")+_T("：")+(_bstr_t)takeoff);
			((CListBox*)GetDlgItem(IDC_LIST2))->AddString(someclass);
			pRst->MoveNext();

		}

	pRst->Close();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void checkbox::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
 
	AfxExtractSubString(csTemp,(LPCTSTR)m_class,0,'-'); 
		CTime mt = CTime::GetCurrentTime();
int nowmonth=mt.GetMonth();
int nowyear=mt.GetYear();
	CString strTime;
	strTime.Format(_T("%d/%d"),nowyear,nowmonth);

	CString sql=_T("");
	CString sql2=_T("");
	//sql.Format(_T("select * from course where ID='%s'"),m_COID); 
	////pRst.CreateInstance("ADODB.Recordset");
	//pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);

	//pRst->Close();
	int showcount=0;
	int takeoff=0;

	CString someclass=_T("");
	((CListBox*)GetDlgItem(IDC_LIST2))->ResetContent();


	sql.Format(_T("select * from people where CID='%s'"),csTemp); 
	//pRst.CreateInstance("ADODB.Recordset");
	pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);

		while(!pRst->rsEOF)
		{
			showcount=0;
			takeoff=0;
			someclass.Format((_bstr_t)pRst->GetCollect("ID"));
			//sql2.Format(_T("select * from state where  PID='%s'and show=YES and sday like '%s'"),someclass,strTime);
			sql2.Format(_T("select * from state where PID='%s'and show=YES and sday like '%s/"),someclass,strTime);
			sql2+="%'";
			//sql2.Format(_T("select * from state where PID='%s'and show=YES"),someclass);
			pRst2->Open(_variant_t(sql2),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
				while(!pRst2->rsEOF)
				{
					showcount++;
				pRst2->MoveNext();
				
				}
			pRst2->Close();
			sql2.Format(_T("select * from state where PID='%s'and takeoff=YES and sday like '%s/"),someclass,strTime);
			sql2+="%'";
			pRst2->Open(_variant_t(sql2),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
				while(!pRst2->rsEOF)
				{
					takeoff++;
				pRst2->MoveNext();
				
				}
			pRst2->Close();
			someclass.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("name")+_T("   -   ")+_T("出勤")+_T("：")+(_bstr_t)showcount+_T("   -  ")+_T("请假")+_T("：")+(_bstr_t)takeoff);
			((CListBox*)GetDlgItem(IDC_LIST2))->AddString(someclass);
			pRst->MoveNext();

		}

	pRst->Close();
}

void checkbox::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CTime mt = CTime::GetCurrentTime();
	int nowmonth=mt.GetMonth();
	int nowyear=mt.GetYear();
	CString strTime;
	strTime.Format(_T("%d/%d"),nowyear,nowmonth);



	CString sql=_T("");
	CString sql2=_T("");
	CString sql3=_T("");
	CString huan=_T("/n");
	int showcount=0;
	int takeoff=0;
	sql.Format(_T("select * from class")); 

	CString someclass=_T("");
	CString someclass2=_T("");
    CFile mFile;
	//LPTSTR p;

	pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
	while(!pRst->rsEOF)
	{
	someclass.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("classname"));

	

    mFile.Open(_T("check.txt"),CFile::modeReadWrite|CFile::modeCreate|CFile::modeReadWrite);
             mFile.SeekToEnd();              
			 mFile.Write("rn",strlen("rn"));//换行
           mFile.Write(someclass,strlen((_bstr_t)(someclass))); 
			mFile.Close();
		sql3.Format(_T("select * from people where CID='%s'"),(_bstr_t)pRst->GetCollect("ID")); 
		pRst3->Open(_variant_t(sql3),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);

		while(!pRst3->rsEOF)
		{
			showcount=0;
			takeoff=0;
			someclass2.Format((_bstr_t)pRst3->GetCollect("ID"));
			sql2.Format(_T("select * from state where PID='%s'and show=YES and sday like '%s/"),someclass2,strTime);
			sql2+="%'";
			pRst2->Open(_variant_t(sql2),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
				while(!pRst2->rsEOF)
				{
					showcount++;
				pRst2->MoveNext();
				
				}
			pRst2->Close();
			sql2.Format(_T("select * from state where PID='%s'and takeoff=YES and sday like '%s/"),someclass2,strTime);
			sql2+="%'";
			pRst2->Open(_variant_t(sql2),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
				while(!pRst2->rsEOF)
				{
					takeoff++;
				pRst2->MoveNext();
				
				}
			pRst2->Close();
			someclass2.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("name")+_T("   -   ")+_T("出勤")+_T("：")+(_bstr_t)showcount+_T("   -  ")+_T("请假")+_T("：")+(_bstr_t)takeoff);
		//fp= fopen("check.txt", "a+");
		//	p = someclass2.GetBuffer();


    mFile.Open(_T("check.txt"),CFile::modeReadWrite|CFile::modeCreate|CFile::modeReadWrite);
            mFile.SeekToEnd();              
			 mFile.Write("rn",strlen("rn"));//换行
           mFile.Write(someclass2,strlen((_bstr_t)(someclass2))); 
			mFile.Close();

			pRst3->MoveNext();

		}

	pRst3->Close();

		pRst->MoveNext();
	}

	pRst->Close();


}
