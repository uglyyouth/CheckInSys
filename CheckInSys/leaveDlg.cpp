// leaveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CheckInSys.h"
#include "leaveDlg.h"



extern CCheckInSysApp theApp;
// leaveDlg 对话框

IMPLEMENT_DYNAMIC(leaveDlg, CDialog)

leaveDlg::leaveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(leaveDlg::IDD, pParent)
	, m_course(_T(""))
	, m_daysel(COleDateTime::GetCurrentTime())
	, m_people(_T(""))
	, csTemp(_T(""))
	, m_COID(_T(""))
{

}

leaveDlg::~leaveDlg()
{
}

void leaveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_LBString(pDX, IDC_LIST1, m_course);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_daysel);
	DDX_LBString(pDX, IDC_LIST2, m_people);
}


BEGIN_MESSAGE_MAP(leaveDlg, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &leaveDlg::OnLbnSelchangeList1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &leaveDlg::OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_BUTTON3, &leaveDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// leaveDlg 消息处理程序

BOOL leaveDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CTime mt = CTime::GetCurrentTime();
	int mw=mt.GetDayOfWeek()-1; 

	
	if ((mw==0)|(mw==6))
	{
		mw=1;
	}


    //try                    
    //{      
    //   mmpConn->ConnectionString=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=CheckinSys.mdb");
	   //mmpConn->Open("","","",adConnectUnspecified);
    //}   
    //catch(_com_error e)   
    //{   
    //    MessageBox(_T("数据库连接失败，确认数据库是否在当前路径下!"));   
    //    MessageBox( e.Description() );   
    //    MessageBox( e.ErrorMessage() );    
    //    return FALSE;   
    //}  

		CString sql=_T("");
		CString kecheng=_T("");
		CString CID=_T("");
	
		sql.Format(_T("select * from course where weektime=%d"),mw); 
		pRst.CreateInstance("ADODB.Recordset");
		pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
		//CID.Format((_bstr_t)mmpRst->GetCollect("CID"));
		while(!pRst->rsEOF)
		{
			kecheng.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("CID")+_T("-")+(_bstr_t)pRst->GetCollect("coursename"));
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(kecheng);
			pRst->MoveNext();
		}

	pRst->Close();
	((CListBox*)GetDlgItem(IDC_LIST1))->SetCurSel(0);

	UpdateData();
	CString csTemp;
	AfxExtractSubString(csTemp,(LPCTSTR)m_course,0,'-'); 

	sql.Format(_T("select * from people where CID='%s'"),csTemp); 
	pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);

		while(!pRst->rsEOF)
		{
			kecheng.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("name"));
			((CListBox*)GetDlgItem(IDC_LIST2))->AddString(kecheng);
			pRst->MoveNext();
		}

	pRst->Close();

	//mmpConn->Close();
	//mmpRst.Release();
	//mmpConn.Release();
	//CoUninitialize();
	//
	

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void leaveDlg::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	AfxExtractSubString(m_COID,(LPCTSTR)m_course,0,'-'); 
	AfxExtractSubString(csTemp,(LPCTSTR)m_course,1,'-'); 

	CString sql=_T("");

	//sql.Format(_T("select * from course where ID='%s'"),m_COID); 
	////pRst.CreateInstance("ADODB.Recordset");
	//pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);

	//pRst->Close();


	CString kecheng=_T("");
	((CListBox*)GetDlgItem(IDC_LIST2))->ResetContent();


	sql.Format(_T("select * from people where CID='%s'"),csTemp); 
	//pRst.CreateInstance("ADODB.Recordset");
	pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);

		while(!pRst->rsEOF)
		{
			kecheng.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("name"));
			((CListBox*)GetDlgItem(IDC_LIST2))->AddString(kecheng);
			pRst->MoveNext();
		}

	pRst->Close();
}

void leaveDlg::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	UpdateData();
	int weekday=m_daysel.GetDayOfWeek()-1;

		if ((weekday==0)|(weekday==6))
	{
		weekday=1;
	}

	CString sql=_T("");
	((CListBox*)GetDlgItem(IDC_LIST1))->ResetContent();


	sql.Format(_T("select * from course where weektime=%d"),weekday); 
	pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
	//CID.Format((_bstr_t)mmpRst->GetCollect("CID"));
	while(!pRst->rsEOF)
	{
		sql.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("CID")+_T("-")+(_bstr_t)pRst->GetCollect("coursename"));
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(sql);
		pRst->MoveNext();
	}

		pRst->Close();
		((CListBox*)GetDlgItem(IDC_LIST1))->SetCurSel(0);



		
	UpdateData();
	//CString csTemp;
	AfxExtractSubString(csTemp,(LPCTSTR)m_course,1,'-'); 
	((CListBox*)GetDlgItem(IDC_LIST2))->ResetContent();

	sql.Format(_T("select * from people where CID='%s'"),csTemp); 
	pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);

		while(!pRst->rsEOF)
		{
			sql.Format((_bstr_t)pRst->GetCollect("ID")+_T("-")+(_bstr_t)pRst->GetCollect("name"));
			((CListBox*)GetDlgItem(IDC_LIST2))->AddString(sql);
			pRst->MoveNext();
		}

	pRst->Close();


}

void leaveDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_people.IsEmpty())
	{
		MessageBox(_T("请选中需要请假的人")); 
	}
	else 
	{
		CTime mt = CTime::GetCurrentTime();
		CString strTime;
		strTime = mt.Format("%Y/%m/%d");

		CString sql;
		long newid;
		sql.Format(_T("select * from state"));
		pRst->Open(_variant_t(sql),_variant_t((IDispatch*)theApp.pConn),adOpenDynamic,adLockOptimistic,adCmdText);
		CString mpeo;
	    pRst->MoveLast();
		//mid.Format((_bstr_t)pRst->GetCollect("ID"));
		 _variant_t vIndex = (long)0;//How to get field value in only 1 record and 1 field condition.
        _variant_t vtemp =pRst->GetCollect("ID");
		newid =(long)(pRst->GetCollect(vIndex))+1;

		AfxExtractSubString(mpeo,(LPCTSTR)m_people,0,'-'); 
		bool takeoff=true;


		 try
		 {
		  pRst->AddNew();       //添加新行
		 pRst->PutCollect("ID",(_bstr_t)newid);

		  pRst->PutCollect("PID",(_bstr_t)mpeo);
		  pRst->PutCollect("COID",(_bstr_t)m_COID);
		  pRst->PutCollect("sday",(_bstr_t)strTime);
		  pRst->PutCollect("takeoff",(_bstr_t)takeoff);
		  pRst->Update();       //更新数据表记录
		  pRst->Close();

		 }
		 catch(...)            //捕捉可能出现的错误
		 {
		  MessageBox(_T("操作失败"));        //弹出错误提示
		  return;
		 }

		MessageBox(_T("OK！")); 
	}
}
