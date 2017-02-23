// leaveDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CheckInSys.h"
#include "leaveDlg.h"



extern CCheckInSysApp theApp;
// leaveDlg �Ի���

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


// leaveDlg ��Ϣ�������

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
    //    MessageBox(_T("���ݿ�����ʧ�ܣ�ȷ�����ݿ��Ƿ��ڵ�ǰ·����!"));   
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
	

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void leaveDlg::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (m_people.IsEmpty())
	{
		MessageBox(_T("��ѡ����Ҫ��ٵ���")); 
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
		  pRst->AddNew();       //�������
		 pRst->PutCollect("ID",(_bstr_t)newid);

		  pRst->PutCollect("PID",(_bstr_t)mpeo);
		  pRst->PutCollect("COID",(_bstr_t)m_COID);
		  pRst->PutCollect("sday",(_bstr_t)strTime);
		  pRst->PutCollect("takeoff",(_bstr_t)takeoff);
		  pRst->Update();       //�������ݱ��¼
		  pRst->Close();

		 }
		 catch(...)            //��׽���ܳ��ֵĴ���
		 {
		  MessageBox(_T("����ʧ��"));        //����������ʾ
		  return;
		 }

		MessageBox(_T("OK��")); 
	}
}
